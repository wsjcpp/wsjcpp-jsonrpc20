
#include "wsjcpp_json_rpc20_handler_game_create.h"
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// WsjcppJsonRpc20HandlerGameCreate

REGISTRY_WSJCPP_JSONRPC20_HANDLER(WsjcppJsonRpc20HandlerGameCreate)

WsjcppJsonRpc20HandlerGameCreate::WsjcppJsonRpc20HandlerGameCreate() 
: WsjcppJsonRpc20HandlerBase("game_create", "Some example of description") {
    TAG = "WsjcppJsonRpc20HandlerGameCreate";
    setAccessUnauthorized(false);
    setAccessUser(true);
    setAccessTester(true);
    setAccessAdmin(true);
    setActivatedFromVersion("v0.0.2");
    // void setDeprecatedFromVersion("");

    // description of input params
    requireStringParam("uuid", "object uuid")
        .addValidator(new WsjcppValidatorUUID());
    optionalStringParam("name", "Name of object")
        .addValidator(new WsjcppValidatorStringLength(3,10));

    requireIntegerParam("cost", "Name of object")
        .addValidator(new WsjcppValidatorIntegerMinValue(3))
        .addValidator(new WsjcppValidatorIntegerMaxValue(1000));
    optionalIntegerParam("age", "Name of object")
        .addValidator(new WsjcppValidatorIntegerMinValue(0));

    requireBooleanParam("public", "True if object is public");
    optionalBooleanParam("activated", "If object can handle");

    optionalJsonParam("custom", "Some custom json");
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20HandlerGameCreate::handle(WsjcppJsonRpc20Request *pRequest) {
    WsjcppLog::err(TAG, "Not implemented");
    // TODO
    pRequest->fail(WsjcppJsonRpc20Error(501, "NOT_IMPLEMENTED"));
}


