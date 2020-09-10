#ifndef WSJCPP_JSON_RPC20_HANDLER_GAME_CREATE_H
#define WSJCPP_JSON_RPC20_HANDLER_GAME_CREATE_H

#include <wsjcpp_jsonrpc20.h>

class WsjcppJsonRpc20HandlerGameCreate : public WsjcppJsonRpc20HandlerBase {
    public:
        WsjcppJsonRpc20HandlerGameCreate();
        virtual void handle(WsjcppJsonRpc20Request *pRequest) override;
};

#endif // WSJCPP_JSON_RPC20_HANDLER_GAME_CREATE_H
