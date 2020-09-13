
#include "wsjcpp_json_rpc20_handler_auth.h"
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// WsjcppJsonRpc20HandlerAuthLogin

REGISTRY_WSJCPP_JSONRPC20_HANDLER(WsjcppJsonRpc20HandlerAuthLogin)

WsjcppJsonRpc20HandlerAuthLogin::WsjcppJsonRpc20HandlerAuthLogin() 
: WsjcppJsonRpc20HandlerBase("auth_login", "Auth by login and password") {
    TAG = "WsjcppJsonRpc20HandlerAuthLogin";
    setAccessUnauthorized(true);
    setAccessUser(false);
    setAccessTester(false);
    setAccessAdmin(false);
    setActivatedFromVersion("v0.0.2");
    // void setDeprecatedFromVersion("");

    // description of input params
    requireStringParam("login", "User Login")
        .addValidator(new WsjcppValidatorStringLength(5,10));
    requireStringParam("password", "User Password")
        .addValidator(new WsjcppValidatorStringLength(5,20));
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20HandlerAuthLogin::handle(WsjcppJsonRpc20Request *pRequest) {
    WsjcppLog::err(TAG, "Not implemented");
    // TODO
    pRequest->fail(WsjcppJsonRpc20Error(501, "NOT_IMPLEMENTED"));
}


// ---------------------------------------------------------------------
// WsjcppJsonRpc20HandlerAuthLogoff

REGISTRY_WSJCPP_JSONRPC20_HANDLER(WsjcppJsonRpc20HandlerAuthLogoff)

WsjcppJsonRpc20HandlerAuthLogoff::WsjcppJsonRpc20HandlerAuthLogoff() 
: WsjcppJsonRpc20HandlerBase("auth_logoff", "Logoff") {
    TAG = "WsjcppJsonRpc20HandlerAuthLogoff";
    setAccessUnauthorized(false);
    setAccessUser(true);
    setAccessTester(true);
    setAccessAdmin(true);
    setActivatedFromVersion("v0.0.2");
    // void setDeprecatedFromVersion("");
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20HandlerAuthLogoff::handle(WsjcppJsonRpc20Request *pRequest) {
    WsjcppLog::err(TAG, "Not implemented");
    // TODO
    pRequest->fail(WsjcppJsonRpc20Error(501, "NOT_IMPLEMENTED"));
}


// ---------------------------------------------------------------------
// WsjcppJsonRpc20HandlerAuthToken

REGISTRY_WSJCPP_JSONRPC20_HANDLER(WsjcppJsonRpc20HandlerAuthToken)

WsjcppJsonRpc20HandlerAuthToken::WsjcppJsonRpc20HandlerAuthToken() 
: WsjcppJsonRpc20HandlerBase("auth_token", "Auth by token") {
    TAG = "WsjcppJsonRpc20HandlerAuthToken";
    setAccessUnauthorized(true);
    setAccessUser(false);
    setAccessTester(false);
    setAccessAdmin(false);
    setActivatedFromVersion("v0.0.2");
    // void setDeprecatedFromVersion("");

    // description of input params
    requireStringParam("token", "Token")
        .addValidator(new WsjcppValidatorStringLength(10,100));
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20HandlerAuthToken::handle(WsjcppJsonRpc20Request *pRequest) {
    WsjcppLog::err(TAG, "Not implemented");
    // TODO
    pRequest->fail(WsjcppJsonRpc20Error(501, "NOT_IMPLEMENTED"));
}


