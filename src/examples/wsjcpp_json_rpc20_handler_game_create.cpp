
#include "wsjcpp_json_rpc20_handler_game_create.h"
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// WsjcppJsonRpc20HandlerGameCreate

WsjcppJsonRpc20HandlerGameCreate::WsjcppJsonRpc20HandlerGameCreate() 
: WsjcppJsonRpc20HandlerBase("game_create", "TODO description") {
    TAG = "WsjcppJsonRpc20HandlerGameCreate";
    // setAccessUnauthorized(true);
    // setAccessUser(true);
    // setAccessTester(true);
    // setAccessAdmin(true);
    // void setActivatedFromVersion("v0.0.1"); // TODO authomatic set WSJCPP_APP_VERSION
    // void setDeprecatedFromVersion("");

    // description of input params
    // requireStringParam("uuid", "object uuid")
    //    .addValidator(new WsjcppValidatorUUID());
    // optionalStringParam("name", "Name of object")
    //    .addValidator(new WsjcppValidatorStringLength(3,10));

    // requireIntegerParam("cost", "Name of object")
    //    .addValidator(new WsjcppValidatorIntegerMinValue(3))
    //    .addValidator(new WsjcppValidatorIntegerMaxValue(1000));
    // optionalIntegerParam("age", "Name of object")
    //    .addValidator(new WsjcppValidatorIntegerMinValue(0))

    // requireBooleanParam("public", "True if object is public");
    // optionalBooleanParam("activated", "If object can handle");
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20HandlerGameCreate::handle(WsjcppJsonRpc20Request *pRequest) {
    WsjcppLog::err(TAG, "Not implemented");
    // TODO
    pRequest->fail(WsjcppJsonRpc20Error(501, "NOT_IMPLEMENTED"));
}


