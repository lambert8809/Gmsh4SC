#ifndef _ONELAB_ATTRIBUTES_H
#define _ONELAB_ATTRIBUTES_H

#define SESSION_SIZE 32

#define ERROR_BUFFER_TOO_SMALL 50
#define ERROR_INVALID_ATTRIBUTE_SIZE 51

#include <stdlib.h>
#include <stdio.h>

#include "NetworkUtils.h"

class OnelabAttr
{
protected:
	// Header :
	//UInt16 _type;
	//UInt16 _size;

	bool _stored; // is the attribute in the database ?
public:
	OnelabAttr() {}
	virtual ~OnelabAttr(){}

	virtual UInt8 *encodeAttribute(UInt8 *dst) = 0;
	virtual UInt8 *parseAttribute(UInt8 *src, UInt32 length) = 0;
	virtual void showAttribute() const = 0;

	virtual inline UInt16 getAttributeType() const = 0;
	virtual inline UInt16 getAttributeLength() const = 0;

	bool isInDatabase() const {return this->_stored;}
	void isInDatabase(bool isInDb) {this->_stored = isInDb;}

	// attributes type to connect peers
	static const UInt16 Peer = 0x01;
	static const UInt16 Server = 0x02;
	static const UInt16 Session = 0x03;

	// attributes type for onelab
	static const UInt16 Start = 0x04;
	static const UInt16 Parameter = 0x05;
	static const UInt16 Number = 0x06;
	static const UInt16 String = 0x07;
	static const UInt16 Region = 0x08;
	static const UInt16 Function = 0x09;

	// other message for onelab
	static const UInt16 Message = 0x0A;

};

class OnelabAttrStart : public OnelabAttr
{
private:
	std::string _name;
public:
	OnelabAttrStart() {}
	OnelabAttrStart(const std::string name) {_name = name;}
	~OnelabAttrStart(){}
	UInt8 *encodeAttribute(UInt8 *dst);
	UInt8 *parseAttribute(UInt8 *src, UInt32 length);
	void showAttribute() const;

	static UInt16 attributeType() {return 0x04;}
	inline UInt16 getAttributeType() const {return this->attributeType();}
	inline UInt16 getAttributeLength() const {return _name.size();}

	std::string name(){return _name;}
};

class OnelabAttrParameterQuery : public OnelabAttr
{
private:
	UInt8 _ptype;
	std::string _pname;
public:
	OnelabAttrParameterQuery() {}
	OnelabAttrParameterQuery(const std::string name, UInt8 parameter) {_ptype = parameter; _pname = name;}
	~OnelabAttrParameterQuery() {}
	UInt8 *encodeAttribute(UInt8 *buff);
	UInt8 *parseAttribute(UInt8 *buff, UInt32 length);
	void showAttribute() const;

	static UInt16 attributeType() {return 0x05;}
	inline UInt16 getAttributeType() const {return this->attributeType();}
	inline UInt16 getAttributeLength() const {return 1+_pname.size();}

	inline UInt8 paramType() const {return this->_ptype;}
	std::string getName() const {return this->_pname;}
};

class OnelabAttrMessage : public OnelabAttr
{
private:
	UInt8 *_message = NULL;
	UInt16 _messageLength;
	UInt8 _level;
	
public:
	OnelabAttrMessage() : _message(NULL), _messageLength(0), _level(0) {}
	OnelabAttrMessage(const std::string &message, const int level=OnelabAttrMessage::Debug) : _message(NULL){setMessage(message, level);}
	~OnelabAttrMessage(){if(_message != NULL) free(_message);};
	UInt8 *encodeAttribute(UInt8 *dst);
	UInt8 *parseAttribute(UInt8 *src, UInt32 length);
	void showAttribute() const;

	static UInt16 attributeType() {return 0x0A;}
	inline UInt16 getAttributeType() const {return this->attributeType();}
	inline UInt16 getAttributeLength() const {return 1+_messageLength;}

	void setMessage(const std::string &message, const int level=OnelabAttrMessage::Debug) {
		_level = level;
		_messageLength = message.size()+1;
		if(_message != NULL) free(_message);
		_message = (UInt8 *)strndup(message.c_str(), _messageLength);
	}
	const char *getMessage() {return (char *)_message;}
	int getLevel() {return _level;}

	typedef enum {
		Debug=99,
		Info=5,
		Warning=3,
		Error=2,
		Fatal=1
	} OnelabMessageLvl;
};

class OnelabAttrAction : public OnelabAttr
{
private:
  std::string _action;
  std::string _client;

public:
  OnelabAttrAction() : _action(""), _client("") {}
  OnelabAttrAction(std::string action, std::string client) : _action(action), _client(client) {}
  ~OnelabAttrAction() {}

  UInt8 *encodeAttribute(UInt8 *dst);
  UInt8 *parseAttribute(UInt8 *src, UInt32 lenght);
  void showAttribute() const;

  static UInt16 attributeType() {return 0x10;}
  inline UInt16 getAttributeType() const {return attributeType();}
  inline UInt16 getAttributeLength() const {return _client.size()+1+_action.size();}

  void setAction(std::string action) {_action = action;}
  void setClient(std::string client) {_client = client;}
  std::string getAction() {return _action;}
  std::string getClient() {return _client;}
};

class OnelabAttrFileQuery : public OnelabAttr
{
private:
  char *_name;
  UInt16 _length;
  std::string _client;

public:
  OnelabAttrFileQuery() : _name(NULL), _length(0){}
  OnelabAttrFileQuery(const std::string filename) : _name(NULL), _length(0) {setFilename(filename);}
  ~OnelabAttrFileQuery() {if(_name != NULL) free(_name);}
  UInt8 *encodeAttribute(UInt8 *dst);
  UInt8 *parseAttribute(UInt8 *src, UInt32 length);
  void showAttribute() const;

  static UInt16 attributeType() {return 0x0B;}
  inline UInt16 getAttributeType() const {return attributeType();}
  inline UInt16 getAttributeLength() const {return _length+_client.length()+1;}

  void setFilename(std::string name);
  void setClient(std::string client) {_client = client;}
  const char *getFilename() {return _name;}
};

class OnelabAttrMergeFile : public OnelabAttr
{
private:
  char *_name;
  UInt16 _length;

public:
  OnelabAttrMergeFile() : _name(NULL), _length(0){}
  OnelabAttrMergeFile(const std::string filename) : _name(NULL), _length(0) {setFilename(filename);}
  ~OnelabAttrMergeFile() {if(_name != NULL) free(_name);}
  UInt8 *encodeAttribute(UInt8 *dst);
  UInt8 *parseAttribute(UInt8 *src, UInt32 length);
  void showAttribute() const;

  static UInt16 attributeType() {return 0x0D;}
  inline UInt16 getAttributeType() const {return attributeType();}
  inline UInt16 getAttributeLength() const {return _length;}

  void setFilename(std::string name);
  const char *getFilename() {return _name;}
};

class OnelabAttrFile : public OnelabAttr
{
private:
  char *_name;
  FILE *_fd;
  UInt32 _filelength;

public:
  OnelabAttrFile() : _name(NULL), _filelength(0) {}
  OnelabAttrFile(const std::string filename, FILE *fd) {setFile(filename, fd);}
  ~OnelabAttrFile() {if(_name != NULL) free(_name);}
  UInt8 *encodeAttribute(UInt8 *dst);
  UInt8 *parseAttribute(UInt8 *src, UInt32 length);
  void showAttribute() const;

  static UInt16 attributeType() {return 0x0C;}
  inline UInt16 getAttributeType() const {return attributeType();}
  inline UInt16 getAttributeLength() const {return 4+strlen(_name);}

  void setFile(std::string name, FILE *fd) 
  {
    if(_name != NULL) free(_name);
    _name = strndup(name.c_str(), name.size()+1);
    _fd = fd;
    long pos = ftell(fd); fseek(fd, 0, SEEK_END);
    _filelength = (UInt32)ftell(fd); fseek(fd, pos, SEEK_SET);
  }
  const char *getFilename() {return _name;}
  unsigned int getFileSize() {return _filelength;}
};

#endif
