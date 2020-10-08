#include <wsjcpp_unit_tests.h>
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// UnitTestJsonRpc20ParamDef

class UnitTestJsonRpc20ParamDef : public WsjcppUnitTestBase {
    public:
        UnitTestJsonRpc20ParamDef();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestJsonRpc20ParamDef)

UnitTestJsonRpc20ParamDef::UnitTestJsonRpc20ParamDef()
    : WsjcppUnitTestBase("UnitTestJsonRpc20ParamDef") {
}

// ---------------------------------------------------------------------

bool UnitTestJsonRpc20ParamDef::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestJsonRpc20ParamDef::executeTest() {
    
    {
        WsjcppJsonRpc20ParamDef paramDef;
        compare("Empty paramDef - name", paramDef.getName(), "");
        compare("Empty paramDef - getType", paramDef.getType(), "");
        compare("Empty paramDef - getRestrict", paramDef.getRestrict(), "required"); // default
        compare("Empty paramDef - getDescription", paramDef.getDescription(), "");
        compare("Empty paramDef - isRequired", paramDef.isRequired(), true);
        compare("Empty paramDef - isOptional", paramDef.isOptional(), false);
        compare("Empty paramDef - isInteger", paramDef.isInteger(), false);
        compare("Empty paramDef - isString", paramDef.isString(), false);
        compare("Empty paramDef - isBool", paramDef.isBool(), false);
        compare("Empty paramDef - isJson", paramDef.isJson(), false);

        nlohmann::json js_empty; 
        js_empty["description"] = "";
        js_empty["name"] = "";
        js_empty["restrict"] = "required";
        js_empty["type"] = "";
        compare("Empty paramDef - toJson", paramDef.toJson().dump(), js_empty.dump());

        compare("Empty paramDef - listOfStringValidators", paramDef.listOfStringValidators().size(), 0);
        compare("Empty paramDef - listOfIntegerValidators", paramDef.listOfIntegerValidators().size(), 0);
        compare("Empty paramDef - listOfJsonValidators", paramDef.listOfJsonValidators().size(), 0);
    }

    {
        WsjcppJsonRpc20ParamDef paramDef2("arg2", "Some argument222222");
        paramDef2.string_().required()
            .addValidator(new WsjcppValidatorURL());
        compare("paramDef2 - name", paramDef2.getName(), "arg2");
        compare("paramDef2 - getType", paramDef2.getType(), "string");
        compare("paramDef2 - getRestrict", paramDef2.getRestrict(), "required");
        compare("paramDef2 - getDescription", paramDef2.getDescription(), "Some argument222222");
        compare("paramDef2 - isRequired", paramDef2.isRequired(), true);
        compare("paramDef2 - isOptional", paramDef2.isOptional(), false);
        compare("paramDef2 - isInteger", paramDef2.isInteger(), false);
        compare("paramDef2 - isString", paramDef2.isString(), true);
        
        compare("paramDef2 - isJson", paramDef2.isJson(), false);
        compare("paramDef2 - isBool", paramDef2.isBool(), false);

        nlohmann::json js2; 
        js2["description"] = "Some argument222222";
        js2["name"] = "arg2";
        js2["restrict"] = "required";
        js2["type"] = "string";
        compare("paramDef2 - toJson", paramDef2.toJson().dump(), js2.dump());

        compare("paramDef2 - listOfStringValidators", paramDef2.listOfStringValidators().size(), 1);
        compare("paramDef2 - listOfIntegerValidators", paramDef2.listOfIntegerValidators().size(), 0);
        compare("paramDef2 - listOfJsonValidators", paramDef2.listOfJsonValidators().size(), 0);
    }

    {
        WsjcppJsonRpc20ParamDef paramDef3("arg3", "Some argument3");
        paramDef3.integer_().optional()
            .addValidator(new WsjcppValidatorIntegerMinValue(1))
            .addValidator(new WsjcppValidatorIntegerMaxValue(1000))
            ;
        compare("paramDef3 - name", paramDef3.getName(), "arg3");
        compare("paramDef3 - getType", paramDef3.getType(), "integer");
        compare("paramDef3 - getRestrict", paramDef3.getRestrict(), "optional");
        compare("paramDef3 - getDescription", paramDef3.getDescription(), "Some argument3");
        compare("paramDef3 - isRequired", paramDef3.isRequired(), false);
        compare("paramDef3 - isOptional", paramDef3.isOptional(), true);
        compare("paramDef3 - isInteger", paramDef3.isInteger(), true);
        compare("paramDef3 - isString", paramDef3.isString(), false);
        compare("paramDef3 - isJson", paramDef3.isJson(), false);
        compare("paramDef3 - isBool", paramDef3.isBool(), false);

        nlohmann::json js3; 
        js3["description"] = "Some argument3";
        js3["name"] = "arg3";
        js3["restrict"] = "optional";
        js3["type"] = "integer";
        compare("paramDef3 - toJson", paramDef3.toJson().dump(), js3.dump());

        compare("paramDef3 - listOfStringValidators", paramDef3.listOfStringValidators().size(), 0);
        compare("paramDef3 - listOfIntegerValidators", paramDef3.listOfIntegerValidators().size(), 2);
        compare("paramDef3 - listOfJsonValidators", paramDef3.listOfJsonValidators().size(), 0);
    }

    {
        WsjcppJsonRpc20ParamDef paramDef4("arg4_1ddd", "Some argument4");
        paramDef4.json_().optional();
            
        compare("paramDef4 - name", paramDef4.getName(), "arg4_1ddd");
        compare("paramDef4 - getType", paramDef4.getType(), "json");
        compare("paramDef4 - getRestrict", paramDef4.getRestrict(), "optional");
        compare("paramDef4 - getDescription", paramDef4.getDescription(), "Some argument4");
        compare("paramDef4 - isRequired", paramDef4.isRequired(), false);
        compare("paramDef4 - isOptional", paramDef4.isOptional(), true);
        compare("paramDef4 - isInteger", paramDef4.isInteger(), false);
        compare("paramDef4 - isString", paramDef4.isString(), false);
        compare("paramDef4 - isJson", paramDef4.isJson(), true);
        compare("paramDef4 - isBool", paramDef4.isBool(), false);

        nlohmann::json js4; 
        js4["description"] = "Some argument4";
        js4["name"] = "arg4_1ddd";
        js4["restrict"] = "optional";
        js4["type"] = "json";
        compare("paramDef4 - toJson", paramDef4.toJson().dump(), js4.dump());

        compare("paramDef4 - listOfStringValidators", paramDef4.listOfStringValidators().size(), 0);
        compare("paramDef4 - listOfIntegerValidators", paramDef4.listOfIntegerValidators().size(), 0);
        compare("paramDef4 - listOfJsonValidators", paramDef4.listOfJsonValidators().size(), 0);
        
    }

    {
        WsjcppJsonRpc20ParamDef paramDef5("arg5_0", "Some argument5");
        paramDef5.bool_().required();
        compare("paramDef5 - name", paramDef5.getName(), "arg5_0");
        compare("paramDef5 - getType", paramDef5.getType(), "boolean");
        compare("paramDef5 - getRestrict", paramDef5.getRestrict(), "required");
        compare("paramDef5 - getDescription", paramDef5.getDescription(), "Some argument5");
        compare("paramDef5 - isRequired", paramDef5.isRequired(), true);
        compare("paramDef5 - isOptional", paramDef5.isOptional(), false);
        compare("paramDef5 - isInteger", paramDef5.isInteger(), false);
        compare("paramDef5 - isString", paramDef5.isString(), false);
        compare("paramDef5 - isJson", paramDef5.isJson(), false);
        compare("paramDef5 - isBool", paramDef5.isBool(), true);

        nlohmann::json js5; 
        js5["description"] = "Some argument5";
        js5["name"] = "arg5_0";
        js5["restrict"] = "required";
        js5["type"] = "boolean";
        compare("paramDef5 - toJson", paramDef5.toJson().dump(), js5.dump());

        compare("paramDef5 - listOfStringValidators", paramDef5.listOfStringValidators().size(), 0);
        compare("paramDef5 - listOfIntegerValidators", paramDef5.listOfIntegerValidators().size(), 0);
        compare("paramDef5 - listOfJsonValidators", paramDef5.listOfJsonValidators().size(), 0);
    }
}

// ---------------------------------------------------------------------

bool UnitTestJsonRpc20ParamDef::doAfterTest() {
    // nothing
    return true;
}