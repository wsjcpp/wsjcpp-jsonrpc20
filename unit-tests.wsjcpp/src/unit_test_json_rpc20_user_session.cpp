#include "unit_test_json_rpc20_user_session.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// UnitTestJsonRpc20UserSession

REGISTRY_WSJCPP_UNIT_TEST(UnitTestJsonRpc20UserSession)

UnitTestJsonRpc20UserSession::UnitTestJsonRpc20UserSession()
    : WsjcppUnitTestBase("UnitTestJsonRpc20UserSession") {
}

// ---------------------------------------------------------------------

bool UnitTestJsonRpc20UserSession::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestJsonRpc20UserSession::executeTest() {

    WsjcppJsonRpc20UserSession session0;
    compareB("is admin (0)", session0.isAdmin(), false);
    compareB("is user (0)", session0.isUser(), false);
    compareB("is tester (0)", session0.isTester(), false);
    compareB("has role (0)", session0.hasRole(), false);

    compareN("User Id (0)", session0.getUserId(), 0);

    compareS("User Uuid (0)", session0.getUserUuid(), "");
    compareS("User Role (0)", session0.getUserRole(), "");
    compareS("User Name (0)", session0.getUserName(), "");
    compareS("User Email (0)", session0.getUserEmail(), "");

    compareS("Session Uuid (0)", session0.getSessionUuid(), "");
    compareN("Session Created (0)", session0.getSessionCreated(), 0);
    compareN("Session Updated (0)", session0.getSessionUpdated(), 0);
    compareN("Session Expire At (0)", session0.getSessionExpireAt(), 0);
    compareS("Session Custom (0)", session0.getSessionCustom().dump(), "null");

    // test fill role
    session0.setUserRole("admin");
    compareB("is admin (1)", session0.isAdmin(), true);
    compareB("is user (1)", session0.isUser(), false);
    compareB("is tester (1)", session0.isTester(), false);
    compareB("has role (1)", session0.hasRole(), true);
    compareS("User Role (1)", session0.getUserRole(), "admin");

    session0.setUserRole("user");  
    compareB("is admin (2)", session0.isAdmin(), false);
    compareB("is user (2)", session0.isUser(), true);
    compareB("is tester (2)", session0.isTester(), false);
    compareB("has role (2)", session0.hasRole(), true);
    compareS("User Role (2)", session0.getUserRole(), "user");

    session0.setUserRole("tester");  
    compareB("is admin (3)", session0.isAdmin(), false);
    compareB("is user (3)", session0.isUser(), false);
    compareB("is tester (3)", session0.isTester(), true);
    compareB("has role (3)", session0.hasRole(), true);
    compareS("User Role (3)", session0.getUserRole(), "tester");

    std::string sUserRole = "custom0";
    session0.setUserRole(sUserRole);
    compareB("is admin (4)", session0.isAdmin(), false);
    compareB("is user (4)", session0.isUser(), false);
    compareB("is tester (4)", session0.isTester(), false);
    compareB("has role (4)", session0.hasRole(), true);
    compareS("User Role (4)", session0.getUserRole(), sUserRole);

    int nUserId = 1000;
    std::string sUserUuid = "b5bd63ce-0405-4ef5-8473-552f2729e7e9";
    std::string sUserName = "user some name";
    std::string sUserEmail = "user@user.usr";
    std::string sSessionUuid = "580ec846-4d3f-47b1-bb05-a54f1dd7fdbe";
    long nCreated = WsjcppCore::getCurrentTimeInMilliseconds();
    long nUpdated = nCreated + 3000;
    long nExpiredAt = nCreated + 24*60*60*1000;
    nlohmann::json jsonCustom;
    jsonCustom["some"] = "some";
    std::string sJsonCustom = "{\"some\":\"some\"}";

    session0.setUserId(nUserId);
    session0.setUserUuid(sUserUuid);
    session0.setUserName(sUserName);
    session0.setUserEmail(sUserEmail);
    session0.setSessionUuid(sSessionUuid);
    session0.setSessionCreated(nCreated);
    session0.setSessionUpdated(nUpdated);
    session0.setSessionExpireAt(nExpiredAt);
    session0.setSessionCustom(jsonCustom);

    compareN("User Id (5)", session0.getUserId(), nUserId);
    compareS("User Uuid (6)", session0.getUserUuid(), sUserUuid);
    compareS("User Name (7)", session0.getUserName(), sUserName);
    compareS("User Email (8)", session0.getUserEmail(), sUserEmail);
    compareS("Session Uuid (9)", session0.getSessionUuid(), sSessionUuid);
    compareN("Session Created (10)", session0.getSessionCreated(), nCreated);
    compareN("Session Updated (11)", session0.getSessionUpdated(), nUpdated);
    compareN("Session Expire At (12)", session0.getSessionExpireAt(), nExpiredAt);
    compareS("Session Custom (13)", session0.getSessionCustom().dump(), sJsonCustom);

    // test full json
    nlohmann::json jsonSession = session0.toJson();
    WsjcppLog::info(TAG, jsonSession.dump());
    compareS("toJson Session uuid (14)", jsonSession["uuid"], sSessionUuid);
    compareN("toJson Session created (14)", jsonSession["created"], nCreated);
    compareN("toJson Session updated (14)", jsonSession["updated"], nUpdated);
    compareN("toJson Session expire_at (14)", jsonSession["expire_at"], nExpiredAt);

    compareN("toJson Session user.id (14)", jsonSession["user"]["id"], nUserId);
    compareS("toJson Session user.id (14)", jsonSession["user"]["uuid"], sUserUuid);
    compareS("toJson Session user.id (14)", jsonSession["user"]["name"], sUserName);
    compareS("toJson Session user.id (14)", jsonSession["user"]["role"], sUserRole);
    compareS("toJson Session user.id (14)", jsonSession["user"]["email"], sUserEmail);

    WsjcppJsonRpc20UserSession session1(jsonSession);

    compareB("session1 is admin (0)", session1.isAdmin(), false);
    compareB("session1 is user (0)", session1.isUser(), false);
    compareB("session1 is tester (0)", session1.isTester(), false);
    compareB("session1 has role (0)", session1.hasRole(), true);
    compareN("session1 User Id (0)", session1.getUserId(), nUserId);
    compareS("session1 User Uuid (0)", session1.getUserUuid(), sUserUuid);
    compareS("session1 User Role (0)", session1.getUserRole(), sUserRole);
    compareS("session1 User Name (0)", session1.getUserName(), sUserName);
    compareS("session1 User Email (0)", session1.getUserEmail(), sUserEmail);
    compareS("session1 Session Uuid (0)", session1.getSessionUuid(), sSessionUuid);
    compareN("session1 Session Created (0)", session1.getSessionCreated(), nCreated);
    compareN("session1 Session Updated (0)", session1.getSessionUpdated(), nUpdated);
    compareN("session1 Session Expire At (0)", session1.getSessionExpireAt(), nExpiredAt);
    compareS("session1 Session Custom (0)", session1.getSessionCustom().dump(), sJsonCustom);

    // check rewrite data 
    WsjcppJsonRpc20UserSession session2;
    session2.setUserId(nUserId);
    session2.setUserUuid(sUserUuid);
    session2.setUserName(sUserName);
    session2.setUserEmail(sUserEmail);
    session2.setSessionUuid(sSessionUuid);
    session2.setSessionCreated(nCreated);
    session2.setSessionUpdated(nUpdated);
    session2.setSessionExpireAt(nExpiredAt);
    session2.setSessionCustom(jsonCustom);

    nlohmann::json jsonSessionEmpty;
    session2.fillFrom(jsonSessionEmpty);

    compare("session2: is admin (0)", session2.isAdmin(), false);
    compare("session2: is user (0)", session2.isUser(), false);
    compare("session2: is tester (0)", session2.isTester(), false);
    compare("session2: has role (0)", session2.hasRole(), false);
    compare("session2: User Id (0)", session2.getUserId(), 0);
    compare("session2: User Uuid (0)", session2.getUserUuid(), "");
    compare("session2: User Role (0)", session2.getUserRole(), "");
    compare("session2: User Name (0)", session2.getUserName(), "");
    compare("session2: User Email (0)", session2.getUserEmail(), "");
    compare("session2: Session Uuid (0)", session2.getSessionUuid(), "");
    compare("session2: Session Created (0)", session2.getSessionCreated(), 0);
    compare("session2: Session Updated (0)", session2.getSessionUpdated(), 0);
    compare("session2: Session Expire At (0)", session2.getSessionExpireAt(), 0);
    compare("session2: Session Custom (0)", session2.getSessionCustom().dump(), "null");
}

// ---------------------------------------------------------------------

bool UnitTestJsonRpc20UserSession::doAfterTest() {
    // nothing
    return true;
}