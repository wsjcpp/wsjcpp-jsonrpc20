#ifndef WSJCPP_JSONRPC20_EXPORT_CLI_BASE_H
#define WSJCPP_JSONRPC20_EXPORT_CLI_BASE_H

#include "wsjcpp_core.h"
#include "wsjcpp_jsonrpc20.h"
#include <vector>

class WsjcppJsonRpc20ExportCliBase {
    public:
        WsjcppJsonRpc20ExportCliBase(
            const std::string &sExporterName,
            const std::string &sExportDir,
            const std::string &sPackageName
        );
        std::string getExporterName() const;
        std::string getExportDir() const;
        std::string getPackageName() const;
        void setAppName(const std::string &sAppName);
        std::string getAppName() const;
        void setAppVersion(const std::string &sAppVersion);
        std::string getAppVersion() const;
        void setAuthorName(const std::string &sAuthorName);
        std::string getAuthorName() const;
        void setAuthorEmail(const std::string &sAuthorEmail);
        std::string getAuthorEmail() const;
        void setClassName(const std::string &sClassName);
        std::string getClassName() const;
        void setKeywords(const std::vector<std::string> &vKeywords);
        std::vector<std::string> getKeywords() const;
        void setDefaultConnectionString(const std::string &sDefaultConnectionString);
        std::string getDefaultConnectionString() const;
        std::string getDateNow() const;
        void addLoginMethod(const std::string &sMethod, const std::string &sResultVarName);
        std::vector<std::pair<std::string, std::string>> getLoginMethods() const;
        void addLogoffMethod(const std::string &sMethod);
        std::vector<std::string> getLogoffMethods() const;

        virtual bool doExportLib() = 0;

    protected:
        std::string TAG;

    private:
        std::string m_sExporterName;
        std::string m_sExportDir;
        std::string m_sPackageName;
        std::string m_sAppName;
        std::string m_sAppVersion;
        std::string m_sClassName;
        std::string m_sAuthorName;
        std::string m_sAuthorEmail;
        std::vector<std::string> m_vKeywords;
        std::string m_sDefaultConnectionString;
        std::string m_sDateNow;
        std::vector<std::pair<std::string, std::string>> m_vMethodsForKeepAuthToken;
        std::vector<std::string> m_vMethodsForClearAuthToken;
};

#endif //  WSJCPP_JSONRPC20_EXPORT_CLI_BASE_H