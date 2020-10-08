#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>
#include <wsjcpp_jsonrpc20_export_cli_python.h>
#include <wsjcpp_jsonrpc20_export_cli_webjs.h>

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_APP_NAME);
    std::string appVersion = std::string(WSJCPP_APP_VERSION);
    if (!WsjcppCore::dirExists(".logs")) {
        WsjcppCore::makeDir(".logs");
    }
    WsjcppLog::setPrefixLogFile("wsjcpp");
    WsjcppLog::setLogDirectory(".logs");

    std::cout << "Generate client python library" << std::endl;

    // export webjs
    WsjcppJsonRpc20ExportCliPython exportCliPython(
        "./example-of-exported/py3",
        "libwsjcppjson20client"
    );
    exportCliPython.setAuthorName("Evgenii Sopov");
    exportCliPython.setAuthorEmail("mrseakg@gmail.com");
    exportCliPython.setAppName(std::string(WSJCPP_APP_NAME));
    exportCliPython.setAppVersion(std::string(WSJCPP_APP_VERSION));
    exportCliPython.setClassName("SomeClient");
    exportCliPython.setUrl("https://github.com/wsjcpp/wsjcpp-jsonrpc20");
    exportCliPython.setDownloadUrl("https://github.com/wsjcpp/wsjcpp-jsonrpc20/archive/" + std::string(WSJCPP_APP_NAME) + ".tar.gz");
    exportCliPython.setKeywords({std::string(WSJCPP_APP_NAME), "wsjcpp", "wsjcpp-jsonrpc20", "example-python-client"});
    exportCliPython.addLoginMethod("auth_login", "token");
    exportCliPython.addLoginMethod("auth_token", "token");
    exportCliPython.addLogoffMethod("auth_logoff");

    if (!exportCliPython.doExportLib()) {
        std::cout << "Python Client Library export failed!" << std::endl;
    } else {
        std::cout << "Python Client Library export success!" << std::endl;
    }

    // export WebJS

    std::cout << "Generate client WebJS library" << std::endl;
    WsjcppJsonRpc20ExportCliWebJs exportCliWebJs(
        "./example-of-exported/webjs",
        "libwsjcppjson20client"
    );
    exportCliWebJs.setAuthorName("Evgenii Sopov");
    exportCliWebJs.setAuthorEmail("mrseakg@gmail.com");
    exportCliWebJs.setAppName(std::string(WSJCPP_APP_NAME));
    exportCliWebJs.setClassName("SomeClient");
    exportCliWebJs.setAppVersion(std::string(WSJCPP_APP_VERSION));
    exportCliWebJs.setIssuesURL("https://github.com/wsjcpp/wsjcpp-jsonrpc20/issues");
    exportCliWebJs.setRepository("git", "https://github.com/wsjcpp/wsjcpp-jsonrpc20.git");
    exportCliWebJs.setKeywords({std::string(WSJCPP_APP_NAME), "wsjcpp", "jsonrpc20", "example-client-webjs"});
    exportCliWebJs.setLicense("MIT", "https://raw.githubusercontent.com/wsjcpp/wsjcpp-jsonrpc20/master/LICENSE");
    exportCliWebJs.setDefaultConnectionString("ws://localhost:1234/");
    
    // exportCliWebJs.addLoginMethod("auth_login", "token");
    // exportCliWebJs.addLoginMethod("auth_token", "token");
    // exportCliWebJs.addLogoffMethod("auth_logoff");

    if (!exportCliWebJs.doExportLib()) {
        std::cout << "WebJS Client Library export failed!" << std::endl;
    } else {
        std::cout << "WebJS Client Library export success!" << std::endl;
    }

    return 0;
}


