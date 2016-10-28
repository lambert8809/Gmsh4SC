// ONELAB - Copyright (C) 2011-2014 ULg-UCL
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, and/or sell copies of the
// Software, and to permit persons to whom the Software is furnished
// to do so, provided that the above copyright notice(s) and this
// permission notice appear in all copies of the Software and that
// both the above copyright notice(s) and this permission notice
// appear in supporting documentation.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR
// ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY
// DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
// ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//
// Please report all bugs and problems to the public mailing list
// <gmsh@geuz.org>.

#ifndef _ONELAB_H_
#define _ONELAB_H_

#include <time.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include "GmshSocket.h"

#ifdef HAVE_ONELAB2
#include "NetworkUtils.h"
#include "OnelabAttributes.h"
#endif

namespace onelab{

  // The base parameter class.
#ifdef HAVE_ONELAB2
  class parameter : public OnelabAttr{
#else
  class parameter {
#endif
  private:
    // the name of the parameter, including its '/'-separated path in the
    // parameter hierarchy. Parameters or subpaths can start with numbers to
    // force their relative ordering (such numbers are automatically hidden in
    // the interface). All strings in onelab are supposed to be UTF8-encoded.
    std::string _name;
    // the parameter label: if provided it serves as a better way to display the
    // parameter in the interface
    std::string _label;
    // a help string
    std::string _help;
    // map of clients that use this parameter, associated with a "changed" flag
    // (set to false if the client has already been run with the current value of
    // the parameter)
    std::map<std::string, bool> _clients;
    // flag indicating that the "changed" flags of this parameter will always be
    // reset to false when the parameter is updated
    bool _neverChanged;
    // should the parameter be visible in the interface?
    bool _visible;
    // sould the paramete be "read-only" (not settable by the user)
    bool _readOnly;
  protected:
    // optional additional attributes
    std::map<std::string, std::string> _attributes;
  public:
    parameter(const std::string &name="", const std::string &label="",
              const std::string &help="")
      : _name(name), _label(label), _help(help), _neverChanged(false),
        _visible(true), _readOnly(false) {}
    virtual ~parameter(){}
    void setName(const std::string &name){ _name = name; }
    void setLabel(const std::string &label){ _label = label; }
    void setHelp(const std::string &help){ _help = help; }
    void setChanged(bool changed, const std::string &client="")
    {
      if(client.size()){
        std::map<std::string, bool>::iterator it = _clients.find(client);
        if(it != _clients.end()) it->second = changed;
      }
      else{
        for(std::map<std::string, bool>::iterator it = _clients.begin();
            it != _clients.end(); it++)
          it->second = changed;
      }
    }
    void setNeverChanged(bool never){ _neverChanged = never; }
    void setVisible(bool visible){ _visible = visible; }
    void setReadOnly(bool readOnly){ _readOnly = readOnly; }
    void setAttribute(const std::string &key, const std::string &value)
    {
      _attributes[key] = value;
    }
    void setAttributes(const std::map<std::string, std::string> &attributes)
    {
      _attributes = attributes;
    }
    void setClients(const std::map<std::string, bool> &clients){ _clients = clients; }
    void addClient(const std::string &client, bool changed)
    {
      if(_clients.find(client) == _clients.end())
        _clients[client] = changed;
    }
    void addClients(const std::map<std::string, bool> &clients)
    {
      _clients.insert(clients.begin(), clients.end());
    }
    bool hasClient(const std::string &client)
    {
      return (_clients.find(client) != _clients.end());
    }
    int getNumClients() { return (int)_clients.size(); };
    virtual std::string getType() const = 0;
    const std::string &getName() const { return _name; }
    const std::string &getLabel() const { return _label; }
    const std::string &getHelp() const { return _help; }
    std::string getPath() const
    {
      std::string::size_type last = _name.find_last_of('/');
      return _name.substr(0, last);
    }
    std::string getShortName() const
    {
      if(_label.size()) return _label;
      std::string s = _name;
      // remove path
      std::string::size_type last = _name.find_last_of('/');
      if(last != std::string::npos)
        s = _name.substr(last + 1);
      // remove starting numbers
      while(s.size() && s[0] >= '0' && s[0] <= '9')
        s = s.substr(1);
      return s;
    }
    bool getChanged(const std::string &client="") const
    {
      if(client.size()){
        std::map<std::string, bool>::const_iterator it = _clients.find(client);
        if(it != _clients.end()) return it->second;
        else return false;
      }
      else{
        for(std::map<std::string, bool>::const_iterator it = _clients.begin();
            it != _clients.end(); it++){
          if(it->second) return true;
        }
        return false;
      }
    }
    bool getNeverChanged() const { return _neverChanged; }
    bool getVisible() const { return _visible; }
    bool getReadOnly() const { return _readOnly; }
    std::string getAttribute(const std::string &key) const
    {
      std::map<std::string, std::string>::const_iterator it = _attributes.find(key);
      if(it != _attributes.end()) return it->second;
      return "";
    }
    const std::map<std::string, std::string> &getAttributes() const
    {
      return _attributes;
    }
    const std::map<std::string, bool> &getClients() const { return _clients; }
    static char charSep() { return '\0'; }
    static double maxNumber() { return 1e200; }
    static std::string version() { return "1.1"; }
    static std::string getNextToken(const std::string &msg,
                                    std::string::size_type &first,
                                    char separator=charSep())
    {
      if(first == std::string::npos) return "";
      std::string::size_type last = msg.find_first_of(separator, first);
      std::string next("");
      if(last == std::string::npos){
        next = msg.substr(first);
        first = last;
      }
      else if(first == last){
        next = "";
        first = last + 1;
      }
      else{
        next = msg.substr(first, last - first);
        first = last + 1;
      }
      return next;
    }
    static std::vector<std::string> split(const std::string &msg,
                                          char separator=charSep())
    {
      std::vector<std::string> out;
      std::string::size_type first = 0;
      while(first != std::string::npos)
        out.push_back(getNextToken(msg, first, separator));
      return out;
    }
    std::string sanitize(const std::string &in) const
    {
      std::string out(in);
      for(unsigned int i = 0; i < in.size(); i++)
        if(out[i] == charSep()) out[i] = ' ';
      return out;
    }
    virtual std::string toChar() const
    {
      std::ostringstream sstream;
      sstream << version() << charSep() << getType() << charSep()
              << sanitize(getName()) << charSep()
              << sanitize(getLabel()) << charSep()
              << sanitize(getHelp()) << charSep()
              << (getNeverChanged() ? 1 : 0) << charSep()
              << (getVisible() ? 1 : 0) << charSep()
              << (getReadOnly() ? 1 : 0) << charSep()
              << _attributes.size() << charSep();
      for(std::map<std::string, std::string>::const_iterator it = _attributes.begin();
          it != _attributes.end(); it++)
        sstream << sanitize(it->first) << charSep()
                << sanitize(it->second) << charSep();
      sstream << getClients().size() << charSep();
      for(std::map<std::string, bool>::const_iterator it = getClients().begin();
          it != getClients().end(); it++)
        sstream << sanitize(it->first) << charSep()
                << (it->second ? 1 : 0) << charSep();
      return sstream.str();
    }
    virtual std::string::size_type fromChar(const std::string &msg)
    {
      std::string::size_type pos = 0;
      if(getNextToken(msg, pos) != version()) return 0;
      if(getNextToken(msg, pos) != getType()) return 0;
      setName(getNextToken(msg, pos));
      setLabel(getNextToken(msg, pos));
      setHelp(getNextToken(msg, pos));
      setNeverChanged(atoi(getNextToken(msg, pos).c_str()));
      setVisible(atoi(getNextToken(msg, pos).c_str()));
      setReadOnly(atoi(getNextToken(msg, pos).c_str()));
      int numAttributes = atoi(getNextToken(msg, pos).c_str());
      for(int i = 0; i < numAttributes; i++){
        std::string key(getNextToken(msg, pos));
        setAttribute(key, getNextToken(msg, pos));
      }
      int numClients = atoi(getNextToken(msg, pos).c_str());
      for(int i = 0; i < numClients; i++){
        std::string client(getNextToken(msg, pos));
        int changed = atoi(getNextToken(msg, pos).c_str());
        addClient(client, changed ? true : false);
      }
      return pos;
    }
    static void getInfoFromChar(const std::string &msg, std::string &version,
                                std::string &type, std::string &name)
    {
      std::string::size_type first = 0;
      version = getNextToken(msg, first);
      type = getNextToken(msg, first);
      name = getNextToken(msg, first);
    }
    static bool fromFile(std::vector<std::string> &msg,
                         FILE *fp)
    {
      msg.clear();
      char tmp[1000];
      if(!fgets(tmp, sizeof(tmp), fp)) return false; // first line is comment
      while(!feof(fp)){
        int numc = 0;
        if(!fscanf(fp, "%d ", &numc)) break; // space is important
        if(!numc) break;
        msg.push_back("");
        for(int i = 0; i < numc; i++)
          msg.back() += fgetc(fp);
        if(!fgets(tmp, sizeof(tmp), fp)) break; // end of line
      }
      return true;
    }
    static bool toFile(const std::vector<std::string> &msg,
                       FILE *fp,
                       const std::string &creator)
    {
      time_t now;
      time(&now);
      fprintf(fp, "ONELAB database created by %s on %s",
              creator.c_str(), ctime(&now));
      for(unsigned int i = 0; i < msg.size(); i++){
        fprintf(fp, "%d ", (int)msg[i].size());
        for(unsigned int j = 0; j < msg[i].size(); j++)
          fputc(msg[i][j], fp);
        fputc('\n', fp);
      }
      return true;
    }
#ifdef HAVE_ONELAB2
    static UInt16 attributeType() {return 0x05;}
    virtual inline UInt16 getAttributeType() const {return this->attributeType();}
    virtual inline UInt16 getAttributeLength() const {
      UInt16 len = _name.length()+_label.length()+_help.length()+10;
      for(std::map<std::string, bool>::const_iterator it = getClients().begin(); it != getClients().end(); it++)
        len += it->first.size()+2;
      for(std::map<std::string, std::string>::const_iterator it = _attributes.begin(); it != _attributes.end(); it++)
        len += it->first.size()+it->second.size()+2;
      return len;
    }
    virtual UInt8 *encodeAttribute(UInt8 *dst)
    {
      dst = encode(dst, getAttributeType());
      dst = encode(dst, getAttributeLength());

      dst = encode(dst, (UInt8 *)_name.c_str(), this->_name.length()+1);
      dst = encode(dst, (UInt8 *)_label.c_str(), this->_label.length()+1);
      dst = encode(dst, (UInt8 *)_help.c_str(), this->_help.length()+1);
      dst = encode(dst, (UInt8)_readOnly);
      dst = encode(dst, (UInt8)_neverChanged);
      dst = encode(dst, (UInt8)_visible);

      dst = encode(dst, (UInt16)_attributes.size());
      for(std::map<std::string, std::string>::const_iterator it = _attributes.begin(); it != _attributes.end(); it++) {
        dst = encode(dst, (UInt8 *)it->first.c_str(), it->first.size()+1);
        dst = encode(dst, (UInt8 *)it->second.c_str(), it->second.size()+1);
      }

      dst = encode(dst, (UInt16)_clients.size());
      for(std::map<std::string, bool>::const_iterator it = getClients().begin(); it != getClients().end(); it++) {
        dst = encode(dst, (UInt8 *)it->first.c_str(), it->first.size()+1);
        dst = encode(dst, (UInt8)it->second);
      }

      return dst;
    }
    virtual UInt8 *parseAttribute(UInt8 *src, UInt32 length)
    {
      UInt8 tmp;
      UInt16 n;

      src = parse(src, _name, '\0');
      src = parse(src, _label, '\0');
      src = parse(src, _help, '\0');
      src = parse(src, tmp);
      this->_readOnly = (bool)tmp;
      src = parse(src, tmp);
      this->_neverChanged = (bool)tmp;
      src = parse(src, tmp);
      this->_visible = (bool)tmp;

      src = parse(src, n);
      for(int i=0; i<n; i++) {
        std::string key, value;
        src = parse(src, key, '\0');
        src = parse(src, value, '\0');
        setAttribute(key, value);
      }

      src = parse(src, n);
      for(int i=0; i<n; i++) {
        std::string client;
        src = parse(src, client, '\0');
        src = parse(src, tmp);
        addClient(client, (bool)tmp);
      }

      return src;
    }
    void showAttribute() const
    {
      std::cout << "Name: " << getName() << std::endl
        << "Label: " << getLabel() << std::endl
        << "Help: " << getHelp() << std::endl
        << "Never changed: " << getNeverChanged() << std::endl
        << "Changed: " << getChanged() << std::endl
        << "Visible: " << getVisible() << std::endl;
    }
#endif
  };

  class parameterLessThan{
  public:
    bool operator()(const parameter *p1, const parameter *p2) const
    {
      return p1->getName() < p2->getName();
    }
  };

  // The number class. Numbers are stored internally as double precision real
  // numbers. All more complicated types (complex numbers, vectors, etc.) are
  // supposed to be either exchanged as strings or encapsulated in functions.
  class number : public parameter{
  private:
    double _value, _min, _max, _step;
    // when in a loop, indicates current index in the vector _choices;
    // is -1 when not in a loop
    int _index;
    std::vector<double> _choices;
    std::map<double, std::string> _valueLabels;
  public:
    number(const std::string &name="", double value=0.,
           const std::string &label="", const std::string &help="")
      : parameter(name, label, help), _value(value),
      _min(-maxNumber()), _max(maxNumber()), _step(0.), _index(-1) {}
    void setValue(double value){ _value = value; }
    void setMin(double min){ _min = min; }
    void setMax(double max){ _max = max; }
    void setStep(double step){ _step = step; }
    void setIndex(int index){ _index = index; }
    void setChoices(const std::vector<double> &choices){ _choices = choices; }
    void setChoiceLabels(const std::vector<std::string> &labels)
    {
      if(labels.size() != _choices.size()) return;
      for(unsigned int i = 0; i < _choices.size(); i++)
        _valueLabels[_choices[i]] = labels[i];
    }
    void setValueLabels(const std::map<double, std::string> &valueLabels)
    {
      _valueLabels = valueLabels;
    }
    void setValueLabel(double value, const std::string &label)
    {
      _valueLabels[value] = label;
    }
    std::string getType() const { return "number"; }
    double getValue() const { return _value; }
    double getMin() const { return _min; }
    double getMax() const { return _max; }
    double getStep() const { return _step; }
    int getIndex() const { return _index; }
    const std::vector<double> &getChoices() const { return _choices; }
    const std::map<double, std::string> &getValueLabels() const
    {
      return _valueLabels;
    }
    std::string getValueLabel(double value) const
    {
      std::map<double, std::string>::const_iterator it = _valueLabels.find(value);
      if(it != _valueLabels.end()) return it->second;
      return "";
    }
    void update(const number &p)
    {
      addClients(p.getClients());
      setLabel(p.getLabel());
      setHelp(p.getHelp());
      setVisible(p.getVisible());
      setReadOnly(p.getReadOnly());
      setAttributes(p.getAttributes());
      if(p.getValue() != getValue()){
        setValue(p.getValue());
        setChanged(true);
      }
      setMin(p.getMin());
      setMax(p.getMax());
      setStep(p.getStep());
      setIndex(p.getIndex());
      setChoices(p.getChoices());
      setValueLabels(p.getValueLabels());
      if(getNeverChanged()) setChanged(false);
    }
    std::string toChar() const
    {
      std::ostringstream sstream;
      sstream.precision(16);
      sstream << parameter::toChar() << _value << charSep()
              << _min << charSep() << _max << charSep() << _step << charSep()
	      << _index << charSep()
              << _choices.size() << charSep();
      for(unsigned int i = 0; i < _choices.size(); i++)
        sstream << _choices[i] << charSep();
      sstream << _valueLabels.size() << charSep();
      for(std::map<double, std::string>::const_iterator it = _valueLabels.begin();
          it != _valueLabels.end(); it++){
        sstream << it->first << charSep();
        sstream << sanitize(it->second) << charSep();
      }
      return sstream.str();
    }
    std::string::size_type fromChar(const std::string &msg)
    {
      std::string::size_type pos = parameter::fromChar(msg);
      if(!pos) return 0;
      setValue(atof(getNextToken(msg, pos).c_str()));
      setMin(atof(getNextToken(msg, pos).c_str()));
      setMax(atof(getNextToken(msg, pos).c_str()));
      setStep(atof(getNextToken(msg, pos).c_str()));
      setIndex(atoi(getNextToken(msg, pos).c_str()));
      _choices.resize(atoi(getNextToken(msg, pos).c_str()));
      for(unsigned int i = 0; i < _choices.size(); i++)
        _choices[i] = atof(getNextToken(msg, pos).c_str());
      int numValueLabels = atoi(getNextToken(msg, pos).c_str());
      for(int i = 0; i < numValueLabels; i++){
        double value = atof(getNextToken(msg, pos).c_str());
        _valueLabels[value] = getNextToken(msg, pos);
      }
      return pos;
    }
#ifdef HAVE_ONELAB2
    static UInt16 attributeType() {return 0x06;}
    virtual inline UInt16 getAttributeType() const {return this->attributeType();}
    virtual inline UInt16 getAttributeLength() const {
      UInt16 len = parameter::getAttributeLength()+sizeof(double)*4+8+sizeof(double)*_choices.size();
      for(std::map<double, std::string>::const_iterator it = _valueLabels.begin(); it != _valueLabels.end(); it++)
        len += it->second.size()+1+sizeof(double);
      return len;
    }
    UInt8 *encodeAttribute(UInt8 *dst)
    {
      dst = parameter::encodeAttribute(dst);

      dst = encode(dst, _value);
      dst = encode(dst, _min);
      dst = encode(dst, _max);
      dst = encode(dst, _step);
      dst = encode(dst, (UInt32)_index);

      dst = encode(dst, (UInt16)_choices.size());
      for(unsigned int i = 0; i < _choices.size(); i++)
        dst = encode(dst, _choices[i]);

      dst = encode(dst, (UInt16)_valueLabels.size());
      for(std::map<double, std::string>::const_iterator it = _valueLabels.begin(); it != _valueLabels.end(); it++) {
        dst = encode(dst, it->first);
        dst = encode(dst, (UInt8 *)it->second.c_str(), it->second.size()+1);
      }

      return dst;
    }
    UInt8 *parseAttribute(UInt8 *src, UInt32 length)
    {
      UInt16 n;

      src = parameter::parseAttribute(src, length);

      src = parse(src, _value);
      src = parse(src, _min);
      src = parse(src, _max);
      src = parse(src, _step);
      src = parse(src, *(UInt32 *)&_index);

      src = parse(src, n);
      _choices.resize(n);
      for(unsigned int i = 0; i < n; i++)
        src = parse(src, _choices[i]);

      src = parse(src, n);
      for(int i=0; i<n; i++) {
        double value;
        std::string label;
        src = parse(src, value);
        src = parse(src, label, '\0');
        setValueLabel(value, label);
      }

      return src;
    }
    void showAttribute() const
    {
      parameter::showAttribute();
      std::cout << "Value: " << this->_value << std::endl
        << "Min: " << this->_min << std::endl
        << "Max: " << this->_max << std::endl;
    }
#endif
  };

  // The string class. A string has a mutable "kind": we do not derive
  // specialized classes, because the kind should be changeable at runtime
  // (e.g. from a client-dependent mathematical expression to a table of
  // values). Kinds currently recognized by Gmsh are: "file". Possible
  // kinds could be "complex", "matrix m n", "hostname", client-dependent
  // mathematical expression, onelab mathematical expression (through mathex?),
  // ...
  class string : public parameter{
  private:
    std::string _value, _kind;
    std::vector<std::string> _choices;
  public:
    string(const std::string &name="", const std::string &value="",
           const std::string &label="", const std::string &help="")
      : parameter(name, label, help), _value(value), _kind("generic") {}
    void setValue(const std::string &value){ _value = value; }
    void setKind(const std::string &kind){ _kind = kind; }
    void setChoices(const std::vector<std::string> &choices){ _choices = choices; }
    std::string getType() const { return "string"; }
    const std::string &getValue() const { return _value; }
    const std::string &getKind() const { return _kind; }
    const std::vector<std::string> &getChoices() const { return _choices; }
    void update(const string &p)
    {
      addClients(p.getClients());
      setLabel(p.getLabel());
      setHelp(p.getHelp());
      setVisible(p.getVisible());
      setReadOnly(p.getReadOnly());
      setAttributes(p.getAttributes());
      if(p.getValue() != getValue()){
        setValue(p.getValue());
        setChanged(true);
      }
      if(p.getKind() != getKind()){
        setKind(p.getKind());
        setChanged(true);
      }
      setChoices(p.getChoices());
      if(getNeverChanged()) setChanged(false);
    }
    std::string toChar() const
    {
      std::ostringstream sstream;
      sstream << parameter::toChar() << sanitize(_value) << charSep()
              << sanitize(_kind) << charSep()
              << _choices.size() << charSep();
      for(unsigned int i = 0; i < _choices.size(); i++)
        sstream << sanitize(_choices[i]) << charSep();
      return sstream.str();
    }
    std::string::size_type fromChar(const std::string &msg)
    {
      std::string::size_type pos = parameter::fromChar(msg);
      if(!pos) return 0;
      setValue(getNextToken(msg, pos));
      setKind(getNextToken(msg, pos));
      _choices.resize(atoi(getNextToken(msg, pos).c_str()));
      for(unsigned int i = 0; i < _choices.size(); i++)
        _choices[i] = getNextToken(msg, pos);
      return pos;
    }
#ifdef HAVE_ONELAB2
    static UInt16 attributeType() {return 0x07;}
    virtual inline UInt16 getAttributeType() const {return this->attributeType();}
    virtual inline UInt16 getAttributeLength() const
    {
      UInt16 len =  parameter::getAttributeLength();
      len += _value.size()+_kind.size()+4;
      for(unsigned int i = 0; i < _choices.size(); i++)
        len += _choices[i].size()+1;
      return len;
    }
    UInt8 *encodeAttribute(UInt8 *dst)
    {
      dst = parameter::encodeAttribute(dst);

      dst = encode(dst, (UInt8 *)_value.c_str(), _value.size()+1);
      dst = encode(dst, (UInt8 *)_kind.c_str(), _kind.size()+1);

      dst = encode(dst, (UInt16)_choices.size());
      for(unsigned int i = 0; i < _choices.size(); i++)
        dst = encode(dst, (UInt8 *)_choices[i].c_str(), _choices[i].size()+1);

      return dst;
     }
    UInt8 *parseAttribute(UInt8 *src, UInt32 length)
    {
      UInt16 n;
      src = parameter::parseAttribute(src, length);
      src = parse(src, _value, '\0');
      src = parse(src, _kind, '\0');

      src = parse(src, n);
      _choices.resize(n);
      for(unsigned int i=0; i<n; i++) {
        src = parse(src, _choices[i], '\0');
      }

      return src;
    }
    void showAttribute() const
    {
      parameter::showAttribute();
      std::cout << "Value: " << this->_value << std::endl;
    }
#endif
  };

  // The region class. A region can be any kind of geometrical entity,
  // represented as identifiers of physical regions. Operations on regions will
  // include union, intersection, etc.
  class region : public parameter{
  private:
    std::set<std::string> _value;
    // optional geometrical dimension
    int _dimension;
    std::vector<std::set<std::string> > _choices;
  public:
    region(const std::string &name="",
           const std::set<std::string> &value = std::set<std::string>(),
           const std::string &label="", const std::string &help="")
      : parameter(name, label, help), _value(value), _dimension(-1) {}
    region(const std::string &name, const std::string &value,
           const std::string &label="", const std::string &help="")
      : parameter(name, label, help), _dimension(-1)
    {
      if(value.size()) _value.insert(value);
    }
    void setValue(const std::set<std::string> &value){ _value = value; }
    void setDimension(int dim){ _dimension = dim; }
    void setChoices(const std::vector<std::set<std::string> > &choices)
    {
      _choices = choices;
    }
    std::string getType() const { return "region"; }
    const std::set<std::string> &getValue() const { return _value; }
    int getDimension() const { return _dimension; }
    const std::vector<std::set<std::string> > &getChoices() const
    {
      return _choices;
    }
    void update(const region &p)
    {
      addClients(p.getClients());
      setLabel(p.getLabel());
      setHelp(p.getHelp());
      setAttributes(p.getAttributes());
      if(p.getValue() != getValue()){
        setValue(p.getValue());
        setChanged(true);
      }
      setDimension(p.getDimension());
      setChoices(p.getChoices());
      if(getNeverChanged()) setChanged(false);
    }
    std::string toChar() const
    {
      std::ostringstream sstream;
      sstream << parameter::toChar() << _value.size() << charSep();
      for(std::set<std::string>::const_iterator it = _value.begin();
          it != _value.end(); it++)
        sstream << sanitize(*it) << charSep();
      sstream << _dimension << charSep();
      sstream << _choices.size() << charSep();
      for(unsigned int i = 0; i < _choices.size(); i++){
        sstream << _choices[i].size() << charSep();
        for(std::set<std::string>::const_iterator it = _choices[i].begin();
            it != _choices[i].end(); it++)
          sstream << sanitize(*it) << charSep();
      }
      return sstream.str();
    }
    std::string::size_type fromChar(const std::string &msg)
    {
      std::string::size_type pos = parameter::fromChar(msg);
      if(!pos) return 0;
      int n = atoi(getNextToken(msg, pos).c_str());
      for(int i = 0; i < n; i++)
        _value.insert(getNextToken(msg, pos));
      setDimension(atoi(getNextToken(msg, pos).c_str()));
      _choices.resize(atoi(getNextToken(msg, pos).c_str()));
      for(unsigned int i = 0; i < _choices.size(); i++){
        n = atoi(getNextToken(msg, pos).c_str());
        for(int i = 0; i < n; i++)
          _choices[i].insert(getNextToken(msg, pos));
      }
      return pos;
    }
#ifdef HAVE_ONELAB2
    static UInt16 attributeType() {return 0x08;}
    virtual inline UInt16 getAttributeType() const {return this->attributeType();}
    virtual inline UInt16 getAttributeLength() const {
      UInt16 len = parameter::getAttributeLength();
      len += 2;
      for(std::set<std::string>::const_iterator it = _value.begin(); it != _value.end(); it++)
        len += it->size()+1;
      len += 4;
      len += 2;
      for(unsigned int i = 0; i < _choices.size(); i++){
        len += 2;
        for(std::set<std::string>::const_iterator it = _choices[i].begin(); it != _choices[i].end(); it++)
          len += it->size()+1;
      }
      return len;
    }
    UInt8 *encodeAttribute(UInt8 *dst)
    {
      dst = parameter::encodeAttribute(dst);
      dst = encode(dst, (UInt16)this->_value.size());
      for(std::set<std::string>::const_iterator it = _value.begin(); it != _value.end(); it++)
        dst = encode(dst, (UInt8 *)it->c_str(), it->size()+1);
      dst = encode(dst, (UInt32)_dimension);
      dst = encode(dst, (UInt16)_choices.size());
      for(unsigned int i = 0; i < _choices.size(); i++){
        dst = encode(dst, (UInt16)_choices[i].size());
        for(std::set<std::string>::const_iterator it = _choices[i].begin(); it != _choices[i].end(); it++)
          dst = encode(dst, (UInt8 *)it->c_str(), it->size()+1);
      }
      return dst;
    }
    UInt8 *parseAttribute(UInt8 *src, UInt32 len)
    {
      src = parameter::parseAttribute(src, len);
      UInt16 m = 0, n = 0;
      std::string value;
      src = parse(src, n);
      for(int i=0; i<n; i++) {
        src = parse(src, value, '\0');
      	_value.insert(value);
      }
      src = parse(src, *(UInt32 *)&_dimension);
      src = parse(src, n);
      _choices.resize(n);
      for(int i=0; i<n; i++) {
        src = parse(src, m);
        for(int j=0; j<m; j++) {
          src = parse(src, value, '\0');
          _choices[i].insert(value);
        }
      }
      return src;
    }
    void showAttribute() const {}
#endif

  };

  // The (possibly piece-wise defined on regions) function class. Functions are
  // entirely client-dependent: they are just represented internally as onelab
  // strings, defined on onelab regions.
  class function : public parameter{
  private:
    std::map<std::string, std::string> _value;
    std::vector<std::map<std::string, std::string> > _choices;
  public:
    function(const std::string &name="") : parameter(name, "", "") {}
    function(const std::string &name, const std::map<std::string, std::string> &value,
             const std::string &label="", const std::string &help="")
      : parameter(name, label, help), _value(value) {}
    void setValue(const std::map<std::string, std::string> &value)
    {
      _value = value;
    }
    void setChoices(const std::vector<std::map<std::string, std::string> > &choices)
    {
      _choices = choices;
    }
    std::string getType() const { return "function"; }
    const std::map<std::string, std::string> &getValue() const { return _value; }
    const std::string getValue(const std::string &region) const
    {
      std::map<std::string, std::string>::const_iterator it = _value.find(region);
      if(it != _value.end()) return it->second;
      return "";
    }
    const std::vector<std::map<std::string, std::string> > &getChoices() const
    {
      return _choices;
    }
    void update(const function &p)
    {
      addClients(p.getClients());
      setLabel(p.getLabel());
      setHelp(p.getHelp());
      setAttributes(p.getAttributes());
      if(p.getValue() != getValue()){
        setValue(p.getValue());
        setChanged(true);
      }
      setChoices(p.getChoices());
      if(getNeverChanged()) setChanged(false);
    }
    std::string toChar() const
    {
      std::ostringstream sstream;
      sstream << parameter::toChar() << _value.size() << charSep();
      for(std::map<std::string, std::string>::const_iterator it = _value.begin();
          it != _value.end(); it++)
        sstream << sanitize(it->first) << charSep()
                << sanitize(it->second) << charSep();
      sstream << _choices.size() << charSep();
      for(unsigned int i = 0; i < _choices.size(); i++){
        sstream << _choices[i].size() << charSep();
        for(std::map<std::string, std::string>::const_iterator it = _choices[i].begin();
            it != _choices[i].end(); it++)
          sstream << sanitize(it->first) << charSep()
                  << sanitize(it->second) << charSep();
      }
      return sstream.str();
    }
    std::string::size_type fromChar(const std::string &msg)
    {
      std::string::size_type pos = parameter::fromChar(msg);
      if(!pos) return 0;
      int n = atoi(getNextToken(msg, pos).c_str());
      for(int i = 0; i < n; i++){
        std::string key = getNextToken(msg, pos);
        _value[key] = getNextToken(msg, pos);
      }
      _choices.resize(atoi(getNextToken(msg, pos).c_str()));
      for(unsigned int i = 0; i < _choices.size(); i++){
        n = atoi(getNextToken(msg, pos).c_str());
        for(int i = 0; i < n; i++){
          std::string key = getNextToken(msg, pos);
          _choices[i][key] = getNextToken(msg, pos);
        }
      }
      return pos;
    }
#ifdef HAVE_ONELAB2
    static UInt16 attributeType() {return 0x09;}
    virtual inline UInt16 getAttributeType() const {return this->attributeType();}
    virtual inline UInt16 getAttributeLength() const {
      UInt16 len = parameter::getAttributeLength();
      len += 2;
      for(std::map<std::string, std::string>::const_iterator it = _value.begin();
          it != _value.end(); it++)
        len += 2+it->first.size()+it->second.size();
      for(unsigned int i = 0; i < _choices.size(); i++){
        len += 2;
        for(std::map<std::string, std::string>::const_iterator it = _choices[i].begin();
            it != _choices[i].end(); it++) {
          len += 2+it->first.size()+it->second.size();
        }
      }
      return len;
    }
    UInt8 *encodeAttribute(UInt8 *dst)
    {
      dst = parameter::encodeAttribute(dst),
      dst = encode(dst, (UInt16)this->_value.size());
      for(std::map<std::string, std::string>::const_iterator it = _value.begin();
          it != _value.end(); it++) {
        dst = encode(dst, (UInt8 *)it->first.c_str(), it->first.size()+1);
        dst = encode(dst, (UInt8 *)it->second.c_str(), it->second.size()+1);
      }
      dst = encode(dst, (UInt16)_choices.size());
      for(unsigned int i = 0; i < _choices.size(); i++){
        dst = encode(dst, (UInt16)_choices[i].size());
        for(std::map<std::string, std::string>::const_iterator it = _choices[i].begin();
            it != _choices[i].end(); it++) {
          dst = encode(dst, (UInt8 *)it->first.c_str(), it->first.size()+1);
          dst = encode(dst, (UInt8 *)it->second.c_str(), it->second.size()+1);
        }
      }
      return dst;
    }
    UInt8 *parseAttribute(UInt8 *src, UInt32 len)
    {
      src = parameter::parseAttribute(src, len);
      UInt16 m = 0, n = 0;
      std::string key, value;
      src = parse(src, n);
      for(int i=0; i<n; i++) {
        src = parse(src, key, '\0');
        src = parse(src, value, '\0');
      	_value[key] = value;
      }
      src = parse(src, n);
      _choices.resize(n);
      for(int i=0; i<n; i++) {
        src = parse(src, m);
        for(int j=0; j<m; j++) {
          src = parse(src, key, '\0');
          src = parse(src, value, '\0');
          _choices[i][key] = value;
        }
      }
      return src;
    }
    void showAttribute() const {}
#endif
  };

  // The parameter space, i.e., the set of parameters stored and handled by the
  // onelab server.
  class parameterSpace{
  private:
    std::set<number*, parameterLessThan> _numbers;
    std::set<string*, parameterLessThan> _strings;
    std::set<region*, parameterLessThan> _regions;
    std::set<function*, parameterLessThan> _functions;
    // delete a parameter from the parameter space
    template <class T> bool _clear(const std::string &name,
                                   const std::string &client,
                                   std::set<T*, parameterLessThan> &ps)
    {
      if(name.empty() && client.size()){
        for(typename std::set<T*, parameterLessThan>::iterator it = ps.begin();
            it != ps.end(); it++){
          T *p = *it;
          if(p->hasClient(client)){
            ps.erase(it);
            delete p;
          }
        }
      }
      else{
        T tmp(name);
        typename std::set<T*, parameterLessThan>::iterator it = ps.find(&tmp);
        if(it != ps.end()){
          T *p = *it;
          if(client.empty() || p->hasClient(client)){
            ps.erase(it);
            delete p;
            return true;
          }
        }
      }
      return false;
    }
    // set a parameter in the parameter space; if it already exists, update it
    // (adding new clients if necessary). This would need to be locked to avoid
    // race conditions when several clients try to set a parameter at the same
    // time.
    template <class T> bool _set(const T &p, const std::string &client,
                                 std::set<T*, parameterLessThan> &ps)
    {
      typename std::set<T*, parameterLessThan>::iterator it = ps.find((T*)&p);
      if(it != ps.end()){
        (*it)->update(p);
        if(client.size()) (*it)->addClient(client, true);
      }
      else{
        T* newp = new T(p);
#ifdef HAVE_ONELAB2
        newp->isInDatabase(true);
#endif
        if(client.size()) newp->addClient(client, true);
        ps.insert(newp);
      }
      return true;
    }
    // get the parameter matching the given name, or all the parameters in the
    // category if no name is given. If we find a given parameter by name, we
    // add the client requesting the parameter to the list of clients for this
    // parameter. This would also need to be locked.
    template <class T> bool _get(std::vector<T> &p, const std::string &name,
                                 const std::string &client,
                                 std::set<T*, parameterLessThan> &ps)
    {
      p.clear();
      if(name.empty()){
        for(typename std::set<T*, parameterLessThan>::iterator it = ps.begin();
            it != ps.end(); it++)
          p.push_back(**it);
      }
      else{
        T tmp(name);
        typename std::set<T*, parameterLessThan>::iterator it = ps.find(&tmp);
        if(it != ps.end()){
          if(client.size()) (*it)->addClient(client, true);
          p.push_back(**it);
        }
      }
      return true;
    }
    template <class T> T* _getPtr(std::string name, const std::string client, std::set<T*, parameterLessThan> ps)
    {
      T tmp(name);
      typename std::set<T*, parameterLessThan>::iterator it = ps.find(&tmp);
      if(it != ps.end()){
        if(client.size()) (*it)->addClient(client, true);
        return *it;
      }
      return NULL;
    }
    void _getAllParameters(std::set<parameter*, parameterLessThan> &ps) const
    {
      ps.insert(_numbers.begin(), _numbers.end());
      ps.insert(_strings.begin(), _strings.end());
      ps.insert(_regions.begin(), _regions.end());
      ps.insert(_functions.begin(), _functions.end());
    }
  public:
    parameterSpace(){}
    ~parameterSpace(){ clear(); }
    void clear(const std::string &name="", const std::string &client="")
    {
      if(name.empty() && client.empty()){
        std::set<parameter*, parameterLessThan> ps;
        _getAllParameters(ps);
        for(std::set<parameter*, parameterLessThan>::iterator it = ps.begin();
            it != ps.end(); it++)
          delete *it;
        _numbers.clear();
        _strings.clear();
        _regions.clear();
        _functions.clear();
      }
      else{
        bool done = _clear(name, client, _numbers);
        if(!done) done = _clear(name, client, _strings);
        if(!done) done = _clear(name, client, _regions);
        if(!done) done = _clear(name, client, _functions);
      }
    }
    bool set(const number &p,
             const std::string &client=""){ return _set(p, client, _numbers); }
    bool set(const string &p,
             const std::string &client=""){ return _set(p, client, _strings); }
    bool set(const region &p,
             const std::string &client=""){ return _set(p, client, _regions); }
    bool set(const function &p,
             const std::string &client=""){ return _set(p, client, _functions); }
    bool get(std::vector<number> &ps, const std::string &name="",
             const std::string &client=""){ return _get(ps, name, client, _numbers); }
    bool get(std::vector<onelab::string> &ps, const std::string &name="",
             const std::string &client=""){ return _get(ps, name, client, _strings); }
    bool get(std::vector<region> &ps, const std::string &name="",
             const std::string &client=""){ return _get(ps, name, client, _regions); }
    bool get(std::vector<function> &ps, const std::string &name="",
             const std::string &client=""){ return _get(ps, name, client, _functions); }
    void getPtr(number **ptr, const std::string name, const std::string client="")
      {*ptr = _getPtr(name, client, _numbers);}
    void getPtr(string **ptr, const std::string name, const std::string client="")
      {*ptr = _getPtr(name, client, _strings);}
    void getPtr(region **ptr, const std::string name, const std::string client="")
      {*ptr = _getPtr(name, client, _regions);}
    void getPtr(function **ptr, const std::string name, const std::string client="")
      {*ptr = _getPtr(name, client, _functions);}
    void getAllParameters(std::set<parameter*, parameterLessThan> &ps) const
    {
      ps.insert(_numbers.begin(), _numbers.end());
      ps.insert(_strings.begin(), _strings.end());
      ps.insert(_regions.begin(), _regions.end());
      ps.insert(_functions.begin(), _functions.end());
    }
    unsigned int getNumParameters()
    {
      return (int)(_numbers.size() + _strings.size() + _regions.size() + _functions.size());
    }
    // check if at least one parameter depends on the given client
    bool hasClient(const std::string &client) const
    {
      std::set<parameter*, parameterLessThan> ps;
      _getAllParameters(ps);
      for(std::set<parameter*, parameterLessThan>::iterator it = ps.begin();
          it != ps.end(); it++)
        if((*it)->hasClient(client)) return true;
      return false;
    }
    // check if some parameters have changed (optionnally only check the
    // parameters that depend on a given client)
    bool getChanged(const std::string &client="") const
    {
      std::set<parameter*, parameterLessThan> ps;
      _getAllParameters(ps);
      for(std::set<parameter*, parameterLessThan>::iterator it = ps.begin();
          it != ps.end(); it++){
        if((*it)->getChanged(client)){
          return true;
        }
      }
      return false;
    }
    // set the changed flag for all the parameters that depend on the given
    // client (or for all parameters if no client name is provided)
    void setChanged(bool changed, const std::string &client="")
    {
      std::set<parameter*, parameterLessThan> ps;
      _getAllParameters(ps);
      for(std::set<parameter*, parameterLessThan>::iterator it = ps.begin();
          it != ps.end(); it++)
        (*it)->setChanged(changed, client);
    }
    // serialize the parameter space (optionally only serialize those parameters
    // that depend on the given client)
    std::vector<std::string> toChar(const std::string &client="") const
    {
      std::vector<std::string> s;
      std::set<parameter*, parameterLessThan> ps;
      _getAllParameters(ps);
      for(std::set<parameter*, parameterLessThan>::const_iterator it = ps.begin();
          it != ps.end(); it++)
        if(client.empty() || (*it)->hasClient(client)){
	  if((*it)->getAttribute("NotInDb") != "True")
	    s.push_back((*it)->toChar());
	}
      return s;
    }
    // unserialize the parameter space
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
  };

  // The onelab client: a class that communicates with the onelab server. Each
  // client should be derived from this one. A client can be understood as "one
  // simulation step in a complex computation".
  class client{
  protected:
    // the name of the client
    std::string _name;
    // the id of the client, used to create a unique socket for this client
    int _id;
    // the index of the client in an external client list (if any)
    int _index;
  public:
    client(const std::string &name) : _name(name), _id(0), _index(-1){}
    virtual ~client(){}
    std::string getName(){ return _name; }
    void setId(int id){ _id = id; }
    int getId(){ return _id; }
    void setIndex(int index){ _index = index; }
    int getIndex(){ return _index; }
    virtual bool run(){ return false; }
    virtual bool isNetworkClient(){ return false; }
    virtual bool kill(){ return false; }
    virtual void sendInfo(const std::string &msg){ std::cout << msg << std::endl; }
    virtual void sendWarning(const std::string &msg){ std::cerr << msg << std::endl; }
    virtual void sendError(const std::string &msg){ std::cerr << msg << std::endl; }
    virtual void sendProgress(const std::string &msg){ std::cout << msg << std::endl; }
    virtual void sendMergeFileRequest(const std::string &msg){}
    virtual void sendOpenProjectRequest(const std::string &msg){}
    virtual void sendParseStringRequest(const std::string &msg){}
    virtual void sendVertexArray(const std::string &msg){}
    virtual bool clear(const std::string &name) = 0;
    virtual bool set(const number &p) = 0;
    virtual bool set(const string &p) = 0;
    virtual bool set(const region &p) = 0;
    virtual bool set(const function &p) = 0;
    virtual bool get(std::vector<number> &ps, const std::string &name="") = 0;
    virtual bool get(std::vector<onelab::string> &ps, const std::string &name="") = 0;
    virtual bool get(std::vector<region> &ps, const std::string &name="") = 0;
    virtual bool get(std::vector<function> &ps, const std::string &name="") = 0;
    std::vector<std::string> toChar()
    {
      std::vector<std::string> out;
      std::vector<number> n; get(n);
      for(unsigned int i = 0; i < n.size(); i++) out.push_back(n[i].toChar());
      std::vector<number> s; get(s);
      for(unsigned int i = 0; i < s.size(); i++) out.push_back(s[i].toChar());
      std::vector<region> r; get(r);
      for(unsigned int i = 0; i < r.size(); i++) out.push_back(r[i].toChar());
      std::vector<region> f; get(f);
      for(unsigned int i = 0; i < f.size(); i++) out.push_back(f[i].toChar());
      return out;
    }
    bool fromChar(const std::vector<std::string> &msg)
    {
      for(unsigned int i = 0; i < msg.size(); i++){
        std::string version, type, name;
        onelab::parameter::getInfoFromChar(msg[i], version, type, name);
        if(onelab::parameter::version() != version) return false;
        if(type == "number"){
          onelab::number p; p.fromChar(msg[i]); set(p);
        }
        else if(type == "string"){
          onelab::string p; p.fromChar(msg[i]); set(p);
        }
        else if(type == "region"){
          onelab::region p; p.fromChar(msg[i]); set(p);
        }
        else if(type == "function"){
          onelab::function p; p.fromChar(msg[i]); set(p);
        }
        else
          return false;
      }
      return true;
    }
    bool toFile(FILE *fp)
    {
      return parameter::toFile(toChar(), fp, getName());
    }
    bool fromFile(FILE *fp)
    {
      std::vector<std::string> msg;
      if(parameter::fromFile(msg, fp)) return fromChar(msg);
      return false;
    }
  };
  // The onelab server: a singleton that stores the parameter space and
  // interacts with onelab clients.
  class server{
  private:
    // the unique server (singleton behaviour due to the "static" specifier)
    static server *_server;
    // the address of the server
    std::string _address;
    // the connected clients, indexed by name
    std::map<std::string, client*> _clients;
    // the parameter space
    parameterSpace _parameterSpace;
  public:
    server(const std::string &address="") : _address(address) {}
    ~server(){}
    static server *instance(const std::string &address="")
    {
      if(!_server) _server = new server(address);
      return _server;
    }
    static void setInstance(server *s) { _server = s; }
    void clear(const std::string &name="", const std::string &client="")
    {
      _parameterSpace.clear(name, client);
    }
    template <class T> bool set(const T &p, const std::string &client="")
    {
      return _parameterSpace.set(p, client);
    }
    template <class T> bool get(std::vector<T> &ps, const std::string &name="",
                                const std::string &client="")
    {
      return _parameterSpace.get(ps, name, client);
    }
    typedef std::map<std::string, client*>::iterator citer;
    citer firstClient(){ return _clients.begin(); }
    citer lastClient(){ return _clients.end(); }
    int getNumClients() { return (int)_clients.size(); };
    citer findClient(const std::string &name){ return _clients.find(name); }
    void registerClient(client *c)
    {
      _clients[c->getName()] = c;
      c->setId(_clients.size());
    }
    void unregisterClient(client *c){ _clients.erase(c->getName()); }
    void setChanged(bool changed, const std::string &client="")
    {
      _parameterSpace.setChanged(changed, client);
    }
    bool getChanged(const std::string &client="")
    {
      return _parameterSpace.getChanged(client);
    }
    bool isRegistered(const std::string &client)
    {
      return _clients.count(client);
    }
    unsigned int getNumParameters(){ return _parameterSpace.getNumParameters(); }
    std::vector<std::string> toChar(const std::string &client="")
    {
      return _parameterSpace.toChar(client);
    }
    bool fromChar(const std::vector<std::string> &msg, const std::string &client="")
    {
      return _parameterSpace.fromChar(msg, client);
    }
    bool toFile(FILE *fp, const std::string &client="")
    {
      return parameter::toFile(toChar(client), fp, "onelab server");
    }
    bool fromFile(FILE *fp, const std::string &client="")
    {
      std::vector<std::string> msg;
      if(parameter::fromFile(msg, fp)) return fromChar(msg, client);
      return false;
    }
  };

  // A local client, which lives in the same memory space as the server.
  class localClient : public client{
  private:
    template <class T> bool _set(const T &p)
    {
      server::instance()->set(p, _name);
      return true;
    }
    template <class T> bool _get(std::vector<T> &ps,
                                 const std::string &name="")
    {
      server::instance()->get(ps, name, _name);
      return true;
    }
  public:
    localClient(const std::string &name) : client(name)
    {
      server::instance()->registerClient(this);
    }
    virtual ~localClient()
    {
      server::instance()->unregisterClient(this);
    }
    virtual bool clear(const std::string &name="")
    {
      server::instance()->clear(name);
      return true;
    }
    virtual bool set(const number &p){ return _set(p); }
    virtual bool set(const string &p){ return _set(p); }
    virtual bool set(const function &p){ return _set(p); }
    virtual bool set(const region &p){ return _set(p); }
    virtual bool get(std::vector<number> &ps,
                     const std::string &name=""){ return _get(ps, name); }
    virtual bool get(std::vector<onelab::string> &ps,
                     const std::string &name=""){ return _get(ps, name); }
    virtual bool get(std::vector<function> &ps,
                     const std::string &name=""){ return _get(ps, name); }
    virtual bool get(std::vector<region> &ps,
                     const std::string &name=""){ return _get(ps, name); }
  };

  // The local part of a network client.
  class localNetworkClient : public localClient{
  private:
    // executable of the client (including filesystem path, if necessary)
    std::string _executable;
    // treat the executable name as a full command line (will prevent the
    // escaping of the exe name, and will assume that the command line has been
    // correcly escaped)
    bool _treatExecutableAsFullCommandLine;
    // command to login to a remote host (if necessary)
    std::string _remoteLogin;
    // command line option to specify socket
    std::string _socketSwitch;
    // pid of the remote network client while it is running (-1 otherwise)
    int _pid;
    // underlying GmshServer
    GmshServer *_gmshServer;
  public:
    localNetworkClient(const std::string &name, const std::string &executable,
                       const std::string &remoteLogin="",
                       bool treatExecutableAsFullCommandLine=false)
      : localClient(name), _executable(executable),
        _treatExecutableAsFullCommandLine(treatExecutableAsFullCommandLine),
        _remoteLogin(remoteLogin), _socketSwitch("-onelab"), _pid(-1),
        _gmshServer(0) {}
    virtual ~localNetworkClient(){}
    virtual bool isNetworkClient(){ return true; }
    const std::string &getExecutable(){ return _executable; }
    void setExecutable(const std::string &s){ _executable = s; }
    const std::string &getRemoteLogin(){ return _remoteLogin; }
    const bool treatExecutableAsFullCommandLine()
    {
      return _treatExecutableAsFullCommandLine;
    }
    void setRemoteLogin(const std::string &s){ _remoteLogin = s; }
    const std::string &getSocketSwitch(){ return _socketSwitch; }
    void setSocketSwitch(const std::string &s){ _socketSwitch = s; }
    int getPid(){ return _pid; }
    void setPid(int pid){ _pid = pid; }
    GmshServer *getGmshServer(){ return _gmshServer; }
    void setGmshServer(GmshServer *server){ _gmshServer = server; }
    virtual bool run() = 0;
    virtual bool kill() = 0;
  };

  // The remote part of a network client.
  class remoteNetworkClient : public client{
  private:
    // address (inet:port or unix socket) of the server
    std::string _serverAddress;
    // underlying GmshClient
    GmshClient *_gmshClient;
    // number of subclients
    int _numSubClients;
    template <class T> bool _set(const T &p)
    {
      if(!_gmshClient) return false;
      std::string msg = p.toChar();
      _gmshClient->SendMessage(GmshSocket::GMSH_PARAMETER, msg.size(), &msg[0]);
      return true;
    }
    template <class T> bool _get(std::vector<T> &ps,
                                 const std::string &name="")
    {
      ps.clear();
      if(!_gmshClient) return false;
      T p(name);
      std::string msg = p.toChar();
      if (name.size())
	_gmshClient->SendMessage(GmshSocket::GMSH_PARAMETER_QUERY, msg.size(), &msg[0]);
      else // get all parameters
	_gmshClient->SendMessage(GmshSocket::GMSH_PARAMETER_QUERY_ALL, msg.size(), &msg[0]);

      while(1){
        // stop if we have no communications for 5 minutes
        int ret = _gmshClient->Select(500, 0);
        if(!ret){
          _gmshClient->Info("Timout: aborting remote get");
          return false;
        }
        else if(ret < 0){
          _gmshClient->Error("Error on select: aborting remote get");
          return false;
        }
        int type, length, swap;
        if(!_gmshClient->ReceiveHeader(&type, &length, &swap)){
          _gmshClient->Error("Did not receive message header: aborting remote get");
          return false;
        }
        std::string msg(length, ' ');
        if(!_gmshClient->ReceiveMessage(length, &msg[0])){
          _gmshClient->Error("Did not receive message body: aborting remote get");
          return false;
        }
        if(type == GmshSocket::GMSH_PARAMETER){
          T p;
          p.fromChar(msg);
          ps.push_back(p);
          return true;
        }
        if(type == GmshSocket::GMSH_PARAMETER_QUERY_ALL){
          T p;
          p.fromChar(msg);
          ps.push_back(p);
          // do NOT return until all parameters have been downloaded
        }
        else if(type == GmshSocket::GMSH_PARAMETER_QUERY_END){
	  // all parameters have been sent
          return true;
        }
        else if(type == GmshSocket::GMSH_PARAMETER_NOT_FOUND){
          // parameter not found
          return true;
        }
        else if(type == GmshSocket::GMSH_INFO){
          return true;
        }
        else{
          _gmshClient->Error("Unknown message type: aborting remote get");
          return false;
        }
      }
      return true;
    }
  public:
    void waitOnSubClients()
    {
      if(!_gmshClient) return;
      while(_numSubClients > 0){
        int ret = _gmshClient->Select(500, 0);
        if(!ret){
          _gmshClient->Info("Timout: aborting wait on subclients");
          return;
        }
        else if(ret < 0){
          _gmshClient->Error("Error on select: aborting wait on subclients");
          return;
        }
        int type, length, swap;
        if(!_gmshClient->ReceiveHeader(&type, &length, &swap)){
          _gmshClient->Error("Did not receive message header: aborting wait on subclients");
          return;
        }
        std::string msg(length, ' ');
        if(!_gmshClient->ReceiveMessage(length, &msg[0])){
          _gmshClient->Error("Did not receive message body: aborting wait on subclients");
          return;
        }
        if(type == GmshSocket::GMSH_STOP)
          _numSubClients -= 1;
      }
    }
  public:
    remoteNetworkClient(const std::string &name, const std::string &serverAddress)
      : client(name), _serverAddress(serverAddress), _numSubClients(0)
    {
      _gmshClient = new GmshClient();
      if(_gmshClient->Connect(_serverAddress.c_str()) < 0){
        delete _gmshClient;
        _gmshClient = 0;
      }
      else{
        _gmshClient->Start();
      }
    }
    virtual ~remoteNetworkClient()
    {
      if(_gmshClient){
        waitOnSubClients();
        _gmshClient->Stop();
        _gmshClient->Disconnect();
        delete _gmshClient;
        _gmshClient = 0;
      }
    }
    GmshClient *getGmshClient(){ return _gmshClient; }
    virtual bool isNetworkClient(){ return true; }
    virtual bool clear(const std::string &name="")
    {
      if(!_gmshClient) return false;
      std::string msg = name;
      if(msg.empty()) msg = "*";
      _gmshClient->SendMessage(GmshSocket::GMSH_PARAMETER_CLEAR, msg.size(), &msg[0]);
      return true;
    }
    virtual bool set(const number &p){ return _set(p); }
    virtual bool set(const string &p){ return _set(p); }
    virtual bool set(const function &p){ return _set(p); }
    virtual bool set(const region &p){ return _set(p); }
    virtual bool get(std::vector<number> &ps,
                     const std::string &name=""){ return _get(ps, name); }
    virtual bool get(std::vector<onelab::string> &ps,
                     const std::string &name=""){ return _get(ps, name); }
    virtual bool get(std::vector<function> &ps,
                     const std::string &name=""){ return _get(ps, name); }
    virtual bool get(std::vector<region> &ps,
                     const std::string &name=""){ return _get(ps, name); }
    void sendInfo(const std::string &msg)
    {
      if(_gmshClient) _gmshClient->Info(msg.c_str());
    }
    void sendWarning(const std::string &msg)
    {
      if(_gmshClient) _gmshClient->Warning(msg.c_str());
    }
    void sendError(const std::string &msg)
    {
      if(_gmshClient) _gmshClient->Error(msg.c_str());
    }
    void sendProgress(const std::string &msg)
    {
      if(_gmshClient) _gmshClient->Progress(msg.c_str());
    }
    void sendMergeFileRequest(const std::string &msg)
    {
      if(_gmshClient) _gmshClient->MergeFile(msg.c_str());
    }
    void sendOpenProjectRequest(const std::string &msg)
    {
      if(_gmshClient) _gmshClient->OpenProject(msg.c_str());
    }
    void sendParseStringRequest(const std::string &msg)
    {
      if(_gmshClient) _gmshClient->ParseString(msg.c_str());
    }
    void runNonBlockingSubClient(const std::string &name, const std::string &command)
    {
      if(!_gmshClient){
        system(command.c_str());
        return;
      }
      std::string msg = name + parameter::charSep() + command;
      _gmshClient->SendMessage(GmshSocket::GMSH_CONNECT, msg.size(), &msg[0]);
      _numSubClients += 1;
    }
    void runSubClient(const std::string &name, const std::string &command)
    {
      runNonBlockingSubClient(name, command);
      waitOnSubClients();
    }
  };

}

#endif
