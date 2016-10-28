#ifndef _ONELABSERVER_H_
#define _ONELABSERVER_H_

#include <vector>
#include <string>
#include <queue>

#include "onelab.h"
#include "GmshSocket.h"
#include "NetworkUtils.h"
#ifdef HAVE_UDT
#include "UdtUtils.h"
#endif
#include "OnelabLocalNetworkClient.h"
#include "OnelabLocalClient.h"

class OnelabLocalClient;

class OnelabServer
{
private:
	static OnelabServer *_server;
	IPv4 _ip;
	std::vector<OnelabLocalNetworkClient> _clients;
  std::vector<OnelabLocalClient *> _localClients;
#ifndef WIN32
  pthread_t _runningThread;
  pthread_mutex_t _mutex_todo;
#else
  HANDLER _runningThread;
#endif
  bool _running;
  std::queue<std::string> _todoClient;
  std::queue<std::string> _todoAction;
	onelab::parameterSpace _parameterSpace;
	Socket _fds;
#ifdef HAVE_UDT
	UDTSOCKET _fdu;
	int _eid;
	void sendto(std::string client, UInt8 *buff, UInt32 len);
#endif
public:
	OnelabServer(UInt16 port);
	OnelabServer(UInt32 iface, UInt16 port);
	static OnelabServer *instance(const UInt32 iface=0, const UInt16 port=0) {
		if(!_server) _server = new OnelabServer(iface, port);
    else if(iface != 0 || port != 0) {
      delete _server;
      _server = new OnelabServer(iface, port);
    }
		return _server;
	}
	static void setInstance(OnelabServer *s) { _server = s; }
  onelab::parameterSpace *getParameterSpace() {return &_parameterSpace;}
  UInt16 getPort() { return _ip.port;}
#ifdef HAVE_UDT
	~OnelabServer(){UDT::cleanup();}
#else
	~OnelabServer(){}
#endif
	void Run();
  bool isRunning() const {return _running;}
  void running(bool running) {_running = running;}
	// Client methods
#ifdef HAVE_UDT
	inline int getEID() const {return _eid;}
	void addClient(std::string name, UDTSOCKET fd, UInt32 ip, UInt16 port);
	OnelabLocalNetworkClient *getClient(UDTSOCKET fd);
#else
	void addClient(std::string name, UInt32 ip, UInt16 port);
#endif
  void addClient(OnelabLocalClient *cli) {_localClients.push_back(cli);}
  int launchClient(const std::string &, bool blocking=false);
	void removeClient(OnelabLocalNetworkClient *client);
  std::vector<OnelabLocalNetworkClient> &getClients() {return _clients;}
  std::vector<OnelabLocalClient *> &getLocalClients() {return _localClients;}
	OnelabLocalNetworkClient *getClient(const UInt32 ip, const UInt16 port);
	OnelabLocalNetworkClient *getClient(const std::string &name);
  OnelabLocalClient *getLocalClient(const std::string &name);
  void waitForClient(const std::string &name);
	void sendAllParameter(OnelabLocalNetworkClient *cli);
	// Parameters methods
	void clear(const std::string &name="", const std::string &client="") {
		_parameterSpace.clear(name, client);
	}
  template <class T> bool existInDatabase(const T &p) {
    std::vector<T> ps;
    _parameterSpace.get(ps, p.getName());
    return ps.size() > 0;
  }
	template <class T> bool set(const T &p, const std::string &client="") {
    bool isNew = !existInDatabase(p);
		_parameterSpace.set(p, client);
    T *pp;
    _parameterSpace.getPtr(&pp, p.getName());
    if(pp->getVisible()) {
      pp->addClient("GUI", true);
      pp->addClient("localGUI", true);
    }
    for(std::vector<OnelabLocalClient *>::iterator it = _localClients.begin() ; it != _localClients.end(); ++it) {
      if((*it)->getName() != client) {
        if(isNew)(*it)->onNewParameter(pp);
        else (*it)->onUpdateParameter(pp);
      }
    }
    std::map<std::string, bool> clients = pp->getClients();
    for(std::map<std::string, bool>::const_iterator it = clients.begin(); it != clients.end(); it++) {
      if(it->first == client) continue;
      OnelabLocalNetworkClient *tmp = getClient(it->first);
      if(tmp == NULL) continue;
      tmp->updateParameter(pp);
    }
    return true;
	}
	template <class T> bool get(std::vector<T> &ps, const std::string &name="", const std::string &client="") {
		return _parameterSpace.get(ps, name, client);
	}
	template <class T> void getPtr(T **ptr, const std::string &name="", const std::string &client="") {
		_parameterSpace.getPtr(ptr, name, client);
	}
  bool fromChar(const std::vector<std::string> &msg, const std::string &client="")
  {
    for(unsigned int i = 0; i < msg.size(); i++){
      std::string version, type, name;
      onelab::parameter::getInfoFromChar(msg[i], version, type, name);
      if(onelab::parameter::version() != version) return false;
      if(type == "number"){
        onelab::number p; p.fromChar(msg[i]); set(p, client);
      }
      else if(type == "string"){
        onelab::string p; p.fromChar(msg[i]); set(p, client);
      }
      else if(type == "region"){
        onelab::region p; p.fromChar(msg[i]); set(p, client);
      }
      else if(type == "function"){
        onelab::function p; p.fromChar(msg[i]); set(p, client);
      }
      else
        return false;
    }
    return true;
  }
  bool fromFile(FILE *fp, const std::string &client="")
  {
    std::vector<std::string> msg;
    if(onelab::parameter::fromFile(msg, fp)) return fromChar(msg, client);
    return false;
  }
  bool getChanged(const std::string &client="") const {
    return _parameterSpace.getChanged(client);
  }
  void setChanged(bool changed, const std::string &client="") {
    _parameterSpace.setChanged(changed, client);
  }
  void performAction(const std::string action, const std::string client="", bool blocking=false);
  bool performNextAction();
};
#endif
