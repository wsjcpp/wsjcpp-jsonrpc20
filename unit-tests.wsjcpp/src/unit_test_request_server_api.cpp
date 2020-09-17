#include "unit_test_request_server_api.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// UnitTestRequestServerApi

REGISTRY_WSJCPP_UNIT_TEST(UnitTestRequestServerApi)

UnitTestRequestServerApi::UnitTestRequestServerApi()
    : WsjcppUnitTestBase("UnitTestRequestServerApi") {
}

// ---------------------------------------------------------------------

bool UnitTestRequestServerApi::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestRequestServerApi::executeTest() {

    WsjcppJsonRpc20WebSocketServer *pWebSocketServer = new WsjcppJsonRpc20WebSocketServer();
    FakeWebSocketClient *pFakeClient = new FakeWebSocketClient();
    WsjcppJsonRpc20WebSocketClient *pClient = pFakeClient;

    WsjcppJsonRpc20HandlerBase *pHandlerServerApi = WsjcppJsonRpc20::findJsonRpc20Handler("server_api");
    WsjcppJsonRpc20Request *pRequest = new WsjcppJsonRpc20Request(pClient, pWebSocketServer);

    nlohmann::json requestJson;
    requestJson["jsonrpc"] = "2.0";
    requestJson["method"] = "server_api";
    requestJson["id"] = "id1";
    
    std::string sRequest = requestJson.dump();
    compareB("Response: check method", pRequest->parseIncomeData(sRequest), true);

    pHandlerServerApi->handle(pRequest);

    std::string sResponse = pFakeClient->getLastTextMessage();
    // std::cout << "sResponse: " << sResponse << std::endl;
    nlohmann::json respJson = nlohmann::json::parse(sResponse);

    std::string sMethod = respJson["method"];
    std::string sId = respJson["id"];
    std::string sJsonRpc = respJson["jsonrpc"];
    compareS("Response: check method", sMethod, "server_api");
    compareS("Response: check id", sId, "id1");
    compareS("Response: check jsonrpc", sJsonRpc, "2.0");

    
    std::string sVersion = respJson["result"]["version"];
    compareS("Response: check result.version", sVersion, std::string(WSJCPP_APP_VERSION));
    
    int nDataLength = respJson["result"]["data_length"];
    int nExpectedDataLength = respJson["result"]["data"].size();
    compareN("Response: check result.data_length", nDataLength, nExpectedDataLength);

    int nId = 1;
    for (int i = 0; i < nExpectedDataLength; i++) {
        std::string sMethodName0 = respJson["result"]["data"][i]["method"];
        if (sMethodName0 == "server_api") {
            nId = i;
        }
    }

    nlohmann::json data0Json = respJson["result"]["data"][nId];
    bool bAccessUnauthorized = data0Json["access"]["unauthorized"];
    bool bAccessUser = data0Json["access"]["user"];
    bool bAccessTester = data0Json["access"]["tester"];
    bool bAccessAdmin = data0Json["access"]["admin"];

    compareB("Response: check result.data[0].access.unauthorized", bAccessUnauthorized, true);
    compareB("Response: check result.data[0].access.user", bAccessUser, true);
    compareB("Response: check result.data[0].access.tester", bAccessTester, true);
    compareB("Response: check result.data[0].access.admin", bAccessAdmin, true);
    
    sMethod = data0Json["method"];
    compareS("Response: check result.data[0].method", sMethod, "server_api");
    std::string sDescription = data0Json["description"];

    compareS("Response: check result.data[0].method", sDescription, pHandlerServerApi->getDescription());
}

// ---------------------------------------------------------------------

bool UnitTestRequestServerApi::doAfterTest() {
    // nothing
    return true;
}