#ifndef WSJCPP_JSONRPC20_EXPORT_CLI_BASE_H
#define WSJCPP_JSONRPC20_EXPORT_CLI_BASE_H

#include "wsjcpp_core.h"
#include "wsjcpp_jsonrpc20.h"
#include <vector>

class WsjcppJsonRpc20ExportCliBase {
    public:
        WsjcppJsonRpc20ExportCliBase(
            const std::string &sExportDir,
            const std::string &sPackageName
        );

        std::string getExportDir() const;
        std::string getPackageName() const;
        void setAppName(const std::string &sAppName);
        std::string getAppName() const;
        void setAppVersion(const std::string &sAppVersion);
        std::string getAppVersion() const;

        virtual bool doExportLib() = 0;

    protected:
        std::string TAG;

    private:
        std::string m_sExportDir;
        std::string m_sPackageName;
        std::string m_sAppName;
        std::string m_sAppVersion;
};

#endif //  WSJCPP_JSONRPC20_EXPORT_CLI_BASE_H