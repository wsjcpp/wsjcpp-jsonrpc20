#ifndef UNIT_TEST_JSON_RPC20_USER_SESSION_H
#define UNIT_TEST_JSON_RPC20_USER_SESSION_H

#include <wsjcpp_unit_tests.h>

class UnitTestJsonRpc20UserSession : public WsjcppUnitTestBase {
    public:
        UnitTestJsonRpc20UserSession();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_JSON_RPC20_USER_SESSION_H

