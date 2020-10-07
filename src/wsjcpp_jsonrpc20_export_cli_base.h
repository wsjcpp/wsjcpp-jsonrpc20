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

        virtual bool doExportLib() = 0;

    protected:
        std::string TAG;

    private:
        std::string m_sExportDir;
        std::string m_sPackageName;
};

#endif //  WSJCPP_JSONRPC20_EXPORT_CLI_BASE_H