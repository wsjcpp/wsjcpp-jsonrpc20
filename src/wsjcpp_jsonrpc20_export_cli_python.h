#ifndef WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H
#define WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H

#include "wsjcpp_jsonrpc20_export_cli_base.h"
#include <vector>
#include <map>

class WsjcppJsonRpc20ExportCliPython : public WsjcppJsonRpc20ExportCliBase {
    public:
        WsjcppJsonRpc20ExportCliPython(
            const std::string &sExportDir,
            const std::string &sPackageName
        );
        void setUrl(const std::string &sUrl);
        void setDownloadUrl(const std::string &sDownloadUrl);
        void setKeywords(const std::vector<std::string> &vKeywords);
        void addLoginMethod(const std::string &sMethod, const std::string &sResultVarName);
        void addLogoffMethod(const std::string &sMethod);

        virtual bool doExportLib() override;
    private:

        std::string m_sUrl;
        std::string m_sDownloadUrl;
        std::vector<std::string> m_vKeywords;
        std::vector<std::pair<std::string, std::string>> m_vMethodsForKeepAuthToken;
        std::vector<std::string> m_vMethodsForClearAuthToken;

        bool exportPrepareDirs();
        bool prepareReadmeMdIfNeed();
        bool exportSetupPy();
        bool exportAPImd();
        bool exportInitPy();
        bool exportClientPy();
};

#endif // WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H
