#ifndef UNIT_TEST_REQUEST_SERVER_API_H
#define UNIT_TEST_REQUEST_SERVER_API_H

#include <wsjcpp_unit_tests.h>

class UnitTestRequestServerApi : public WsjcppUnitTestBase {
    public:
        UnitTestRequestServerApi();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_REQUEST_SERVER_API_H

