#include "unit_test_parsing_request_params.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// CustomObjValidator

class CustomObjValidator : public WsjcppValidatorJsonBase {

    public:
        CustomObjValidator() : WsjcppValidatorJsonBase("custom_json") {
            // nothing
        };
        
        virtual bool isValid(const nlohmann::json &jsonValue, std::string &sError) override {
            if (jsonValue.find("subname") == jsonValue.end()) {
                sError = "Expected subname in struct";
                return false;
            }
            return true;
        };
};

// ---------------------------------------------------------------------
// WsjcppJsonRpc20HandlerGameCreate

class WsjcppJsonRpc20HandlerGameCreate : public WsjcppJsonRpc20HandlerBase {
    public:
        WsjcppJsonRpc20HandlerGameCreate();
        virtual void handle(WsjcppJsonRpc20Request *pRequest) override;
};

// ---------------------------------------------------------------------

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
    requireStringParam("uuid1", "object uuid")
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

    optionalJsonParam("custom", "Some custom json")
        .addValidator(new CustomObjValidator());
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

bool UnitTestParsingRequestParams::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestParsingRequestParams::executeTest() {

    WsjcppJsonRpc20WebSocketServer *pWebSocketServer = new WsjcppJsonRpc20WebSocketServer();
    FakeWebSocketClient *pFakeClient = new FakeWebSocketClient();
    WsjcppJsonRpc20WebSocketClient *pClient = pFakeClient;
    WsjcppJsonRpc20HandlerBase *pHandlergameCreate = WsjcppJsonRpc20::findJsonRpc20Handler("game_create");
    const std::vector<WsjcppJsonRpc20ParamDef> &vParamsDef = pHandlergameCreate->getParamsDef();

    // checkInputParams - paramer required
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams0 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams0 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams0 error.message", sErrorMessage, "PARAMETER_REQUIRED");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams0 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams0 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams0 error.context.param_name", sErrorContextParamName, "uuid1");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams0 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams0 method", sMethod, "game_create");
        delete pRequest;
    }

    // checkInputParams - paramer datatype string
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        jsonRequest["params"] = nlohmann::json::object();
        jsonRequest["params"]["uuid1"] = 1;
        
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams1 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams1 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams1 error.message", sErrorMessage, "DATATYPE_OF_PARAMETER_EXPECTED_STRING");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams1 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams1 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams1 error.context.param_name", sErrorContextParamName, "uuid1");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams1 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams1 method", sMethod, "game_create");
        delete pRequest;
    }

    // checkInputParams - parameter data type int
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        jsonRequest["params"] = nlohmann::json::object();
        jsonRequest["params"]["uuid1"] = "9eb658c0-c217-4386-8688-f86c72e077c5";
        jsonRequest["params"]["cost"] = "111";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams2 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams2 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams2 error.message", sErrorMessage, "DATATYPE_OF_PARAMETER_EXPECTED_INTEGER");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams2 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams2 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams2 error.context.param_name", sErrorContextParamName, "cost");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams2 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams2 method", sMethod, "game_create");
        delete pRequest;
    }

    // checkInputParams - parameter data type boolean
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        jsonRequest["params"] = nlohmann::json::object();
        jsonRequest["params"]["uuid1"] = "9eb658c0-c217-4386-8688-f86c72e077c5";
        jsonRequest["params"]["name"] = "1111";
        jsonRequest["params"]["cost"] = 3;
        jsonRequest["params"]["age"] = 1;
        jsonRequest["params"]["public"] = "true";
        jsonRequest["params"]["activated"] = false;
        jsonRequest["params"]["custom"] = nlohmann::json::object();

        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams3 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams3 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams3 error.message", sErrorMessage, "DATATYPE_OF_PARAMETER_EXPECTED_BOOLEAN");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams3 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams3 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams3 error.context.param_name", sErrorContextParamName, "public");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams3 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams3 method", sMethod, "game_create");
        delete pRequest;
    }

    // checkInputParams - parameter data type json
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        jsonRequest["params"] = nlohmann::json::object();
        jsonRequest["params"]["uuid1"] = "9eb658c0-c217-4386-8688-f86c72e077c5";
        jsonRequest["params"]["name"] = "1111";
        jsonRequest["params"]["cost"] = 3;
        jsonRequest["params"]["age"] = 1;
        jsonRequest["params"]["public"] = true;
        jsonRequest["params"]["activated"] = false;
        jsonRequest["params"]["custom"] = "some";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams4 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams4 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams4 error.message", sErrorMessage, "DATATYPE_OF_PARAMETER_EXPECTED_JSON_OBJECT");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams4 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams4 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams4 error.context.param_name", sErrorContextParamName, "custom");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams4 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams4 method", sMethod, "game_create");
        delete pRequest;
    }

    // checkInputParams - extra field
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        jsonRequest["params"] = nlohmann::json::object();
        jsonRequest["params"]["uuid1"] = "9eb658c0-c217-4386-8688-f86c72e077c5";
        jsonRequest["params"]["name"] = "1111";
        jsonRequest["params"]["cost"] = 3;
        jsonRequest["params"]["age"] = 1;
        jsonRequest["params"]["public"] = true;
        jsonRequest["params"]["activated"] = false;
        jsonRequest["params"]["custom"] = nlohmann::json::object();
        jsonRequest["params"]["custom"]["subname"] = "111";
        jsonRequest["params"]["ollala"] = "some";
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams5 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams5 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams5 error.message", sErrorMessage, "EXTRA_PARAMETER_FOUND");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams5 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams5 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams5 error.context.param_name", sErrorContextParamName, "ollala");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams5 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams5 method", sMethod, "game_create");
        delete pRequest;
    }

    // checkInputParams - string validator
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        jsonRequest["params"] = nlohmann::json::object();
        jsonRequest["params"]["uuid1"] = "9eb658c0-c217-4386-8688- ";
        jsonRequest["params"]["name"] = "1111";
        jsonRequest["params"]["cost"] = 3;
        jsonRequest["params"]["age"] = 1;
        jsonRequest["params"]["public"] = true;
        jsonRequest["params"]["activated"] = false;
        jsonRequest["params"]["custom"] = nlohmann::json::object();
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams6 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams6 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams6 error.message", sErrorMessage, "INVALID_PARAM_STRING_VALUE");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams6 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams6 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams6 error.context.param_name", sErrorContextParamName, "uuid1");
        std::string sErrorContextDescription = jsonResponse["error"]["context"]["description"];
        compare("checkInputParams6 error.context.description", sErrorContextDescription,
            "uuid - Value must match regular expression ^[0-9A-Fa-f]{8}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{12}$");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams6 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams6 method", sMethod, "game_create");
        delete pRequest;
    }

    // checkInputParams - int validator
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        jsonRequest["params"] = nlohmann::json::object();
        jsonRequest["params"]["uuid1"] = "9eb658c0-c217-4386-8688-f86c72e077c5";
        jsonRequest["params"]["name"] = "1111";
        jsonRequest["params"]["cost"] = 1;
        jsonRequest["params"]["age"] = 1;
        jsonRequest["params"]["public"] = true;
        jsonRequest["params"]["activated"] = false;
        jsonRequest["params"]["custom"] = nlohmann::json::object();
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams7 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams7 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams7 error.message", sErrorMessage, "INVALID_PARAM_INTEGER_VALUE");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams7 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams7 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams7 error.context.param_name", sErrorContextParamName, "cost");
        std::string sErrorContextDescription = jsonResponse["error"]["context"]["description"];
        compare("checkInputParams7 error.context.description", sErrorContextDescription,
            "Value must be more or equal then 3");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams7 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams7 method", sMethod, "game_create");
        delete pRequest;
    }

    // checkInputParams - json validator
    {
        pFakeClient->clearLastTextMessage();
        nlohmann::json jsonRequest;
        jsonRequest["id"] = "id1";
        jsonRequest["jsonrpc"] = "2.0";
        jsonRequest["method"] = "game_create";
        jsonRequest["params"] = nlohmann::json::object();
        jsonRequest["params"]["uuid1"] = "9eb658c0-c217-4386-8688-f86c72e077c5";
        jsonRequest["params"]["name"] = "1111";
        jsonRequest["params"]["cost"] = 3;
        jsonRequest["params"]["age"] = 1;
        jsonRequest["params"]["public"] = true;
        jsonRequest["params"]["activated"] = false;
        jsonRequest["params"]["custom"] = nlohmann::json::object();
        std::string sRequest = jsonRequest.dump();
        WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);
        compare("checkInputParams8 parseIncomeData", pRequest->parseIncomeData(sRequest), true);
        compare("checkInputParams8 result", pRequest->checkInputParams(vParamsDef), false);
        std::string sResponse = pFakeClient->getLastTextMessage();
        // std::cout << "sResponse = " << sResponse << std::endl;
        nlohmann::json jsonResponse = nlohmann::json::parse(sResponse);
        std::string sErrorMessage = jsonResponse["error"]["message"];
        compare("checkInputParams8 error.message", sErrorMessage, "INVALID_PARAM_JSON_VALUE");
        int nErrorCode = jsonResponse["error"]["code"];
        compare("checkInputParams8 error.code", nErrorCode, 400);
        std::string sErrorContextMethod = jsonResponse["error"]["context"]["method"];
        compare("checkInputParams8 error.context.method", sErrorContextMethod, "game_create");
        std::string sErrorContextParamName = jsonResponse["error"]["context"]["param_name"];
        compare("checkInputParams8 error.context.param_name", sErrorContextParamName, "custom");
        std::string sErrorContextDescription = jsonResponse["error"]["context"]["description"];
        compare("checkInputParams8 error.context.description", sErrorContextDescription,
            "Expected subname in struct");
        std::string sId = jsonResponse["id"];
        compare("checkInputParams8 id", sId, "id1");
        std::string sMethod = jsonResponse["method"];
        compare("checkInputParams8 method", sMethod, "game_create");
        delete pRequest;
    }

    delete pHandlergameCreate;
    delete pWebSocketServer;
    delete pFakeClient;
}

// ---------------------------------------------------------------------

bool UnitTestParsingRequestParams::doAfterTest() {
    // nothing
    return true;
}