#ifndef WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H
#define WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H

#include <string>
#include <vector>

class WsjcppJsonRpc20ExportCliPython {
    public:
        WsjcppJsonRpc20ExportCliPython(
            const std::string &sExportDir,
            const std::string &sPackageName
        );
        void setAuthorName(const std::string &sAuthorName);
        void setAuthorEmail(const std::string &sAuthorEmail);
        void setAppName(const std::string &sAppName);
        void setAppVersion(const std::string &sAppVersion);
        void setClassName(const std::string &sClassName);
        void setUrl(const std::string &sUrl);
        void setDownloadUrl(const std::string &sDownloadUrl);
        void setKeywords(const std::vector<std::string> &vKeywords);

        bool doExportLib();
    private:
        std::string TAG;
        std::string m_sExportDir;
        std::string m_sPackageName;
        std::string m_sAuthorName;
        std::string m_sAuthorEmail;
        std::string m_sAppName;
        std::string m_sAppVersion;
        std::string m_sClassName;
        std::string m_sUrl;
        std::string m_sDownloadUrl;
        std::vector<std::string> m_vKeywords;

        bool exportPrepareDirs();
        bool prepareReadmeMdIfNeed();
        bool exportSetupPy();
        bool exportAPImd();
        bool export__init__py();
        
};

#endif // WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H
