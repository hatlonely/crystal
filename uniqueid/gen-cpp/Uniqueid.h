/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Uniqueid_H
#define Uniqueid_H

#include <thrift/TDispatchProcessor.h>
#include "uniqueid_types.h"

namespace uniqueid {

class UniqueidIf {
 public:
  virtual ~UniqueidIf() {}
  virtual void uniqueid(UniqueidResponse& _return, const int32_t logid, const UniqueidRequest& request) = 0;
};

class UniqueidIfFactory {
 public:
  typedef UniqueidIf Handler;

  virtual ~UniqueidIfFactory() {}

  virtual UniqueidIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(UniqueidIf* /* handler */) = 0;
};

class UniqueidIfSingletonFactory : virtual public UniqueidIfFactory {
 public:
  UniqueidIfSingletonFactory(const boost::shared_ptr<UniqueidIf>& iface) : iface_(iface) {}
  virtual ~UniqueidIfSingletonFactory() {}

  virtual UniqueidIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(UniqueidIf* /* handler */) {}

 protected:
  boost::shared_ptr<UniqueidIf> iface_;
};

class UniqueidNull : virtual public UniqueidIf {
 public:
  virtual ~UniqueidNull() {}
  void uniqueid(UniqueidResponse& /* _return */, const int32_t /* logid */, const UniqueidRequest& /* request */) {
    return;
  }
};

typedef struct _Uniqueid_uniqueid_args__isset {
  _Uniqueid_uniqueid_args__isset() : logid(false), request(false) {}
  bool logid :1;
  bool request :1;
} _Uniqueid_uniqueid_args__isset;

class Uniqueid_uniqueid_args {
 public:

  static const char* ascii_fingerprint; // = "3E4EA75EE4645FBC17071FF4F3229B0A";
  static const uint8_t binary_fingerprint[16]; // = {0x3E,0x4E,0xA7,0x5E,0xE4,0x64,0x5F,0xBC,0x17,0x07,0x1F,0xF4,0xF3,0x22,0x9B,0x0A};

  Uniqueid_uniqueid_args(const Uniqueid_uniqueid_args&);
  Uniqueid_uniqueid_args& operator=(const Uniqueid_uniqueid_args&);
  Uniqueid_uniqueid_args() : logid(0) {
  }

  virtual ~Uniqueid_uniqueid_args() throw();
  int32_t logid;
  UniqueidRequest request;

  _Uniqueid_uniqueid_args__isset __isset;

  void __set_logid(const int32_t val);

  void __set_request(const UniqueidRequest& val);

  bool operator == (const Uniqueid_uniqueid_args & rhs) const
  {
    if (!(logid == rhs.logid))
      return false;
    if (!(request == rhs.request))
      return false;
    return true;
  }
  bool operator != (const Uniqueid_uniqueid_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Uniqueid_uniqueid_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const Uniqueid_uniqueid_args& obj);
};


class Uniqueid_uniqueid_pargs {
 public:

  static const char* ascii_fingerprint; // = "3E4EA75EE4645FBC17071FF4F3229B0A";
  static const uint8_t binary_fingerprint[16]; // = {0x3E,0x4E,0xA7,0x5E,0xE4,0x64,0x5F,0xBC,0x17,0x07,0x1F,0xF4,0xF3,0x22,0x9B,0x0A};


  virtual ~Uniqueid_uniqueid_pargs() throw();
  const int32_t* logid;
  const UniqueidRequest* request;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const Uniqueid_uniqueid_pargs& obj);
};

typedef struct _Uniqueid_uniqueid_result__isset {
  _Uniqueid_uniqueid_result__isset() : success(false), ue(false) {}
  bool success :1;
  bool ue :1;
} _Uniqueid_uniqueid_result__isset;

class Uniqueid_uniqueid_result {
 public:

  static const char* ascii_fingerprint; // = "E238ED6C5E48CB3196BE244BF1D5587F";
  static const uint8_t binary_fingerprint[16]; // = {0xE2,0x38,0xED,0x6C,0x5E,0x48,0xCB,0x31,0x96,0xBE,0x24,0x4B,0xF1,0xD5,0x58,0x7F};

  Uniqueid_uniqueid_result(const Uniqueid_uniqueid_result&);
  Uniqueid_uniqueid_result& operator=(const Uniqueid_uniqueid_result&);
  Uniqueid_uniqueid_result() {
  }

  virtual ~Uniqueid_uniqueid_result() throw();
  UniqueidResponse success;
  UniqueidException ue;

  _Uniqueid_uniqueid_result__isset __isset;

  void __set_success(const UniqueidResponse& val);

  void __set_ue(const UniqueidException& val);

  bool operator == (const Uniqueid_uniqueid_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(ue == rhs.ue))
      return false;
    return true;
  }
  bool operator != (const Uniqueid_uniqueid_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Uniqueid_uniqueid_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const Uniqueid_uniqueid_result& obj);
};

typedef struct _Uniqueid_uniqueid_presult__isset {
  _Uniqueid_uniqueid_presult__isset() : success(false), ue(false) {}
  bool success :1;
  bool ue :1;
} _Uniqueid_uniqueid_presult__isset;

class Uniqueid_uniqueid_presult {
 public:

  static const char* ascii_fingerprint; // = "E238ED6C5E48CB3196BE244BF1D5587F";
  static const uint8_t binary_fingerprint[16]; // = {0xE2,0x38,0xED,0x6C,0x5E,0x48,0xCB,0x31,0x96,0xBE,0x24,0x4B,0xF1,0xD5,0x58,0x7F};


  virtual ~Uniqueid_uniqueid_presult() throw();
  UniqueidResponse* success;
  UniqueidException ue;

  _Uniqueid_uniqueid_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const Uniqueid_uniqueid_presult& obj);
};

class UniqueidClient : virtual public UniqueidIf {
 public:
  UniqueidClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  UniqueidClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void uniqueid(UniqueidResponse& _return, const int32_t logid, const UniqueidRequest& request);
  void send_uniqueid(const int32_t logid, const UniqueidRequest& request);
  void recv_uniqueid(UniqueidResponse& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class UniqueidProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<UniqueidIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (UniqueidProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_uniqueid(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  UniqueidProcessor(boost::shared_ptr<UniqueidIf> iface) :
    iface_(iface) {
    processMap_["uniqueid"] = &UniqueidProcessor::process_uniqueid;
  }

  virtual ~UniqueidProcessor() {}
};

class UniqueidProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  UniqueidProcessorFactory(const ::boost::shared_ptr< UniqueidIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< UniqueidIfFactory > handlerFactory_;
};

class UniqueidMultiface : virtual public UniqueidIf {
 public:
  UniqueidMultiface(std::vector<boost::shared_ptr<UniqueidIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~UniqueidMultiface() {}
 protected:
  std::vector<boost::shared_ptr<UniqueidIf> > ifaces_;
  UniqueidMultiface() {}
  void add(boost::shared_ptr<UniqueidIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void uniqueid(UniqueidResponse& _return, const int32_t logid, const UniqueidRequest& request) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->uniqueid(_return, logid, request);
    }
    ifaces_[i]->uniqueid(_return, logid, request);
    return;
  }

};

} // namespace

#endif
