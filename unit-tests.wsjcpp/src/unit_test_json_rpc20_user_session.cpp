#include <wsjcpp_unit_tests.h>
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// UnitTestJsonRpc20UserSession

class UnitTestJsonRpc20UserSession : public WsjcppUnitTestBase {
    public:
        UnitTestJsonRpc20UserSession();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

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
    compare("is admin (0)", session0.isAdmin(), false);
    compare("is user (0)", session0.isUser(), false);
    compare("is tester (0)", session0.isTester(), false);
    compare("has role (0)", session0.hasRole(), false);

    compare("User Id (0)", session0.getUserId(), 0);

    compare("User Uuid (0)", session0.getUserUuid(), "");
    compare("User Role (0)", session0.getUserRole(), "");
    compare("User Name (0)", session0.getUserName(), "");
    compare("User Email (0)", session0.getUserEmail(), "");

    compare("Session Uuid (0)", session0.getSessionUuid(), "");
    compare("Session Created (0)", session0.getSessionCreated(), 0);
    compare("Session Updated (0)", session0.getSessionUpdated(), 0);
    compare("Session Expire At (0)", session0.getSessionExpireAt(), 0);
    compare("Session Custom (0)", session0.getSessionCustom().dump(), "null");

    // test fill role
    session0.setUserRole("admin");
    compare("is admin (1)", session0.isAdmin(), true);
    compare("is user (1)", session0.isUser(), false);
    compare("is tester (1)", session0.isTester(), false);
    compare("has role (1)", session0.hasRole(), true);
    compare("User Role (1)", session0.getUserRole(), "admin");

    session0.setUserRole("user");  
    compare("is admin (2)", session0.isAdmin(), false);
    compare("is user (2)", session0.isUser(), true);
    compare("is tester (2)", session0.isTester(), false);
    compare("has role (2)", session0.hasRole(), true);
    compare("User Role (2)", session0.getUserRole(), "user");

    session0.setUserRole("tester");  
    compare("is admin (3)", session0.isAdmin(), false);
    compare("is user (3)", session0.isUser(), false);
    compare("is tester (3)", session0.isTester(), true);
    compare("has role (3)", session0.hasRole(), true);
    compare("User Role (3)", session0.getUserRole(), "tester");

    std::string sUserRole = "custom0";
    session0.setUserRole(sUserRole);
    compare("is admin (4)", session0.isAdmin(), false);
    compare("is user (4)", session0.isUser(), false);
    compare("is tester (4)", session0.isTester(), false);
    compare("has role (4)", session0.hasRole(), true);
    compare("User Role (4)", session0.getUserRole(), sUserRole);

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

    compare("User Id (5)", session0.getUserId(), nUserId);
    compare("User Uuid (6)", session0.getUserUuid(), sUserUuid);
    compare("User Name (7)", session0.getUserName(), sUserName);
    compare("User Email (8)", session0.getUserEmail(), sUserEmail);
    compare("Session Uuid (9)", session0.getSessionUuid(), sSessionUuid);
    compare("Session Created (10)", session0.getSessionCreated(), nCreated);
    compare("Session Updated (11)", session0.getSessionUpdated(), nUpdated);
    compare("Session Expire At (12)", session0.getSessionExpireAt(), nExpiredAt);
    compare("Session Custom (13)", session0.getSessionCustom().dump(), sJsonCustom);

    // test full json
    nlohmann::json jsonSession = session0.toJson();
    WsjcppLog::info(TAG, jsonSession.dump());
    compare("toJson Session uuid (14)", jsonSession["uuid"], sSessionUuid);
    compare("toJson Session created (14)", jsonSession["created"], nCreated);
    compare("toJson Session updated (14)", jsonSession["updated"], nUpdated);
    compare("toJson Session expire_at (14)", jsonSession["expire_at"], nExpiredAt);

    compare("toJson Session user.id (14)", jsonSession["user"]["id"], nUserId);
    compare("toJson Session user.id (14)", jsonSession["user"]["uuid"], sUserUuid);
    compare("toJson Session user.id (14)", jsonSession["user"]["name"], sUserName);
    compare("toJson Session user.id (14)", jsonSession["user"]["role"], sUserRole);
    compare("toJson Session user.id (14)", jsonSession["user"]["email"], sUserEmail);

    WsjcppJsonRpc20UserSession session1(jsonSession);

    compare("session1 is admin (0)", session1.isAdmin(), false);
    compare("session1 is user (0)", session1.isUser(), false);
    compare("session1 is tester (0)", session1.isTester(), false);
    compare("session1 has role (0)", session1.hasRole(), true);
    compare("session1 User Id (0)", session1.getUserId(), nUserId);
    compare("session1 User Uuid (0)", session1.getUserUuid(), sUserUuid);
    compare("session1 User Role (0)", session1.getUserRole(), sUserRole);
    compare("session1 User Name (0)", session1.getUserName(), sUserName);
    compare("session1 User Email (0)", session1.getUserEmail(), sUserEmail);
    compare("session1 Session Uuid (0)", session1.getSessionUuid(), sSessionUuid);
    compare("session1 Session Created (0)", session1.getSessionCreated(), nCreated);
    compare("session1 Session Updated (0)", session1.getSessionUpdated(), nUpdated);
    compare("session1 Session Expire At (0)", session1.getSessionExpireAt(), nExpiredAt);
    compare("session1 Session Custom (0)", session1.getSessionCustom().dump(), sJsonCustom);

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