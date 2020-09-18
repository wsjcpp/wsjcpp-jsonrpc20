#ifndef UNIT_TEST_REQUEST_PARSE_INCOME_DATA_H
#define UNIT_TEST_REQUEST_PARSE_INCOME_DATA_H

#include <wsjcpp_unit_tests.h>

class UnitTestRequestParseIncomeData : public WsjcppUnitTestBase {
    public:
        UnitTestRequestParseIncomeData();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_REQUEST_PARSE_INCOME_DATA_H

