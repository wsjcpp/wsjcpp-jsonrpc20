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

        virtual bool doExportLib() override;
    private:

        std::string m_sUrl;
        std::string m_sDownloadUrl;

        bool exportPrepareDirs();
        bool prepareReadmeMdIfNeed();
        bool exportSetupPy();
        bool exportAPImd();
        bool exportInitPy();
        bool exportClientPy();
};

#endif // WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H
