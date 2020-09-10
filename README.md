# wsjcpp-jsonrpc20

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp-jsonrpc20.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp-jsonrpc20)

C++ Implementation for JsonRPC 2.0

## Features

* Collect all handlers for jsonrpc20
* Including system of define validators
* 


## Integration

### via wsjcpp

```
$ wsjcpp install https://github.com/wsjcpp/wsjcpp-jsonrpc20:master
```

### Include files

* src.wsjcpp/nlohmann_json/json.hpp
* src.wsjcpp/wsjcpp_core.h
* src.wsjcpp/wsjcpp_validators/wsjcpp_validators.h
* src.wsjcpp/wsjcpp_validators/wsjcpp_validators.cpp
* src/wsjcpp_jsonrpc20.h
* src/wsjcpp_jsonrpc20.cpp
* src/wsjcpp_jsonrpc20_export_cli_python.h
* src/wsjcpp_jsonrpc20_export_cli_python.cpp

## Example 

``` cpp

// method: order_remove or remove_order

MethodJsonRpc20_OrderRemove::MethodJsonRpc20_OrderRemove()
    : WsjcppJsonRpc20Base({"order_remove", "remove_order"}, "Remove order by id") {
    
    // restriction for different roles
    setAccessUnauthorized(false); // this define "false" says that UserSession will be not nullptr
    setAccessUser(true);
    setAccessAdmin(true);

    // just information for documentation
    setActivatedFromVersion("0.2.32");

    // validation and description input fields
    requireIntegerParam("id", "Id of user");
}

void MethodJsonRpc20_OrderRemove::handle(ModelRequest *pRequest) {
    WsjcppUserSession *pUserSession = pRequest->getUserSession();
    
    int nId = pRequest->getInputInteger("id", -1);

    // find id in database if not then return NOT_FOUND

    if (nId == -1) {
        pRequest->fail(404, "NOT_FOUND");
        return;
    }

    // do remove order here

    nlohmann::json jsonResponse;
    pRequest->done(jsonResponse);
}

```