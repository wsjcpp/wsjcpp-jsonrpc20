#include "unit_test_parsing_request_params.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

class WsjcppJsonRpc20HandlerGameCreate : public WsjcppJsonRpc20HandlerBase {
    public:
        WsjcppJsonRpc20HandlerGameCreate();
        virtual void handle(WsjcppJsonRpc20Request *pRequest) override;
};


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

// ---------------------------------------------------------------------
// UnitTestParsingRequestParams

REGISTRY_WSJCPP_UNIT_TEST(UnitTestParsingRequestParams)

UnitTestParsingRequestParams::UnitTestParsingRequestParams()
    : WsjcppUnitTestBase("UnitTestParsingRequestParams") {
}

// ---------------------------------------------------------------------

void UnitTestParsingRequestParams::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestParsingRequestParams::run() {
    bool bTestSuccess = true;

     WsjcppJsonRpc20WebSocketServer *pWebSocketServer = new WsjcppJsonRpc20WebSocketServer();
    FakeWebSocketClient *pFakeClient = new FakeWebSocketClient();
    WsjcppJsonRpc20WebSocketClient *pClient = pFakeClient;

    WsjcppJsonRpc20HandlerBase *pHandlerServerApi = WsjcppJsonRpc20::findJsonRpc20Handler("game_create");

    // parseIncomeData empty - wrong json
    {
        WsjcppJsonRpc20Request *pRequest0 = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compareB(bTestSuccess, "parseIncomeData empty", pRequest0->parseIncomeData(""), false);
        std::string sResponse0 = pFakeClient->getLastTextMessage();
        nlohmann::json jsonResponse0 = nlohmann::json::parse(sResponse0);
        std::string sErrorMessage = jsonResponse0["error"]["message"];
        compareS(bTestSuccess, "parseIncomeData empty. error.message", sErrorMessage, "WRONG_JSON");
        int nErrorCode = jsonResponse0["error"]["code"];
        compareN(bTestSuccess, "parseIncomeData empty. error.code", nErrorCode, 400);
        std::string sId = jsonResponse0["id"];
        compareS(bTestSuccess, "parseIncomeData empty. id", sId, "unknown_id");
        std::string sMethod = jsonResponse0["method"];
        compareS(bTestSuccess, "parseIncomeData empty. method", sMethod, "unknown_method");
    }
    
    // missing 'id' in request
    {
        nlohmann::json jsonRequest;
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compareB(bTestSuccess, "parseIncomeData missing id", pRequest->parseIncomeData(sRequest), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compareS(bTestSuccess, "parseIncomeData missing id. error.message", sErrorMessage, "NOT_FOUND_ID_IN_REQUEST");
        int nErrorCode = jsonResponse["error"]["code"];
        compareN(bTestSuccess, "parseIncomeData missing id. error.code", nErrorCode, 400);
        std::string sId = jsonResponse["id"];
        compareS(bTestSuccess, "parseIncomeData missing id. id", sId, "unknown_id");
        std::string sMethod = jsonResponse["method"];
        compareS(bTestSuccess, "parseIncomeData missing id. method", sMethod, "game_create");
    }

    // missing 'method' in request
    {
        nlohmann::json jsonRequest;
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["id"] = "id1";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compareB(bTestSuccess, "parseIncomeData missing method", pRequest->parseIncomeData(sRequest), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compareS(bTestSuccess, "parseIncomeData missing method. error. message", sErrorMessage, "NOT_FOUND_METHOD_IN_REQUEST");
        int nErrorCode = jsonResponse["error"]["code"];
        compareN(bTestSuccess, "parseIncomeData missing method. error. code", nErrorCode, 400);
        std::string sId = jsonResponse["id"];
        compareS(bTestSuccess, "parseIncomeData missing method. id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compareS(bTestSuccess, "parseIncomeData missing method. method", sMethod, "unknown_method");
    }

    // missing 'jsonrpc' in request
    {
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["method"] = "game_create";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compareB(bTestSuccess, "parseIncomeData missing jsonrpc", pRequest->parseIncomeData(sRequest), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << sResponse << std::endl;
        nlohmann::json jsonResponse0 = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse0["error"]["message"];
        compareS(bTestSuccess, "parseIncomeData missing jsonrpc. error.message", sErrorMessage, "NOT_FOUND_FIELD_JSONRPC_IN_REQUEST");
        int nErrorCode = jsonResponse0["error"]["code"];
        compareN(bTestSuccess, "parseIncomeData missing jsonrpc. error.code", nErrorCode, 400);
        std::string sId = jsonResponse0["id"];
        compareS(bTestSuccess, "parseIncomeData missing jsonrpc. id", sId, "id1");
        std::string sMethod = jsonResponse0["method"];
        compareS(bTestSuccess, "parseIncomeData missing jsonrpc. method", sMethod, "game_create");
    }

    // field 'jsonrpc' is non string in request
    {
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = 2;
        jsonRequest["method"] = "game_create";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compareB(bTestSuccess, "parseIncomeData jsonrpc is non string", pRequest->parseIncomeData(sRequest), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << sResponse << std::endl;
        nlohmann::json jsonResponse0 = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse0["error"]["message"];
        compareS(bTestSuccess, "parseIncomeData jsonrpc is non string. error.message", sErrorMessage, "FIELD_JSONRPC_EXPECTED_AS_STRING_IN_REQUEST");
        int nErrorCode = jsonResponse0["error"]["code"];
        compareN(bTestSuccess, "parseIncomeData jsonrpc is non string. error.code", nErrorCode, 400);
        std::string sId = jsonResponse0["id"];
        compareS(bTestSuccess, "parseIncomeData jsonrpc is non string. id", sId, "id1");
        std::string sMethod = jsonResponse0["method"];
        compareS(bTestSuccess, "parseIncomeData jsonrpc is non string. method", sMethod, "game_create");
    }

    // field 'jsonrpc' is no "2.0" in request
    {
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.1";
        jsonRequest["method"] = "game_create";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compareB(bTestSuccess, "parseIncomeData jsonrpc is no 2.0", pRequest->parseIncomeData(sRequest), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << sResponse << std::endl;
        nlohmann::json jsonResponse0 = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse0["error"]["message"];
        compareS(bTestSuccess, "parseIncomeData jsonrpc is no 2.0. error.message", sErrorMessage, "FIELD_JSONRPC_EXPECTED_2_DOT_0_IN_REQUEST");
        int nErrorCode = jsonResponse0["error"]["code"];
        compareN(bTestSuccess, "parseIncomeData jsonrpc is no 2.0. error.code", nErrorCode, 400);
        std::string sId = jsonResponse0["id"];
        compareS(bTestSuccess, "parseIncomeData jsonrpc is no 2.0. id", sId, "id1");
        std::string sMethod = jsonResponse0["method"];
        compareS(bTestSuccess, "parseIncomeData jsonrpc is no 2.0. method", sMethod, "game_create");
    }

    

    nlohmann::json requestJson;
    requestJson["jsonrpc"] = "2.0";
    requestJson["method"] = "game_create";
    requestJson["id"] = "id1";
    requestJson["params"] = nlohmann::json::array();

    // pRequest0->parseIncomeData(requestJson.dump());

    // pHandlerServerApi->handle(pRequest0);

    return bTestSuccess;
}

