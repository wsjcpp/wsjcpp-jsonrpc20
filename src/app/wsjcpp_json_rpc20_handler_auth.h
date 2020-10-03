#ifndef WSJCPP_JSON_RPC20_HANDLER_AUTH_H
#define WSJCPP_JSON_RPC20_HANDLER_AUTH_H

#include <wsjcpp_jsonrpc20.h>

class WsjcppJsonRpc20HandlerAuthLogin : public WsjcppJsonRpc20HandlerBase {
    public:
        WsjcppJsonRpc20HandlerAuthLogin();
        virtual void handle(WsjcppJsonRpc20Request *pRequest) override;
};

class WsjcppJsonRpc20HandlerAuthLogoff : public WsjcppJsonRpc20HandlerBase {
    public:
        WsjcppJsonRpc20HandlerAuthLogoff();
        virtual void handle(WsjcppJsonRpc20Request *pRequest) override;
};

class WsjcppJsonRpc20HandlerAuthToken : public WsjcppJsonRpc20HandlerBase {
    public:
        WsjcppJsonRpc20HandlerAuthToken();
        virtual void handle(WsjcppJsonRpc20Request *pRequest) override;
};

#endif // WSJCPP_JSON_RPC20_HANDLER_AUTH_H
