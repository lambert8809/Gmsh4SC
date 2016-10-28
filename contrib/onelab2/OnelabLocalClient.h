#ifndef _ONELABLOCALCLIENT_H_
#define _ONELABLOCALCLIENT_H_

#include "VirtualClient.h"

/**
  @class OnelabLocalClient
  @brief This class is used for client in the same memory space as the server.

*/

class OnelabLocalClient : public VirtualClient
{
public:
	OnelabLocalClient(std::string name, onelab::parameterSpace *parameterSpace)
		: VirtualClient(name, parameterSpace){
	}
	virtual ~OnelabLocalClient(){}
	virtual void onNewParameter(onelab::parameter *p){}
  virtual void onUpdateParameter(onelab::parameter *p){}
  virtual void onRemoveParameter(onelab::parameter *p){}
  virtual void onMessage(const std::string &name, const std::string &message, int level){}
  virtual void refresh(){}
  virtual void mergeFile(const std::string &filename){}

  virtual void run(std::string action) {}
  void stop() {}
};

#endif
