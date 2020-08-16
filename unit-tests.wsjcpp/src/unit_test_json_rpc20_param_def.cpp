#include "unit_test_json_rpc20_param_def.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestJsonRpc20ParamDef)

UnitTestJsonRpc20ParamDef::UnitTestJsonRpc20ParamDef()
    : WsjcppUnitTestBase("UnitTestJsonRpc20ParamDef") {
}

// ---------------------------------------------------------------------

void UnitTestJsonRpc20ParamDef::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestJsonRpc20ParamDef::run() {
    bool bTestSuccess = true;
    
    {
        WsjcppJsonRpc20ParamDef paramDef;
        compareS(bTestSuccess, "Empty paramDef - name", paramDef.getName(), "");
        compareS(bTestSuccess, "Empty paramDef - getType", paramDef.getType(), "");
        compareS(bTestSuccess, "Empty paramDef - getRestrict", paramDef.getRestrict(), "");
        compareS(bTestSuccess, "Empty paramDef - getDescription", paramDef.getDescription(), "");
        compareB(bTestSuccess, "Empty paramDef - isRequired", paramDef.isRequired(), false);
        compareB(bTestSuccess, "Empty paramDef - isOptional", paramDef.isOptional(), false);
        compareB(bTestSuccess, "Empty paramDef - isInteger", paramDef.isInteger(), false);
        compareB(bTestSuccess, "Empty paramDef - isString", paramDef.isString(), false);
        compareB(bTestSuccess, "Empty paramDef - isBool", paramDef.isBool(), false);
        compareB(bTestSuccess, "Empty paramDef - isJson", paramDef.isJson(), false);

        nlohmann::json js_empty; 
        js_empty["description"] = "";
        js_empty["name"] = "";
        js_empty["restrict"] = "";
        js_empty["type"] = "";
        compareS(bTestSuccess, "Empty paramDef - toJson", paramDef.toJson().dump(), js_empty.dump());

        compareN(bTestSuccess, "Empty paramDef - listOfStringValidators", paramDef.listOfStringValidators().size(), 0);
        compareN(bTestSuccess, "Empty paramDef - listOfIntegerValidators", paramDef.listOfIntegerValidators().size(), 0);
        compareN(bTestSuccess, "Empty paramDef - listOfJsonValidators", paramDef.listOfJsonValidators().size(), 0);
    }

    {
        WsjcppJsonRpc20ParamDef paramDef2("arg2", "Some argument222222");
        paramDef2.string_().required()
            .addValidator(new WsjcppValidatorURL());
        compareS(bTestSuccess, "paramDef2 - name", paramDef2.getName(), "arg2");
        compareS(bTestSuccess, "paramDef2 - getType", paramDef2.getType(), "string");
        compareS(bTestSuccess, "paramDef2 - getRestrict", paramDef2.getRestrict(), "required");
        compareS(bTestSuccess, "paramDef2 - getDescription", paramDef2.getDescription(), "Some argument222222");
        compareB(bTestSuccess, "paramDef2 - isRequired", paramDef2.isRequired(), true);
        compareB(bTestSuccess, "paramDef2 - isOptional", paramDef2.isOptional(), false);
        compareB(bTestSuccess, "paramDef2 - isInteger", paramDef2.isInteger(), false);
        compareB(bTestSuccess, "paramDef2 - isString", paramDef2.isString(), true);
        
        compareB(bTestSuccess, "paramDef2 - isJson", paramDef2.isJson(), false);
        compareB(bTestSuccess, "paramDef2 - isBool", paramDef2.isBool(), false);

        nlohmann::json js2; 
        js2["description"] = "Some argument222222";
        js2["name"] = "arg2";
        js2["restrict"] = "required";
        js2["type"] = "string";
        compareS(bTestSuccess, "paramDef2 - toJson", paramDef2.toJson().dump(), js2.dump());

        compareN(bTestSuccess, "paramDef2 - listOfStringValidators", paramDef2.listOfStringValidators().size(), 1);
        compareN(bTestSuccess, "paramDef2 - listOfIntegerValidators", paramDef2.listOfIntegerValidators().size(), 0);
        compareN(bTestSuccess, "paramDef2 - listOfJsonValidators", paramDef2.listOfJsonValidators().size(), 0);
    }

    {
        WsjcppJsonRpc20ParamDef paramDef3("arg3", "Some argument3");
        paramDef3.integer_().optional()
            .addValidator(new WsjcppValidatorIntegerMinValue(1))
            .addValidator(new WsjcppValidatorIntegerMaxValue(1000))
            ;
        compareS(bTestSuccess, "paramDef3 - name", paramDef3.getName(), "arg3");
        compareS(bTestSuccess, "paramDef3 - getType", paramDef3.getType(), "integer");
        compareS(bTestSuccess, "paramDef3 - getRestrict", paramDef3.getRestrict(), "optional");
        compareS(bTestSuccess, "paramDef3 - getDescription", paramDef3.getDescription(), "Some argument3");
        compareB(bTestSuccess, "paramDef3 - isRequired", paramDef3.isRequired(), false);
        compareB(bTestSuccess, "paramDef3 - isOptional", paramDef3.isOptional(), true);
        compareB(bTestSuccess, "paramDef3 - isInteger", paramDef3.isInteger(), true);
        compareB(bTestSuccess, "paramDef3 - isString", paramDef3.isString(), false);
        compareB(bTestSuccess, "paramDef3 - isJson", paramDef3.isJson(), false);
        compareB(bTestSuccess, "paramDef3 - isBool", paramDef3.isBool(), false);

        nlohmann::json js3; 
        js3["description"] = "Some argument3";
        js3["name"] = "arg3";
        js3["restrict"] = "optional";
        js3["type"] = "integer";
        compareS(bTestSuccess, "paramDef3 - toJson", paramDef3.toJson().dump(), js3.dump());

        compareN(bTestSuccess, "paramDef3 - listOfStringValidators", paramDef3.listOfStringValidators().size(), 0);
        compareN(bTestSuccess, "paramDef3 - listOfIntegerValidators", paramDef3.listOfIntegerValidators().size(), 2);
        compareN(bTestSuccess, "paramDef3 - listOfJsonValidators", paramDef3.listOfJsonValidators().size(), 0);
    }

    {
        WsjcppJsonRpc20ParamDef paramDef4("arg4_1ddd", "Some argument4");
        paramDef4.json_().optional();
            
        compareS(bTestSuccess, "paramDef4 - name", paramDef4.getName(), "arg4_1ddd");
        compareS(bTestSuccess, "paramDef4 - getType", paramDef4.getType(), "json");
        compareS(bTestSuccess, "paramDef4 - getRestrict", paramDef4.getRestrict(), "optional");
        compareS(bTestSuccess, "paramDef4 - getDescription", paramDef4.getDescription(), "Some argument4");
        compareB(bTestSuccess, "paramDef4 - isRequired", paramDef4.isRequired(), false);
        compareB(bTestSuccess, "paramDef4 - isOptional", paramDef4.isOptional(), true);
        compareB(bTestSuccess, "paramDef4 - isInteger", paramDef4.isInteger(), false);
        compareB(bTestSuccess, "paramDef4 - isString", paramDef4.isString(), false);
        compareB(bTestSuccess, "paramDef4 - isJson", paramDef4.isJson(), true);
        compareB(bTestSuccess, "paramDef4 - isBool", paramDef4.isBool(), false);

        nlohmann::json js4; 
        js4["description"] = "Some argument4";
        js4["name"] = "arg4_1ddd";
        js4["restrict"] = "optional";
        js4["type"] = "json";
        compareS(bTestSuccess, "paramDef4 - toJson", paramDef4.toJson().dump(), js4.dump());

        compareN(bTestSuccess, "paramDef4 - listOfStringValidators", paramDef4.listOfStringValidators().size(), 0);
        compareN(bTestSuccess, "paramDef4 - listOfIntegerValidators", paramDef4.listOfIntegerValidators().size(), 0);
        compareN(bTestSuccess, "paramDef4 - listOfJsonValidators", paramDef4.listOfJsonValidators().size(), 0);
        
    }

    {
        WsjcppJsonRpc20ParamDef paramDef5("arg5_0", "Some argument5");
        paramDef5.bool_().required();
        compareS(bTestSuccess, "paramDef5 - name", paramDef5.getName(), "arg5_0");
        compareS(bTestSuccess, "paramDef5 - getType", paramDef5.getType(), "boolean");
        compareS(bTestSuccess, "paramDef5 - getRestrict", paramDef5.getRestrict(), "required");
        compareS(bTestSuccess, "paramDef5 - getDescription", paramDef5.getDescription(), "Some argument5");
        compareB(bTestSuccess, "paramDef5 - isRequired", paramDef5.isRequired(), true);
        compareB(bTestSuccess, "paramDef5 - isOptional", paramDef5.isOptional(), false);
        compareB(bTestSuccess, "paramDef5 - isInteger", paramDef5.isInteger(), false);
        compareB(bTestSuccess, "paramDef5 - isString", paramDef5.isString(), false);
        compareB(bTestSuccess, "paramDef5 - isJson", paramDef5.isJson(), false);
        compareB(bTestSuccess, "paramDef5 - isBool", paramDef5.isBool(), true);

        nlohmann::json js5; 
        js5["description"] = "Some argument5";
        js5["name"] = "arg5_0";
        js5["restrict"] = "required";
        js5["type"] = "boolean";
        compareS(bTestSuccess, "paramDef5 - toJson", paramDef5.toJson().dump(), js5.dump());

        compareN(bTestSuccess, "paramDef5 - listOfStringValidators", paramDef5.listOfStringValidators().size(), 0);
        compareN(bTestSuccess, "paramDef5 - listOfIntegerValidators", paramDef5.listOfIntegerValidators().size(), 0);
        compareN(bTestSuccess, "paramDef5 - listOfJsonValidators", paramDef5.listOfJsonValidators().size(), 0);
    }
    

    return bTestSuccess;
}

