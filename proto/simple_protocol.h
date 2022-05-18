//------------------------------------------------------------------------------
// Automatically generated by the Fast Binary Encoding compiler, do not modify!
// https://github.com/chronoxor/FastBinaryEncoding
// Source: simple.fbe
// FBE version: 1.9.0.0
//------------------------------------------------------------------------------

#pragma once

#if defined(__clang__)
#pragma clang system_header
#elif defined(__GNUC__)
#pragma GCC system_header
#elif defined(_MSC_VER)
#pragma system_header
#endif

#include "fbe_protocol.h"

#include "simple_models.h"

namespace FBE {

namespace simple {

// Fast Binary Encoding simple protocol version
struct ProtocolVersion
{
    // Protocol major version
    static const int major = 1;
    // Protocol minor version
    static const int minor = 0;
};

// Fast Binary Encoding simple sender
class Sender : public virtual FBE::Sender
{
public:
    Sender()
        : SimpleRequestModel(this->_buffer)
        , SimpleResponseModel(this->_buffer)
        , SimpleRejectModel(this->_buffer)
        , SimpleNotifyModel(this->_buffer)
        , DisconnectRequestModel(this->_buffer)
    {}
    Sender(const Sender&) = delete;
    Sender(Sender&&) noexcept = delete;
    virtual ~Sender() = default;

    Sender& operator=(const Sender&) = delete;
    Sender& operator=(Sender&&) noexcept = delete;

    size_t send(const ::simple::SimpleRequest& value);
    size_t send(const ::simple::SimpleResponse& value);
    size_t send(const ::simple::SimpleReject& value);
    size_t send(const ::simple::SimpleNotify& value);
    size_t send(const ::simple::DisconnectRequest& value);

public:
    // Sender models accessors
    FBE::simple::SimpleRequestModel SimpleRequestModel;
    FBE::simple::SimpleResponseModel SimpleResponseModel;
    FBE::simple::SimpleRejectModel SimpleRejectModel;
    FBE::simple::SimpleNotifyModel SimpleNotifyModel;
    FBE::simple::DisconnectRequestModel DisconnectRequestModel;
};

// Fast Binary Encoding simple receiver
class Receiver : public virtual FBE::Receiver
{
public:
    Receiver() {}
    Receiver(const Receiver&) = delete;
    Receiver(Receiver&&) = delete;
    virtual ~Receiver() = default;

    Receiver& operator=(const Receiver&) = delete;
    Receiver& operator=(Receiver&&) = delete;

protected:
    // Receive handlers
    virtual void onReceive(const ::simple::SimpleRequest& value) {}
    virtual void onReceive(const ::simple::SimpleResponse& value) {}
    virtual void onReceive(const ::simple::SimpleReject& value) {}
    virtual void onReceive(const ::simple::SimpleNotify& value) {}
    virtual void onReceive(const ::simple::DisconnectRequest& value) {}

    // Receive message handler
    bool onReceive(size_t type, const void* data, size_t size) override;

private:
    // Receiver values accessors
    ::simple::SimpleRequest SimpleRequestValue;
    ::simple::SimpleResponse SimpleResponseValue;
    ::simple::SimpleReject SimpleRejectValue;
    ::simple::SimpleNotify SimpleNotifyValue;
    ::simple::DisconnectRequest DisconnectRequestValue;

    // Receiver models accessors
    FBE::simple::SimpleRequestModel SimpleRequestModel;
    FBE::simple::SimpleResponseModel SimpleResponseModel;
    FBE::simple::SimpleRejectModel SimpleRejectModel;
    FBE::simple::SimpleNotifyModel SimpleNotifyModel;
    FBE::simple::DisconnectRequestModel DisconnectRequestModel;
};

// Fast Binary Encoding simple proxy
class Proxy : public virtual FBE::Receiver
{
public:
    Proxy() {}
    Proxy(const Proxy&) = delete;
    Proxy(Proxy&&) = delete;
    virtual ~Proxy() = default;

    Proxy& operator=(const Proxy&) = delete;
    Proxy& operator=(Proxy&&) = delete;

protected:
    // Proxy handlers
    virtual void onProxy(FBE::simple::SimpleRequestModel& model, size_t type, const void* data, size_t size) {}
    virtual void onProxy(FBE::simple::SimpleResponseModel& model, size_t type, const void* data, size_t size) {}
    virtual void onProxy(FBE::simple::SimpleRejectModel& model, size_t type, const void* data, size_t size) {}
    virtual void onProxy(FBE::simple::SimpleNotifyModel& model, size_t type, const void* data, size_t size) {}
    virtual void onProxy(FBE::simple::DisconnectRequestModel& model, size_t type, const void* data, size_t size) {}

    // Receive message handler
    bool onReceive(size_t type, const void* data, size_t size) override;

private:
    // Proxy models accessors
    FBE::simple::SimpleRequestModel SimpleRequestModel;
    FBE::simple::SimpleResponseModel SimpleResponseModel;
    FBE::simple::SimpleRejectModel SimpleRejectModel;
    FBE::simple::SimpleNotifyModel SimpleNotifyModel;
    FBE::simple::DisconnectRequestModel DisconnectRequestModel;
};

// Fast Binary Encoding simple client
class Client : public virtual Sender, protected virtual Receiver
{
public:
    Client() = default;
    Client(const Client&) = delete;
    Client(Client&&) = delete;
    virtual ~Client() = default;

    Client& operator=(const Client&) = delete;
    Client& operator=(Client&&) = delete;

    // Reset client buffers
    void reset() { std::scoped_lock locker(this->_lock); reset_requests(); }

    // Watchdog for timeouts
    void watchdog(uint64_t utc) { std::scoped_lock locker(this->_lock); watchdog_requests(utc); }

    std::future<::simple::SimpleResponse> request(const ::simple::SimpleRequest& value, size_t timeout = 0);
    std::future<void> request(const ::simple::DisconnectRequest& value, size_t timeout = 0);

protected:
    std::mutex _lock;
    uint64_t _timestamp{0};

    virtual bool onReceiveResponse(const ::simple::SimpleResponse& response);

    virtual bool onReceiveResponse(const ::simple::SimpleRequest& response) { return false; }
    virtual bool onReceiveResponse(const ::simple::SimpleReject& response) { return false; }
    virtual bool onReceiveResponse(const ::simple::SimpleNotify& response) { return false; }
    virtual bool onReceiveResponse(const ::simple::DisconnectRequest& response) { return false; }

    virtual bool onReceiveReject(const ::simple::SimpleReject& reject);

    virtual bool onReceiveReject(const ::simple::SimpleRequest& reject) { return false; }
    virtual bool onReceiveReject(const ::simple::SimpleResponse& reject) { return false; }
    virtual bool onReceiveReject(const ::simple::SimpleNotify& reject) { return false; }
    virtual bool onReceiveReject(const ::simple::DisconnectRequest& reject) { return false; }

    virtual void onReceiveNotify(const ::simple::SimpleRequest& notify) {}
    virtual void onReceiveNotify(const ::simple::SimpleResponse& notify) {}
    virtual void onReceiveNotify(const ::simple::SimpleReject& notify) {}
    virtual void onReceiveNotify(const ::simple::SimpleNotify& notify) {}
    virtual void onReceiveNotify(const ::simple::DisconnectRequest& notify) {}

    virtual void onReceive(const ::simple::SimpleRequest& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }
    virtual void onReceive(const ::simple::SimpleResponse& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }
    virtual void onReceive(const ::simple::SimpleReject& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }
    virtual void onReceive(const ::simple::SimpleNotify& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }
    virtual void onReceive(const ::simple::DisconnectRequest& value) override { if (!onReceiveResponse(value) && !onReceiveReject(value)) onReceiveNotify(value); }

    // Reset client requests
    virtual void reset_requests();

    // Watchdog client requests for timeouts
    virtual void watchdog_requests(uint64_t utc);

private:
    std::unordered_map<FBE::uuid_t, std::tuple<uint64_t, uint64_t, std::promise<::simple::SimpleResponse>>> _requests_by_id_SimpleResponse;
    std::map<uint64_t, FBE::uuid_t> _requests_by_timestamp_SimpleResponse;
};

} // namespace simple

} // namespace FBE
