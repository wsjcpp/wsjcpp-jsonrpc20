#include "wsjcpp_jsonrpc20_export_cli_base.h"
#include <iomanip> // for put_time

// ---------------------------------------------------------------------
// WsjcppJsonRpc20ExportCliBase

WsjcppJsonRpc20ExportCliBase::WsjcppJsonRpc20ExportCliBase(
    const std::string &sExporterName,
    const std::string &sExportDir,
    const std::string &sPackageName
) {
    TAG = "WsjcppJsonRpc20ExportCliBase";
    m_sExporterName = sExporterName;
    m_sExportDir = WsjcppCore::doNormalizePath(sExportDir);
    m_sPackageName = sPackageName;
    m_sAppName = "unknown";
    m_sAppVersion = "unknown";
    m_sAuthorName = "Unknown";
    m_sAuthorEmail = "unknown";
    m_sClassName = "Unknown";
    m_sDefaultConnectionString = "ws://localhost:1234/";

    // generate DateNow in one time on start
    std::time_t t = std::time(nullptr);
    std::stringstream buffer;
    buffer << std::put_time(std::gmtime(&t), "%d %b %Y");
    m_sDateNow = buffer.str();
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getExporterName() const {
    return m_sExporterName;
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

void WsjcppJsonRpc20ExportCliBase::setAppName(const std::string &sAppName) {
    m_sAppName = sAppName;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getAppName() const {
    return m_sAppName;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliBase::setAppVersion(const std::string &sAppVersion) {
    // https://www.python.org/dev/peps/pep-0440/
    // [N!]N(.N)*[{a|b|rc}N][.postN][.devN]
    // TODO regexp 
    m_sAppVersion = sAppVersion;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getAppVersion() const {
    return m_sAppVersion;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliBase::setAuthorName(const std::string &sAuthorName) {
    m_sAuthorName = sAuthorName;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getAuthorName() const {
    return m_sAuthorName;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliBase::setAuthorEmail(const std::string &sAuthorEmail) {
    m_sAuthorEmail = sAuthorEmail;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getAuthorEmail() const {
    return m_sAuthorEmail;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliBase::setClassName(const std::string &sClassName) {
    m_sClassName = sClassName;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getClassName() const {
    return m_sClassName;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliBase::setKeywords(const std::vector<std::string> &vKeywords) {
    m_vKeywords = vKeywords;
}

// ---------------------------------------------------------------------

std::vector<std::string> WsjcppJsonRpc20ExportCliBase::getKeywords() const {
    return m_vKeywords;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliBase::setDefaultConnectionString(const std::string &sDefaultConnectionString) {
    m_sDefaultConnectionString = sDefaultConnectionString;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getDefaultConnectionString() const {
    return m_sDefaultConnectionString;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20ExportCliBase::getDateNow() const {
    return m_sDateNow;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliBase::addLoginMethod(const std::string &sMethod, const std::string &sResultVarName) {
    m_vMethodsForKeepAuthToken.push_back(std::pair<std::string,std::string>(sMethod, sResultVarName));
}

// ---------------------------------------------------------------------

std::vector<std::pair<std::string, std::string>> WsjcppJsonRpc20ExportCliBase::getLoginMethods() const {
    return m_vMethodsForKeepAuthToken;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliBase::addLogoffMethod(const std::string &sMethod) {
    m_vMethodsForClearAuthToken.push_back(sMethod);
}

// ---------------------------------------------------------------------

std::vector<std::string> WsjcppJsonRpc20ExportCliBase::getLogoffMethods() const {
    return m_vMethodsForClearAuthToken;
}