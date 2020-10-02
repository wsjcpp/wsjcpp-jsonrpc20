# wsjcpp-jsonrpc20

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp-jsonrpc20.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp-jsonrpc20) [![Total alerts](https://img.shields.io/lgtm/alerts/g/wsjcpp/wsjcpp-jsonrpc20.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-jsonrpc20/alerts/) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wsjcpp/wsjcpp-jsonrpc20.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-jsonrpc20/context:cpp) [![Language grade: Python](https://img.shields.io/lgtm/grade/python/g/wsjcpp/wsjcpp-jsonrpc20.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-jsonrpc20/context:python) [![deepcode](https://www.deepcode.ai/api/gh/badge?key=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJwbGF0Zm9ybTEiOiJnaCIsIm93bmVyMSI6IndzamNwcCIsInJlcG8xIjoid3NqY3BwLWpzb25ycGMyMCIsImluY2x1ZGVMaW50IjpmYWxzZSwiYXV0aG9ySWQiOjE1NjQxLCJpYXQiOjE2MDE2MTM0MTh9.gErsnFaMiBhySNjNeNqAjFgxFP41QJZVYeJJffWmaDw)](https://www.deepcode.ai/app/gh/wsjcpp/wsjcpp-jsonrpc20/_/dashboard?utm_content=gh%2Fwsjcpp%2Fwsjcpp-jsonrpc20)

C++ Implementation for JsonRPC 2.0 (oriented on websockets)

## Features

* Collect all handlers for jsonrpc20
* Including system of define validators

## Integration

### via wsjcpp

```
$ wsjcpp install https://github.com/wsjcpp/wsjcpp-jsonrpc20:master
```

### Include files

* src.wsjcpp/nlohmann_json/json.hpp
* src.wsjcpp/wsjcpp_core/wsjcpp_core.h
* src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp
* src.wsjcpp/wsjcpp_validators/wsjcpp_validators.h
* src.wsjcpp/wsjcpp_validators/wsjcpp_validators.cpp
* src/wsjcpp_jsonrpc20.h
* src/wsjcpp_jsonrpc20.cpp
* src/wsjcpp_jsonrpc20_export_cli_python.h
* src/wsjcpp_jsonrpc20_export_cli_python.cpp

## Prepare handler

### via wsjcpp

```
$ wsjcpp generate WsjcppJsonRpc20Handler GameCreate
```

Will be generated new files 

- ./src/wsjcpp_json_rpc20_handler_game_create.h
- ./src/wsjcpp_json_rpc20_handler_game_create.cpp

And automaticly included to CMakeLists.txt between `#### BEGIN_WSJCPP_APPEND` and `#### END_WSJCPP_APPEND`

Like this:
```
#### BEGIN_WSJCPP_APPEND
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_json_rpc20_handler_game_create.h")
list (APPEND WSJCPP_SOURCES "./src/wsjcpp_json_rpc20_handler_game_create.cpp")
#### END_WSJCPP_APPEND
```

They will contains class `WsjcppJsonRpc20HandlerGameCreate` with method `game_create`


### code sample

File `./src/wsjcpp_json_rpc20_handler_game_create.h`:

``` cpp
#ifndef WSJCPP_JSON_RPC20_HANDLER_GAME_CREATE_H
#define WSJCPP_JSON_RPC20_HANDLER_GAME_CREATE_H

#include <wsjcpp_jsonrpc20.h>

class WsjcppJsonRpc20HandlerGameCreate : public WsjcppJsonRpc20HandlerBase {
    public:
        WsjcppJsonRpc20HandlerGameCreate();
        virtual void handle(WsjcppJsonRpc20Request *pRequest) override;
};

#endif // WSJCPP_JSON_RPC20_HANDLER_GAME_CREATE_H
```

File `./src/wsjcpp_json_rpc20_handler_game_create.cpp`:

``` cpp
#include "wsjcpp_json_rpc20_handler_game_create.h"
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>

// ---------------------------------------------------------------------
// WsjcppJsonRpc20HandlerGameCreate

WsjcppJsonRpc20HandlerGameCreate::WsjcppJsonRpc20HandlerGameCreate() 
: WsjcppJsonRpc20HandlerBase("game_create", "TODO description") {
    TAG = "WsjcppJsonRpc20HandlerGameCreate";
    // setAccessUnauthorized(true);
    // setAccessUser(true);
    // setAccessTester(true);
    // setAccessAdmin(true);
    // void setActivatedFromVersion("v0.0.1"); // TODO authomatic set WSJCPP_APP_VERSION
    // void setDeprecatedFromVersion("");

    // description of input params
    // requireStringParam("uuid", "object uuid")
    //    .addValidator(new WsjcppValidatorUUID());
    // optionalStringParam("name", "Name of object")
    //    .addValidator(new WsjcppValidatorStringLength(3,10));

    // requireIntegerParam("cost", "Name of object")
    //    .addValidator(new WsjcppValidatorIntegerMinValue(3))
    //    .addValidator(new WsjcppValidatorIntegerMaxValue(1000));
    // optionalIntegerParam("age", "Name of object")
    //    .addValidator(new WsjcppValidatorIntegerMinValue(0))

    // requireBooleanParam("public", "True if object is public");
    // optionalBooleanParam("activated", "If object can handle");
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20HandlerGameCreate::handle(WsjcppJsonRpc20Request *pRequest) {
    WsjcppLog::err(TAG, "Not implemented");
    // TODO
    pRequest->fail(WsjcppJsonRpc20Error(501, "NOT_IMPLEMENTED"));
}
```


## Automaticly generate client libraries on different languages

### Generate Python Library + PyPi Package

``` cpp

#include <wsjcpp_jsonrpc20_export_cli_python.h>
#include <iostream>
... 
void main() {
    std::string sExportDir = "./example-of-exported-client-libraries";

    WsjcppJsonRpc20ExportCliPython exportCliPython(
        "./example-of-exported/py3",
        "libwsjcppjson20client"
    );
    exportCliPython.setAuthorName("Evgenii Sopov");
    exportCliPython.setAuthorEmail("mrseakg@gmail.com");
    exportCliPython.setAppName(std::string(WSJCPP_APP_NAME));
    exportCliPython.setAppVersion(std::string(WSJCPP_APP_VERSION));
    exportCliPython.setUrl("https://github.com/user/repo");
    exportCliPython.setDownloadUrl("https://github.com/user/repo/archive/" + std::string(WSJCPP_APP_NAME) + ".tar.gz");
    exportCliPython.setKeywords({std::string(WSJCPP_APP_NAME), "wsjcpp", "wsjcpp-jsonrpc20", "example-python-client"});

    if (!exportCliPython.doExportLib()) {
        std::cout << "Failed!" << std::endl;
    } else {
        std::cout << "Success!" << std::endl;
    }
}
```

Usefull (official docs): https://packaging.python.org/tutorials/packaging-projects/


In next step you need:

```
$ cd ./example-of-exported/py3
$ python3 setup.py sdist bdist_wheel
... here will prepared dist/* directory
$ twine check dist/*
Checking dist/libwsjcppjson20client-0.0.2-py3-none-any.whl: PASSED
Checking dist/libwsjcppjson20client-0.0.2.tar.gz: PASSED
$ python3 -m pip install --user --upgrade twine
$ python3 -m twine upload dist/*
... here you need registered account on pypi
```

