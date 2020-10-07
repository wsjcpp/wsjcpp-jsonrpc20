#include "wsjcpp_jsonrpc20_export_cli_base.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip> // put_time
#include <ctime>
#include <sstream>

// ---------------------------------------------------------------------
// WsjcppJsonRpc20ExportCliBase

WsjcppJsonRpc20ExportCliBase::WsjcppJsonRpc20ExportCliBase(
    const std::string &sExportDir,
    const std::string &sPackageName
) {
    TAG = "WsjcppJsonRpc20ExportCliBase";
    m_sExportDir = WsjcppCore::doNormalizePath(sExportDir);
    m_sPackageName = sPackageName;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getExportDir() const {
    return m_sExportDir;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getPackageName() const {
    return m_sPackageName;
}

// ---------------------------------------------------------------------