#include "wsjcpp_jsonrpc20.h"
#include <wsjcpp_core.h>

// ---------------------------------------------------------------------

/*! 
 * WsjcppJsonRpc20UserSession - all data by current user session
 * */

WsjcppJsonRpc20UserSession::WsjcppJsonRpc20UserSession() {
    TAG = "WsjcppJsonRpc20UserSession";
    m_nUserID = 0;
    m_sUserRole = "";
    m_sUserEmail = "";
    m_sUserUuid = "";
    m_sUserName = "";
    m_sSessionUuid = "";
    m_nSessionCreated = 0;
    m_nSessionUpdated = 0;
    m_nSessionExpireAt = 0;
    m_jsonSessionCustom = nlohmann::json{};
}

// ---------------------------------------------------------------------

WsjcppJsonRpc20UserSession::WsjcppJsonRpc20UserSession(nlohmann::json const& obj) : WsjcppJsonRpc20UserSession() {
    this->fillFrom(obj);
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::fillFrom(const nlohmann::json &obj) {
    if (obj.find("uuid") != obj.end()) {
        try {
            m_sSessionUuid = obj.at("uuid").get<std::string>();
        } catch (const std::exception &e) {
            WsjcppLog::err(TAG, "Something wrong param session.uuid in struct: "
                 + obj.dump() + "; error: " + std::string(e.what()));
            m_sSessionUuid = "";
        }
    } else {
        WsjcppLog::warn(TAG, "Not found param 'uuid' in struct");
        m_sSessionUuid = "";
    }

    if (obj.find("created") != obj.end()) {
        try {
            m_nSessionCreated = obj.at("created").get<long>();
        } catch (const std::exception &e) {
            WsjcppLog::err(TAG, "Something wrong param session.created in struct: "
                 + obj.dump() + "; error: " + std::string(e.what()));
            m_nSessionCreated = 0;
        }
    } else {
        WsjcppLog::warn(TAG, "Not found param 'created' in struct");
        m_nSessionCreated = 0;
    }

    if (obj.find("updated") != obj.end()) {
        try {
            m_nSessionUpdated = obj.at("updated").get<long>();
        } catch (const std::exception &e) {
            WsjcppLog::err(TAG, "Something wrong param session.updated in struct: "
                 + obj.dump() + "; error: " + std::string(e.what()));
            m_nSessionUpdated = 0;
        }
    } else {
        WsjcppLog::warn(TAG, "Not found param 'updated' in struct");
        m_nSessionUpdated = 0;
    }

    if (obj.find("expire_at") != obj.end()) {
        try {
            m_nSessionExpireAt = obj.at("expire_at").get<long>();
        } catch (const std::exception &e) {
            WsjcppLog::err(TAG, "Something wrong param session.expire_at in struct: "
                 + obj.dump() + "; error: " + std::string(e.what()));
            m_nSessionExpireAt = 0;
        }
    } else {
        WsjcppLog::warn(TAG, "Not found param 'expire_at' in struct");
        m_nSessionExpireAt = 0;
    }

    if (obj.find("custom") != obj.end()) {
        m_jsonSessionCustom = obj["custom"];
    } else {
        WsjcppLog::warn(TAG, "Not found param 'custom' in struct");
        m_jsonSessionCustom = nlohmann::json{};
    }

    if (obj.find("user") != obj.end()) {
        nlohmann::json user = obj.at("user");

        if (user.find("role") != user.end()) {
            try {
                m_sUserRole = user.at("role").get<std::string>();
            } catch (const std::exception &e) {
                WsjcppLog::err(TAG, "Something wrong param session.user.role in struct: "
                 + obj.dump() + "; error: " + std::string(e.what()));
                m_sUserRole = "";
            }
        } else {
            m_sUserRole = "";
        }

        if (user.find("id") != user.end()) {
            try {
                m_nUserID = user.at("id").get<int>();
            } catch (const std::exception &e) {
                WsjcppLog::err(TAG, "Something wrong param session.user.id in struct: "
                    + obj.dump() + "; error: " + std::string(e.what()));
                m_nUserID = 0;
            }
        } else {
            m_nUserID = 0;
        }
        
        // user.email
        if (user.find("email") != user.end()) {
            try {
                m_sUserEmail = user.at("email").get<std::string>();
            } catch (const std::exception &e) {
                WsjcppLog::err(TAG, "Something wrong param session.user.email in struct: "
                    + obj.dump() + "; error: " + std::string(e.what()));
                m_sUserEmail = "";
            }
        } else {
            m_sUserEmail = "";
        }

        // user.nick
        if (user.find("name") != user.end()) {
            try {
                m_sUserName = user.at("name").get<std::string>();
            } catch (const std::exception &e) {
                WsjcppLog::err(TAG, "Something wrong param session.user.name in struct: "
                    + obj.dump() + "; error: " + std::string(e.what()));
                m_sUserName = "";
            }
        } else {
            m_sUserName = "";
        }

        // user.uuid
        if (user.find("uuid") != user.end()) {
            try {
                m_sUserUuid = user.at("uuid").get<std::string>();
            } catch (const std::exception &e) {
                WsjcppLog::err(TAG, "Something wrong param session.user.uuid in struct: "
                    + obj.dump() + "; error: " + std::string(e.what()));
                m_sUserUuid = "";
            }
        } else {
            m_sUserUuid = "";
        }
    } else {
        WsjcppLog::warn(TAG, "Not found param 'user' in struct");
        m_nUserID = 0;
        m_sUserRole = "";
        m_sUserName = "";
        m_sUserUuid = "";
        m_sUserEmail = "";
    }
}

// ---------------------------------------------------------------------

nlohmann::json WsjcppJsonRpc20UserSession::toJson() {
    nlohmann::json jsonRet;
    jsonRet["uuid"] = m_sSessionUuid;
    jsonRet["created"] = m_nSessionCreated;
    jsonRet["updated"] = m_nSessionUpdated;
    jsonRet["expire_at"] = m_nSessionExpireAt;

    nlohmann::json jsonUser;
    jsonUser["id"] = m_nUserID;
    jsonUser["uuid"] = m_sUserUuid;
    jsonUser["name"] = m_sUserName;
    jsonUser["email"] = m_sUserEmail;
    jsonUser["role"] = m_sUserRole;
    jsonRet["user"] = jsonUser;

    jsonRet["custom"] = m_jsonSessionCustom;

    return jsonRet;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20UserSession::getSessionUuid() {
    return m_sSessionUuid;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setSessionUuid(const std::string& sSessionUuid) {
    m_sSessionUuid = sSessionUuid;
}


// ---------------------------------------------------------------------

long WsjcppJsonRpc20UserSession::getSessionCreated() {
    return m_nSessionCreated;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setSessionCreated(long nSessionCreated) {
    m_nSessionCreated = nSessionCreated;
}

// ---------------------------------------------------------------------

long WsjcppJsonRpc20UserSession::getSessionUpdated() {
    return m_nSessionUpdated;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setSessionUpdated(long nSessionUpdated) {
    m_nSessionUpdated = nSessionUpdated;
}

// ---------------------------------------------------------------------

long WsjcppJsonRpc20UserSession::getSessionExpireAt() {
    return m_nSessionExpireAt;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setSessionExpireAt(long nSessionExpireAt) {
    m_nSessionExpireAt = nSessionExpireAt;
}

// ---------------------------------------------------------------------

int WsjcppJsonRpc20UserSession::getUserId() {
    return m_nUserID;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setUserId(int nUserId) {
    m_nUserID = nUserId;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20UserSession::getUserUuid() {
    return m_sUserUuid;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setUserUuid(const std::string& sUserUuid) {
    m_sUserUuid = sUserUuid;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20UserSession::getUserName() {
    return m_sUserName;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setUserName(const std::string &sUserName) {
    m_sUserName = sUserName;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20UserSession::getUserEmail() {
    return m_sUserEmail;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setUserEmail(const std::string &sUserEmail) {
    m_sUserEmail = sUserEmail;
}

// ---------------------------------------------------------------------

std::string WsjcppJsonRpc20UserSession::getUserRole() {
    return m_sUserRole;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setUserRole(const std::string &sUserRole) {
    m_sUserRole = sUserRole;
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20UserSession::isAdmin() {
    return m_sUserRole == "admin";
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20UserSession::isUser() {
    return m_sUserRole == "user";
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20UserSession::isTester() {
    return m_sUserRole == "tester";
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20UserSession::hasRole() {
    return m_sUserRole != "";
}

// ---------------------------------------------------------------------

nlohmann::json WsjcppJsonRpc20UserSession::getSessionCustom() {
    return m_jsonSessionCustom;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20UserSession::setSessionCustom(const nlohmann::json &jsonSessionCustom) {
    m_jsonSessionCustom = jsonSessionCustom;
}

// ---------------------------------------------------------------------