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
        void setKeywords(const std::vector<std::string> &vKeywords);
        void setLicense(const std::string &sLicenseType, const std::string &sLicenseURL);
        void setDefaultConnectionString(const std::string &sDefaultConnectionString);
        virtual bool doExportLib() override;

    private:
        std::string TAG;
        std::string m_sIssuesURL;
        std::string m_sRepositoryType;
        std::string m_sRepositoryURL;
        std::vector<std::string> m_vKeywords;
        std::string m_sLicenseType;
        std::string m_sLicenseURL;
        std::string m_sDefaultConnectionString;

        std::string m_sSampleUrlConnection;
        
        std::vector<std::pair<std::string, std::string>> m_vMethodsForKeepAuthToken;
        std::vector<std::string> m_vMethodsForClearAuthToken;

        std::vector<std::string> m_vEvents;

        bool prepareDirs();
        bool exportLibCliWebJSFile();

        void exportPackageJson();
        void exportAPImd();
        
        void exportLibCliWebServiceTSFile();
        void exportSampleHtmlFile();
};

#endif //  WSJCPP_JSONRPC20_EXPORT_CLI_WEBJS_H