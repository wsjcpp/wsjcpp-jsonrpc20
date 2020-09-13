#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>
#include <wsjcpp_jsonrpc20_export_cli_python.h>

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
    
    std::string sExportDir = "./example-of-exported-client-libraries";

    WsjcppJsonRpc20ExportCliPython exportCliPython(
        "./example-of-exported/py3",
        "libwsjcppjson20client"
    );
    exportCliPython.setAuthorName("Evgenii Sopov");
    exportCliPython.setAuthorEmail("mrseakg@gmail.com");
    exportCliPython.setAppName(std::string(WSJCPP_APP_NAME));
    exportCliPython.setAppVersion(std::string(WSJCPP_APP_VERSION));
    exportCliPython.setUrl("https://github.com/wsjcpp/wsjcpp-jsonrpc20");
    exportCliPython.setDownloadUrl("https://github.com/wsjcpp/wsjcpp-jsonrpc20/archive/" + std::string(WSJCPP_APP_NAME) + ".tar.gz");
    exportCliPython.setKeywords({std::string(WSJCPP_APP_NAME), "wsjcpp", "wsjcpp-jsonrpc20", "example-python-client"});
    exportCliPython.addLoginMethod("auth_login", "token");
    exportCliPython.addLogoffMethod("auth_logoff");

    if (!exportCliPython.doExportLib()) {
        std::cout << "Failed!" << std::endl;
    } else {
        std::cout << "Success!" << std::endl;
    }

    // TODO your code here
    return 0;
}


