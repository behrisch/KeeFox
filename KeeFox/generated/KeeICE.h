// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.0
// Generated from file `KeeICE.ice'

#ifndef __C__development_KeeFox_KeeFox_generated_KeeICE_h__
#define __C__development_KeeFox_KeeFox_generated_KeeICE_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/UserExceptionFactory.h>
#include <Ice/FactoryTable.h>
#include <Ice/StreamF.h>
#include <Ice/Identity.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 303
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace KeeICE
{

namespace KFlib
{

class KPGroup;

class KP;

class CallbackReceiver;

}

}

}

namespace KeeICE
{

namespace KFlib
{

class KPGroup;
bool operator==(const KPGroup&, const KPGroup&);
bool operator<(const KPGroup&, const KPGroup&);

class KP;
bool operator==(const KP&, const KP&);
bool operator<(const KP&, const KP&);

class CallbackReceiver;
bool operator==(const CallbackReceiver&, const CallbackReceiver&);
bool operator<(const CallbackReceiver&, const CallbackReceiver&);

}

}

namespace IceInternal
{

::Ice::Object* upCast(::KeeICE::KFlib::KPGroup*);
::IceProxy::Ice::Object* upCast(::IceProxy::KeeICE::KFlib::KPGroup*);

::Ice::Object* upCast(::KeeICE::KFlib::KP*);
::IceProxy::Ice::Object* upCast(::IceProxy::KeeICE::KFlib::KP*);

::Ice::Object* upCast(::KeeICE::KFlib::CallbackReceiver*);
::IceProxy::Ice::Object* upCast(::IceProxy::KeeICE::KFlib::CallbackReceiver*);

}

namespace KeeICE
{

namespace KFlib
{

typedef ::IceInternal::Handle< ::KeeICE::KFlib::KPGroup> KPGroupPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::KeeICE::KFlib::KPGroup> KPGroupPrx;

void __read(::IceInternal::BasicStream*, KPGroupPrx&);
void __patch__KPGroupPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::KeeICE::KFlib::KP> KPPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::KeeICE::KFlib::KP> KPPrx;

void __read(::IceInternal::BasicStream*, KPPrx&);
void __patch__KPPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::KeeICE::KFlib::CallbackReceiver> CallbackReceiverPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::KeeICE::KFlib::CallbackReceiver> CallbackReceiverPrx;

void __read(::IceInternal::BasicStream*, CallbackReceiverPrx&);
void __patch__CallbackReceiverPtr(void*, ::Ice::ObjectPtr&);

}

}

namespace KeeICE
{

namespace KFlib
{

enum loginSearchType
{
    LSTall,
    LSTnoForms,
    LSTnoRealms
};

void __write(::IceInternal::BasicStream*, loginSearchType);
void __read(::IceInternal::BasicStream*, loginSearchType&);

enum formFieldType
{
    FFTradio,
    FFTusername,
    FFTtext,
    FFTpassword,
    FFTselect,
    FFTcheckbox
};

void __write(::IceInternal::BasicStream*, formFieldType);
void __read(::IceInternal::BasicStream*, formFieldType&);

struct KPFormField
{
    ::std::string name;
    ::std::string displayName;
    ::std::string value;
    ::KeeICE::KFlib::formFieldType type;

    bool operator==(const KPFormField&) const;
    bool operator<(const KPFormField&) const;
    bool operator!=(const KPFormField& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const KPFormField& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const KPFormField& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const KPFormField& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::KeeICE::KFlib::KPFormField> KPFormFieldList;
void __writeKPFormFieldList(::IceInternal::BasicStream*, const ::KeeICE::KFlib::KPFormField*, const ::KeeICE::KFlib::KPFormField*);
void __readKPFormFieldList(::IceInternal::BasicStream*, KPFormFieldList&);

struct KPEntry
{
    ::std::string hostName;
    ::std::string formURL;
    ::std::string HTTPRealm;
    ::std::string title;
    ::KeeICE::KFlib::KPFormFieldList formFieldList;
    bool _cpp_default;
    bool exactMatch;

    bool operator==(const KPEntry&) const;
    bool operator<(const KPEntry&) const;
    bool operator!=(const KPEntry& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const KPEntry& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const KPEntry& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const KPEntry& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::KeeICE::KFlib::KPEntry> KPEntryList;
void __writeKPEntryList(::IceInternal::BasicStream*, const ::KeeICE::KFlib::KPEntry*, const ::KeeICE::KFlib::KPEntry*);
void __readKPEntryList(::IceInternal::BasicStream*, KPEntryList&);

class KeeICEException : public ::Ice::UserException
{
public:

    KeeICEException() {}
    explicit KeeICEException(const ::std::string&);
    virtual ~KeeICEException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    ::std::string reason;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

static KeeICEException __KeeICEException_init;

struct KPDatabase
{
    ::std::string DBname;
    ::std::string fileName;
    bool _cpp_default;
    ::std::string rootGroupUID;
    bool useILM;

    bool operator==(const KPDatabase&) const;
    bool operator<(const KPDatabase&) const;
    bool operator!=(const KPDatabase& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const KPDatabase& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const KPDatabase& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const KPDatabase& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::KeeICE::KFlib::KPDatabase> KPDatabaseList;
void __writeKPDatabaseList(::IceInternal::BasicStream*, const ::KeeICE::KFlib::KPDatabase*, const ::KeeICE::KFlib::KPDatabase*);
void __readKPDatabaseList(::IceInternal::BasicStream*, KPDatabaseList&);

struct KFConfiguration
{
    bool allowUnencryptedMetaData;
    ::KeeICE::KFlib::KPDatabaseList knownDatabases;

    bool operator==(const KFConfiguration&) const;
    bool operator<(const KFConfiguration&) const;
    bool operator!=(const KFConfiguration& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const KFConfiguration& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const KFConfiguration& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const KFConfiguration& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

}

}

namespace IceProxy
{

namespace KeeICE
{

namespace KFlib
{

class KPGroup : virtual public ::IceProxy::Ice::Object
{
public:

    void Touch(bool isModified)
    {
        Touch(isModified, 0);
    }
    void Touch(bool isModified, const ::Ice::Context& __ctx)
    {
        Touch(isModified, &__ctx);
    }
    
private:

    void Touch(bool, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<KPGroup> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KPGroup> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KPGroup*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<KPGroup*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class KP : virtual public ::IceProxy::Ice::Object
{
public:

    bool checkVersion(::Ice::Float keeFoxVersion, ::Ice::Float keeICEVersion, ::Ice::Int& result)
    {
        return checkVersion(keeFoxVersion, keeICEVersion, result, 0);
    }
    bool checkVersion(::Ice::Float keeFoxVersion, ::Ice::Float keeICEVersion, ::Ice::Int& result, const ::Ice::Context& __ctx)
    {
        return checkVersion(keeFoxVersion, keeICEVersion, result, &__ctx);
    }
    
private:

    bool checkVersion(::Ice::Float, ::Ice::Float, ::Ice::Int&, const ::Ice::Context*);
    
public:

    ::std::string getDatabaseName()
    {
        return getDatabaseName(0);
    }
    ::std::string getDatabaseName(const ::Ice::Context& __ctx)
    {
        return getDatabaseName(&__ctx);
    }
    
private:

    ::std::string getDatabaseName(const ::Ice::Context*);
    
public:

    void AddLogin(const ::KeeICE::KFlib::KPEntry& login)
    {
        AddLogin(login, 0);
    }
    void AddLogin(const ::KeeICE::KFlib::KPEntry& login, const ::Ice::Context& __ctx)
    {
        AddLogin(login, &__ctx);
    }
    
private:

    void AddLogin(const ::KeeICE::KFlib::KPEntry&, const ::Ice::Context*);
    
public:

    void ModifyLogin(const ::KeeICE::KFlib::KPEntry& oldLogin, const ::KeeICE::KFlib::KPEntry& newLogin)
    {
        ModifyLogin(oldLogin, newLogin, 0);
    }
    void ModifyLogin(const ::KeeICE::KFlib::KPEntry& oldLogin, const ::KeeICE::KFlib::KPEntry& newLogin, const ::Ice::Context& __ctx)
    {
        ModifyLogin(oldLogin, newLogin, &__ctx);
    }
    
private:

    void ModifyLogin(const ::KeeICE::KFlib::KPEntry&, const ::KeeICE::KFlib::KPEntry&, const ::Ice::Context*);
    
public:

    ::Ice::Int getAllLogins(::KeeICE::KFlib::KPEntryList& logins)
    {
        return getAllLogins(logins, 0);
    }
    ::Ice::Int getAllLogins(::KeeICE::KFlib::KPEntryList& logins, const ::Ice::Context& __ctx)
    {
        return getAllLogins(logins, &__ctx);
    }
    
private:

    ::Ice::Int getAllLogins(::KeeICE::KFlib::KPEntryList&, const ::Ice::Context*);
    
public:

    ::Ice::Int findLogins(const ::std::string& hostname, const ::std::string& actionURL, const ::std::string& httpRealm, ::KeeICE::KFlib::loginSearchType lst, bool requireFullURLMatches, ::KeeICE::KFlib::KPEntryList& logins)
    {
        return findLogins(hostname, actionURL, httpRealm, lst, requireFullURLMatches, logins, 0);
    }
    ::Ice::Int findLogins(const ::std::string& hostname, const ::std::string& actionURL, const ::std::string& httpRealm, ::KeeICE::KFlib::loginSearchType lst, bool requireFullURLMatches, ::KeeICE::KFlib::KPEntryList& logins, const ::Ice::Context& __ctx)
    {
        return findLogins(hostname, actionURL, httpRealm, lst, requireFullURLMatches, logins, &__ctx);
    }
    
private:

    ::Ice::Int findLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, ::KeeICE::KFlib::KPEntryList&, const ::Ice::Context*);
    
public:

    ::Ice::Int countLogins(const ::std::string& hostname, const ::std::string& actionURL, const ::std::string& httpRealm, ::KeeICE::KFlib::loginSearchType lst, bool requireFullURLMatches)
    {
        return countLogins(hostname, actionURL, httpRealm, lst, requireFullURLMatches, 0);
    }
    ::Ice::Int countLogins(const ::std::string& hostname, const ::std::string& actionURL, const ::std::string& httpRealm, ::KeeICE::KFlib::loginSearchType lst, bool requireFullURLMatches, const ::Ice::Context& __ctx)
    {
        return countLogins(hostname, actionURL, httpRealm, lst, requireFullURLMatches, &__ctx);
    }
    
private:

    ::Ice::Int countLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, const ::Ice::Context*);
    
public:

    void addClient(const ::Ice::Identity& ident)
    {
        addClient(ident, 0);
    }
    void addClient(const ::Ice::Identity& ident, const ::Ice::Context& __ctx)
    {
        addClient(ident, &__ctx);
    }
    
private:

    void addClient(const ::Ice::Identity&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<KP> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<KP> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<KP*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<KP*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class CallbackReceiver : virtual public ::IceProxy::Ice::Object
{
public:

    void callback(::Ice::Int num)
    {
        callback(num, 0);
    }
    void callback(::Ice::Int num, const ::Ice::Context& __ctx)
    {
        callback(num, &__ctx);
    }
    
private:

    void callback(::Ice::Int, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CallbackReceiver> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CallbackReceiver*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<CallbackReceiver*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

}

namespace IceDelegate
{

namespace KeeICE
{

namespace KFlib
{

class KPGroup : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void Touch(bool, const ::Ice::Context*) = 0;
};

class KP : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool checkVersion(::Ice::Float, ::Ice::Float, ::Ice::Int&, const ::Ice::Context*) = 0;

    virtual ::std::string getDatabaseName(const ::Ice::Context*) = 0;

    virtual void AddLogin(const ::KeeICE::KFlib::KPEntry&, const ::Ice::Context*) = 0;

    virtual void ModifyLogin(const ::KeeICE::KFlib::KPEntry&, const ::KeeICE::KFlib::KPEntry&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int getAllLogins(::KeeICE::KFlib::KPEntryList&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int findLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, ::KeeICE::KFlib::KPEntryList&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int countLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, const ::Ice::Context*) = 0;

    virtual void addClient(const ::Ice::Identity&, const ::Ice::Context*) = 0;
};

class CallbackReceiver : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void callback(::Ice::Int, const ::Ice::Context*) = 0;
};

}

}

}

namespace IceDelegateM
{

namespace KeeICE
{

namespace KFlib
{

class KPGroup : virtual public ::IceDelegate::KeeICE::KFlib::KPGroup,
                virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void Touch(bool, const ::Ice::Context*);
};

class KP : virtual public ::IceDelegate::KeeICE::KFlib::KP,
           virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool checkVersion(::Ice::Float, ::Ice::Float, ::Ice::Int&, const ::Ice::Context*);

    virtual ::std::string getDatabaseName(const ::Ice::Context*);

    virtual void AddLogin(const ::KeeICE::KFlib::KPEntry&, const ::Ice::Context*);

    virtual void ModifyLogin(const ::KeeICE::KFlib::KPEntry&, const ::KeeICE::KFlib::KPEntry&, const ::Ice::Context*);

    virtual ::Ice::Int getAllLogins(::KeeICE::KFlib::KPEntryList&, const ::Ice::Context*);

    virtual ::Ice::Int findLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, ::KeeICE::KFlib::KPEntryList&, const ::Ice::Context*);

    virtual ::Ice::Int countLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, const ::Ice::Context*);

    virtual void addClient(const ::Ice::Identity&, const ::Ice::Context*);
};

class CallbackReceiver : virtual public ::IceDelegate::KeeICE::KFlib::CallbackReceiver,
                         virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void callback(::Ice::Int, const ::Ice::Context*);
};

}

}

}

namespace IceDelegateD
{

namespace KeeICE
{

namespace KFlib
{

class KPGroup : virtual public ::IceDelegate::KeeICE::KFlib::KPGroup,
                virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void Touch(bool, const ::Ice::Context*);
};

class KP : virtual public ::IceDelegate::KeeICE::KFlib::KP,
           virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool checkVersion(::Ice::Float, ::Ice::Float, ::Ice::Int&, const ::Ice::Context*);

    virtual ::std::string getDatabaseName(const ::Ice::Context*);

    virtual void AddLogin(const ::KeeICE::KFlib::KPEntry&, const ::Ice::Context*);

    virtual void ModifyLogin(const ::KeeICE::KFlib::KPEntry&, const ::KeeICE::KFlib::KPEntry&, const ::Ice::Context*);

    virtual ::Ice::Int getAllLogins(::KeeICE::KFlib::KPEntryList&, const ::Ice::Context*);

    virtual ::Ice::Int findLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, ::KeeICE::KFlib::KPEntryList&, const ::Ice::Context*);

    virtual ::Ice::Int countLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, const ::Ice::Context*);

    virtual void addClient(const ::Ice::Identity&, const ::Ice::Context*);
};

class CallbackReceiver : virtual public ::IceDelegate::KeeICE::KFlib::CallbackReceiver,
                         virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void callback(::Ice::Int, const ::Ice::Context*);
};

}

}

}

namespace KeeICE
{

namespace KFlib
{

class KPGroup : virtual public ::Ice::Object
{
public:

    typedef KPGroupPrx ProxyType;
    typedef KPGroupPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void Touch(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___Touch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class KP : virtual public ::Ice::Object
{
public:

    typedef KPPrx ProxyType;
    typedef KPPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool checkVersion(::Ice::Float, ::Ice::Float, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___checkVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string getDatabaseName(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___getDatabaseName(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void AddLogin(const ::KeeICE::KFlib::KPEntry&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___AddLogin(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void ModifyLogin(const ::KeeICE::KFlib::KPEntry&, const ::KeeICE::KFlib::KPEntry&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___ModifyLogin(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int getAllLogins(::KeeICE::KFlib::KPEntryList&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___getAllLogins(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int findLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, ::KeeICE::KFlib::KPEntryList&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___findLogins(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int countLogins(const ::std::string&, const ::std::string&, const ::std::string&, ::KeeICE::KFlib::loginSearchType, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___countLogins(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void addClient(const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___addClient(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class CallbackReceiver : virtual public ::Ice::Object
{
public:

    typedef CallbackReceiverPrx ProxyType;
    typedef CallbackReceiverPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void callback(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___callback(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

}

#endif
