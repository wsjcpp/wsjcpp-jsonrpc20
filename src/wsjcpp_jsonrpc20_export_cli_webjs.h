#ifndef WSJCPP_JSONRPC20_EXPORT_CLI_WEBJS_H
#define WSJCPP_JSONRPC20_EXPORT_CLI_WEBJS_H

#include "wsjcpp_jsonrpc20_export_cli_base.h"
#include <vector>

class WsjcppJsonRpc20ExportCliWebJs : public WsjcppJsonRpc20ExportCliBase {
    public:
        WsjcppJsonRpc20ExportCliWebJs(
            const std::string &sExportDir,
            const std::string &sPackageName
        );
        // TODO homepage
        void setIssuesURL(const std::string &sIssuesURL);
        void setRepository(const std::string &sRepositoryType, const std::string &sRepositoryURL);
        void setLicense(const std::string &sLicenseType, const std::string &sLicenseURL);
        virtual bool doExportLib() override;

    private:
        std::string TAG;
        std::string m_sIssuesURL;
        std::string m_sRepositoryType;
        std::string m_sRepositoryURL;
        std::string m_sLicenseType;
        std::string m_sLicenseURL;
        

        std::string m_sSampleUrlConnection;

        std::vector<std::string> m_vEvents;

        bool prepareDirs();
        bool exportLibCliWebJSFile();

        bool exportPackageJson();
        bool exportAPImd();
        bool exportLibCliWebServiceTSFile();
        bool exportSampleHtmlFile();
};

#endif //  WSJCPP_JSONRPC20_EXPORT_CLI_WEBJS_H