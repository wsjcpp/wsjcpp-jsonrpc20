#ifndef UNIT_TEST_PARSING_REQUEST_PARAMS_H
#define UNIT_TEST_PARSING_REQUEST_PARAMS_H

#include <wsjcpp_unit_tests.h>

class UnitTestParsingRequestParams : public WsjcppUnitTestBase {
    public:
        UnitTestParsingRequestParams();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_PARSING_REQUEST_PARAMS_H

