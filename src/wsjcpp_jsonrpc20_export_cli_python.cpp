#include "wsjcpp_jsonrpc20_export_cli_python.h"

#include <wsjcpp_core.h>
#include <wsjcpp_jsonrpc20.h>
#include <iostream>
// #include <iomanip>
#include <algorithm>
// #include <sys/types.h>
// #include <sys/stat.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip> // put_time
#include <ctime>
#include <sstream>

// ---------------------------------------------------------------------

class PyCodeLine{
    PyCodeLine *m_pParent;
    std::string m_sLine;
    std::vector<PyCodeLine *> m_vLines;
public:
    
    PyCodeLine() {
        m_pParent = NULL;
        m_sLine = "";
    }

    PyCodeLine(PyCodeLine *parent, const std::string &sLine) {
        m_pParent = parent;
        m_sLine = sLine;
    }

    ~PyCodeLine() {
        if (m_pParent == NULL) {
            std::cout << "destruct root \n";
        } else {
            std::cout << "destruct something else [" << m_sLine << "]\n";
        }
    }

    PyCodeLine *addLine(const std::string &sLine) {
        PyCodeLine *pPyCodeLine = new PyCodeLine(this,sLine);
        m_vLines.push_back(pPyCodeLine);
        return pPyCodeLine;
    }

    PyCodeLine *getParent() {
        return m_pParent;
    }

    std::string getLine() {
        return m_sLine;
    }

    PyCodeLine *findRoot() {
        if (m_pParent == NULL) {
            return this;
        }
        return m_pParent->findRoot();
    }

    void print(std::ofstream &__init__, std::string intent = "") {
        if (m_pParent != NULL) {
            __init__ << intent << m_sLine << std::endl;
            intent += "    ";
        }
        for (int i = 0; i < m_vLines.size(); i++) {
            m_vLines[i]->print(__init__, intent);
        }
    }
};

// ---------------------------------------------------------------------

class PyCodeBuilder {

private:
    PyCodeLine *m_pCurr = NULL;

public:
    PyCodeBuilder() {
        m_pCurr = new PyCodeLine();
    }

    ~PyCodeBuilder() {
        // std::cout << "destruct something else [" << m_pCurr->getLine() << "]\n";
    }

    PyCodeBuilder &add(const std::string &sLine) {
        m_pCurr->addLine(sLine);
        return *this;
    }
    PyCodeBuilder &add(const std::vector<std::string> &vLines) {
        for (int i = 0; i < vLines.size(); i++) {
            m_pCurr->addLine(vLines[i]);
        }
        return *this;
    }
    PyCodeBuilder &sub(const std::string &sLine) {
        m_pCurr = m_pCurr->addLine(sLine);
        return *this;
    }
    PyCodeBuilder &end() {
        PyCodeLine *p = m_pCurr->getParent();
        if (p != NULL) {
            m_pCurr = p;
        } else {
            std::cout << "Wrong called end function" << std::endl;
        }
        return *this;
    }

    void print(std::ofstream &__init__) {
        PyCodeLine *pRoot = m_pCurr->findRoot();
        pRoot->print(__init__);
    };
};


// ---------------------------------------------------------------------
// WsjcppJsonRpc20ExportCliPython

WsjcppJsonRpc20ExportCliPython::WsjcppJsonRpc20ExportCliPython(
    const std::string &sExportDir,
    const std::string &sPackageName
) {
    TAG = "WsjcppJsonRpc20ExportCliPython";
    m_sExportDir = WsjcppCore::doNormalizePath(sExportDir);
    m_sPackageName = sPackageName;
    m_sAuthorName = "Unknown";
    m_sAuthorEmail = "unknown";
    m_sAppName = "unknown";
    m_sAppVersion = "unknown";
    m_sClassName = "SomeClient";
    m_sUrl = "none";
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::setAuthorName(const std::string &sAuthorName) {
    m_sAuthorName = sAuthorName;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::setAuthorEmail(const std::string &sAuthorEmail) {
    m_sAuthorEmail = sAuthorEmail;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::setAppName(const std::string &sAppName) {
    m_sAppName = sAppName;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::setAppVersion(const std::string &sAppVersion) {
    // https://www.python.org/dev/peps/pep-0440/
    // [N!]N(.N)*[{a|b|rc}N][.postN][.devN]
    // TODO regexp 
    m_sAppVersion = sAppVersion;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::setClassName(const std::string &sClassName) {
    m_sClassName = sClassName;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::setUrl(const std::string &sUrl) {
    m_sUrl = sUrl;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::setDownloadUrl(const std::string &sDownloadUrl) {
    m_sDownloadUrl = sDownloadUrl;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::setKeywords(const std::vector<std::string> &vKeywords) {
    m_vKeywords = vKeywords;
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::addLoginMethod(const std::string &sMethod, const std::string &sResultVarName) {
    m_vMethodsForKeepAuthToken.push_back(std::pair<std::string,std::string>(sMethod, sResultVarName));
}

// ---------------------------------------------------------------------

void WsjcppJsonRpc20ExportCliPython::addLogoffMethod(const std::string &sMethod) {
    m_vMethodsForClearAuthToken.push_back(sMethod);
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20ExportCliPython::doExportLib() {
    if (!this->exportPrepareDirs()) {
        return false;
    }

    if (!this->prepareReadmeMdIfNeed()) {
        return false;
    }

    if (!this->exportSetupPy()) {
        return false;
    }

    if (!this->exportAPImd()) {
        return false;
    }

    if (!this->exportInitPy()) {
        return false;
    }

    if (!this->exportClientPy()) {
        return false;
    }

    return true;
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20ExportCliPython::exportPrepareDirs() {
    std::vector<std::string> vCreateDirs;
    std::vector<std::string> vSplited = WsjcppCore::split(m_sExportDir, "/");
    std::string sExportDir = "";
    for (int i = 0; i < vSplited.size(); i++) {
        if (i > 0) {
            sExportDir += "/";
        }
        sExportDir += vSplited[i];
        sExportDir = WsjcppCore::doNormalizePath(sExportDir);
        vCreateDirs.push_back(sExportDir);
    }
    sExportDir = WsjcppCore::doNormalizePath(sExportDir + "/" + m_sPackageName);
    vCreateDirs.push_back(sExportDir);

    for (int i = 0; i < vCreateDirs.size(); i++) {
        std::string sDir = vCreateDirs[i];
        WsjcppLog::info(TAG, "Info: " + sDir);
        
        if (!WsjcppCore::dirExists(sDir)) {
            if (!WsjcppCore::makeDir(sDir)) {
                WsjcppLog::err(TAG, "Could not create directory: " + sDir);
                return false;
            } else {
                WsjcppLog::ok(TAG, "Created directory: " + sDir);
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20ExportCliPython::prepareReadmeMdIfNeed() {
    std::string sReadmeMd = m_sExportDir + "/README.md";
    if (!WsjcppCore::fileExists(sReadmeMd)) {
        std::string sContentReadme = 
            "#" + m_sPackageName + "\n\n"
            + m_sClassName + " Python Library for " + m_sAppName + "\n\n"
            + "## Install \n\n"
            + "```\n"
            + "$ pip3 install " + m_sPackageName + " --upgrade\n"
            + "```\n\n"
            + "## Example code\n\n"
            + "```\n"
            + "#!/usr/bin/env python3\n"
            + "# -*- coding: utf-8 -*-\n"
            + "from " + m_sPackageName + " import " + m_sClassName + "\n\n"
            + "client = " + m_sClassName + "(\"ws://host/ws-api/\")\n\n"
            + "resp = client.server_api({})\n\n"
            + "print(resp)\n"
            + "```\n\n"
            + "Full description API here: [API.md](./API.md)";
        WsjcppCore::writeFile(sReadmeMd, sContentReadme);
        WsjcppLog::warn(TAG, "Generated once, so please read and update if need: '" + sReadmeMd + "'");
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20ExportCliPython::exportSetupPy() {
    std::ofstream setupPy;
    std::string sFilename = m_sExportDir + "/setup.py";
    WsjcppLog::info(TAG, "Prepare setup.py " + sFilename);
    
    // https://packaging.python.org/tutorials/packaging-projects/
    std::string sContentSetupPy = 
        "import setuptools\n"
        "\n"
        "with open('README.md', 'r') as fh:\n"
        "    long_description = fh.read()\n"
        "\n"
        "setuptools.setup(\n"
        "    name='" + m_sPackageName + "',\n"
        "    version='" + m_sAppVersion + "',\n"
        "    packages=['" + m_sPackageName + "'],\n"
        "    install_requires=['websocket-client>=0.56.0', 'requests>=2.21.0'],\n"
        "    keywords=['" + WsjcppCore::join(m_vKeywords, "', '") + "'],\n"
        "    author='" + m_sAuthorName + "',\n"
        "    author_email='" + m_sAuthorEmail + "',\n"
        "    description='" + m_sClassName + " Python Library for " + m_sAppName + "',\n"
        "    long_description=long_description,\n"
        "    long_description_content_type='text/markdown',\n"
        "    url='" + m_sUrl + "',\n"
        "    license='MIT',\n"
        "    download_url='" + m_sDownloadUrl + "',\n"
        "    classifiers=[\n"
        "         'Development Status :: 5 - Production/Stable',\n" //  # Chose either "3 - Alpha", "4 - Beta" or "5 - Production/Stable" as the current state of your package
        "         'License :: OSI Approved :: MIT License',\n"
        "         'Operating System :: OS Independent',\n"
        "         'Programming Language :: Python :: 3',\n"
        "         'Programming Language :: Python :: 3.4',\n"
        "         'Programming Language :: Python :: 3.5',\n"
        "         'Programming Language :: Python :: 3.6',\n"
        "         'Programming Language :: Python :: 3.7',\n"
        "    ],\n"
        "    python_requires='>=3.6',\n"
        ")\n"
    ;

    WsjcppCore::writeFile(sFilename, sContentSetupPy);

    WsjcppLog::ok(TAG, "Done: setup.py");
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20ExportCliPython::exportAPImd() {
    
    std::ofstream apimd;
    std::string sFilename = m_sExportDir + "/API.md";
    WsjcppLog::info(TAG, "Prepare API.md " + sFilename);

    apimd.open(sFilename);

    long nSec = WsjcppCore::currentTime_seconds();

    apimd << "# " + m_sClassName + " Python Library \n\n";
    apimd << "Automatically generated by " << m_sAppName << ". \n";
    apimd << "* Version: " << m_sAppVersion << "\n";
    apimd << "* Date: " << WsjcppCore::formatTimeForWeb(nSec) << "\n\n";
    apimd << "Example connect/disconnect:\n"
        << "```\n"
        << "from " + m_sPackageName + " import " + m_sClassName + " \n\n"
        << "client = " + m_sClassName + "('ws://host:1234')\n"
        << " ... \n"
        << "client.close()\n"
        << "```\n";
    apimd << "\n";

    std::map<std::string, WsjcppJsonRpc20HandlerBase*>::iterator it = g_pWsjcppJsonRpc20HandlerList->begin();
    for (; it!=g_pWsjcppJsonRpc20HandlerList->end(); ++it) {
        std::string sMethod = it->first;
        WsjcppJsonRpc20HandlerBase* pWsjcppJsonRpc20HandlerBase = it->second;

        apimd
            << "<details>\n"
            << "<summary>" << sMethod << "</summary>\n\n"
            << "## " << sMethod << "\n\n";

        if (pWsjcppJsonRpc20HandlerBase->getDescription() != "") {
            apimd << pWsjcppJsonRpc20HandlerBase->getDescription() << "\n\n";
        }
        apimd 
            << "Access: unauthorized - **" << (pWsjcppJsonRpc20HandlerBase->haveUnauthorizedAccess() ? "yes" : "no") << "**, "
            << " user - **"   << (pWsjcppJsonRpc20HandlerBase->haveUserAccess() ? "yes" : "no") << "**, "
            << " tester - **" << (pWsjcppJsonRpc20HandlerBase->haveTesterAccess() ? "yes" : "no") << "**, "
            << " admin - **"  << (pWsjcppJsonRpc20HandlerBase->haveAdminAccess() ? "yes" : "no") << "**\n"
            << "\n";

        apimd << " #### Input params \n\n";

        std::string pythonTemplate = "";

        std::vector<WsjcppJsonRpc20ParamDef> vVin = pWsjcppJsonRpc20HandlerBase->inputs();
        for (int i = 0; i < vVin.size(); i++) {
            WsjcppJsonRpc20ParamDef inDef = vVin[i];
            std::string nameIn = std::string(inDef.getName());

            apimd << " * " << inDef.getName() << " - " << inDef.getType() << ", " << inDef.getRestrict() << "; " << inDef.getDescription() << "\n";

            pythonTemplate += "    " + inDef.getName() + "=";
            if (inDef.isInteger()) {
                pythonTemplate += "0";
            } else if (inDef.isString()) {
                pythonTemplate += "\"\"";
            } else if (inDef.isBool()) {
                pythonTemplate += "False";
            } else if (inDef.isJson()) {
                pythonTemplate += "{}";
            }

            if (i != vVin.size()-1) {
                pythonTemplate += ",\n";
            }
        }
        apimd 
            << "\n\n"
            << " #### example call method \n\n ```\nresponse = client." + sMethod + "(\n" + pythonTemplate + "\n)\n```"
            << "\n\n</details>"
            << "\n\n";
    }

    apimd.close();
    WsjcppLog::ok(TAG, "Done: " + sFilename);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppJsonRpc20ExportCliPython::exportInitPy() {
    std::string sFilename = m_sExportDir + "/" + m_sPackageName + "/__init__.py";
    WsjcppLog::info(TAG, "Prepare __init__.py " + sFilename);
    std::ofstream __init__;
    __init__.open (sFilename);
    __init__ << "from ." << m_sClassName << " import *\n";
    WsjcppLog::ok(TAG, "Done: " + sFilename);
    return true;
}

// ---------------------------------------------------------------------

void exportCliPythonAddCheckDataTypeOfParam(
    PyCodeBuilder &builder,
    WsjcppJsonRpc20ParamDef &paramDef,
    const std::string &sClassName,
    const std::string &sMethod
) {
    std::string sParamName = paramDef.getName();
    if (paramDef.isBool()) {
        builder
            .sub("if not isinstance(" + sParamName + ", bool): ")
                .add("raise Exception('Parameter \"" + sParamName + "\" expected datatype \"bool\" (lib: " + sClassName + "." + sMethod + " )')")
                .end();
    } else if (paramDef.isString()) {
        builder
            .sub("if not isinstance(" + sParamName + ", str): ")
                .add("raise Exception('Parameter \"" + sParamName + "\" expected datatype \"str\" (lib: " + sClassName + "." + sMethod + " )')")
                .end();
    } else if (paramDef.isInteger()) {
        builder
            .sub("if not isinstance(" + sParamName + ", int): ")
                .add("raise Exception('Parameter \"" + sParamName + "\" expected datatype \"int\" (lib: " + sClassName + "." + sMethod + " )')")
                .end();
    } else if (paramDef.isJson()) {
        builder
            .sub("if not isinstance(" + sParamName + ", dict): ")
                .add("raise Exception('Parameter \"" + sParamName + "\" expected \"dict\" (lib: " + sClassName + "." + sMethod + " )')")
                .end();
    } else {
        WsjcppLog::throw_err("exportCliPythonAddCheckDataTypeOfParam",
            "Not handled type for '" + sParamName + "' in method '" + sMethod + "'");
    }
};

bool WsjcppJsonRpc20ExportCliPython::exportClientPy() {
    std::string sFilename = m_sExportDir + "/" + m_sPackageName + "/" + m_sClassName + ".py";
    WsjcppLog::info(TAG, "Prepare " + m_sClassName + ".py: " + sFilename);

    std::ofstream clientpy;
    clientpy.open (sFilename);

    long nSec = WsjcppCore::currentTime_seconds();

    PyCodeBuilder builder;
    builder
    .add("#!/usr/bin/env python3")
    .add("# -*- coding: utf-8 -*-")
    .add("### This file was automatically generated by " + m_sAppName)
    .add("### Version: " + m_sAppVersion)
    .add("### Date: " + WsjcppCore::formatTimeForWeb(nSec))
    .add("")
    .add("import asyncio")
    .add("import websocket")
    .add("import json")
    .add("import select")
    .add("import time")
    .add("")
    .sub("class " + m_sClassName + ":")
        .add("__ws = None")
        .add("__url = None")
        .add("__cli_version = '" + m_sAppVersion + "'")
        .add("__loop = None")
        .add("__token = None")
        .add("__connecting = False")
        .add("__messageIdCounter = 0")
        .add("__incomingMesssages = []")
        .add("")
        .sub("def __init__(self, url):")
            .add("self.__url = url")
            .add("self.__loop = asyncio.get_event_loop()")
            .sub("try:")
                .add("self.__ws = websocket.create_connection(self.__url)")
                .add("self.__connecting = True")
                .end()
            .sub("except Exception as e:")
                .add("print('Failed connect to ' + self.__url)")
                .add("print('Exception: ' + str(e))")
                .add("self.__ws = None")
                .add("self.__connecting = False")
                .add("return")
                .end()
            .end()
        .add("")
        .sub("def __enter__(self):")
            .add("return self")
            .end()
        .add("")
        .sub("def __exit__(self, exc_type, exc_value, traceback):")
            .add("self.close()")
            .end()
        .add("")
        .sub("def hasConnection(self):")
            .add("return self.__ws != None")
            .end()
        .add("")
        .sub("def getToken(self):")
            .add("return self.__token")
            .end()
        .sub("def setToken(self, token):")
            .sub("if self.__token == None:")
                .add("self.__token = token")
                .end()
            .sub("else:")
                .add("print('ERROR: Token can be set only once')")
                .end()
            .end()
        .add("")
        .sub("def close(self):")
            .sub("if self.__ws != None:")
                .add("self.__ws.close()")
                .add("self.__ws = None")
                .end()
            // .add("self.__loop.close()")
            .end()
        .add("")
        .sub("def receiveIncomingMesssages(self):")
            .sub("if self.__ws == None:")
                .add("return None # TODO has not connection")
                .end()
            .sub("while True:")
                .sub("if self.__ws == None:")
                    .add("return None # TODO has not connection")
                    .end()
                .add("ready = select.select([self.__ws], [], [], 1)")
                .sub("if ready[0]:")
                    .add("responseText =  self.__ws.recv()")
                    .add("responseJson = json.loads(responseText)")
                    .add("# print('responseText: ' + responseText)")
                    .add("# incomeMessageId = responseJson['m']")
                    .add("self.__incomingMesssages.append(responseJson)")
                    .end()
                .sub("else:")
                    .add("return")
                    .end()
                .add("time.sleep(0.2)")
                .end()
            .end()
        .add("")
        .sub("def getIncomingMesssages(self):")
            .add("return self.__incomingMesssages")
            .end()
        .add("")
        .sub("def clearIncomingMesssages(self):")
            .add("self.__incomingMesssages = []")
            .end()
        .add("")
        .add("@asyncio.coroutine")
        .sub("async def __looper(self, messageId):")
            .add("max_time = 5*10 # 5 seconds")
            .add("counter_time = 0")
            .sub("while True:")
                .sub("if self.__ws == None:")
                    .add("return None # TODO has not connection")
                    .end()
                .sub("for inmsg in self.__incomingMesssages:")
                    .sub("if inmsg['id'] == messageId:")
                        .add("responseJson = inmsg")
                        .add("self.__incomingMesssages.remove(responseJson)")
                        .add("return responseJson")
                        .end()
                    .end()
                .add("counter_time = counter_time + 1")
                .add("ready = select.select([self.__ws], [], [], 0.1)")
                .sub("if ready[0]:")
                    .add("responseText =  self.__ws.recv()")
                    .add("responseJson = json.loads(responseText)")
                    .add("# print('responseText: ' + responseText)")
                    .sub("if 'id' in responseJson:")
                        .add("incomeMessageId = responseJson['id']")
                        .sub("if incomeMessageId == messageId:")
                            .add("return responseJson")
                            .end()
                        .sub("else:")
                            .add("self.__incomingMesssages.append(responseJson)")
                            .end()
                        .end()
                    .sub("else:")
                        .add("print('What is it? ' + responseText)")
                        .end()
                    .end()
                .sub("else:")
                    .add("print('wait...')")
                    .end()
                .sub("if counter_time > max_time:")
                    .add("return None")
                    .end()
                .add("await asyncio.sleep(0.2)")
                .end()
            .end()
        .add("")
        .sub("def generateBaseCommand(self, method):")
            .add("requestJson = {}")
            .add("self.__messageIdCounter = self.__messageIdCounter + 1")
            .add("msgId = 'id' + str(self.__messageIdCounter)")
            .add("requestJson['id'] = msgId")
            .add("requestJson['method'] = method")
            .add("requestJson['jsonrpc'] = '2.0'")
            .add("requestJson['params'] = {}")
            .add("return requestJson")
            .end()
        .add("")

        .sub("def __sendCommand(self, req):")
            .add("requestText = json.dumps(req)")
            .add("messageId = req['id']")
            .add("# print('requestText: ' + requestText)")
            .add("self.__ws.send(requestText) ")
            .add("result = self.__loop.run_until_complete(asyncio.gather(self.__looper(messageId)))")
            .add("result = self.preprocessIncomeJson(result[0])")
            .add("return result")
            .end()
        .add("");

    // prepare login / logoff
    builder
        .sub("def preprocessIncomeJson(self, jsonIn):")
            .sub("if jsonIn == None:")
                .add("return jsonIn")
                .end()
    ;
    for (int i = 0; i < m_vMethodsForClearAuthToken.size(); i++) {
        builder
            .sub("if jsonIn['method'] == '" + m_vMethodsForClearAuthToken[i] + "' and 'result' in jsonIn:")
                .add("self.__token = None")
                .end();
    }
    for (int i = 0; i < m_vMethodsForKeepAuthToken.size(); i++) {
        std::pair<std::string,std::string> p = m_vMethodsForKeepAuthToken[i];
        builder
            .sub("if jsonIn['method'] == '" + p.first + "' and 'result' in jsonIn:")
                .add("self.__token = jsonIn['result']['" + p.second + "']")
                .end();
    }
    builder
        .add("return jsonIn")
        .end()
    .add("")
    ;

    std::map<std::string, WsjcppJsonRpc20HandlerBase*>::iterator it = g_pWsjcppJsonRpc20HandlerList->begin();
    for (; it != g_pWsjcppJsonRpc20HandlerList->end(); ++it) {
        std::string sMethod = it->first;
        WsjcppJsonRpc20HandlerBase* pWsjcppJsonRpc20HandlerBase = it->second;
        std::vector<WsjcppJsonRpc20ParamDef> vParams = pWsjcppJsonRpc20HandlerBase->inputs();

        std::string sRequestParams = "";
        if (vParams.size() > 0) {
            for (int i = 0; i < vParams.size(); i++) {
                WsjcppJsonRpc20ParamDef inDef = vParams[i];
                if (inDef.isRequired()) {
                    sRequestParams += ", " + inDef.getName();
                }
            }
            for (int i = 0; i < vParams.size(); i++) {
                WsjcppJsonRpc20ParamDef inDef = vParams[i];
                if (inDef.isOptional()) {
                    sRequestParams += ", " + inDef.getName() + " = None";
                }
            }
        }

        builder
        .sub("def " + sMethod + "(self" + sRequestParams + "):")
            .sub("\"\"\"" + pWsjcppJsonRpc20HandlerBase->getDescription())
                .add("");
        
        if (pWsjcppJsonRpc20HandlerBase->getActivatedFromVersion() != "") {
            builder.add("Activated From Version: " + pWsjcppJsonRpc20HandlerBase->getActivatedFromVersion());
        }
        
        if (pWsjcppJsonRpc20HandlerBase->getDeprecatedFromVersion() != "") {
            builder.add("Deprecated From Version: " + pWsjcppJsonRpc20HandlerBase->getDeprecatedFromVersion());
        }

        builder
            .add(pWsjcppJsonRpc20HandlerBase->haveUnauthorizedAccess() ? "Allowed access for unauthorized users" : "Denied access for unauthorized users")
            .add(pWsjcppJsonRpc20HandlerBase->haveUserAccess() ? "Allowed access for users" : "Denied access for users")
            .add(pWsjcppJsonRpc20HandlerBase->haveTesterAccess() ? "Allowed access for tester" : "Denied access for tester")
            .add(pWsjcppJsonRpc20HandlerBase->haveAdminAccess() ? "Allowed access for admins" : "Denied access for admins")
            .add("");

        if (vParams.size() > 0) {
            builder
                .sub("Args:");

            for (int i = 0; i < vParams.size(); i++) {
                WsjcppJsonRpc20ParamDef inDef = vParams[i];
                std::string nameIn = std::string(inDef.getName());
                builder.add(nameIn + " (" + inDef.getType() + "): " + inDef.getRestrict() + ", " + inDef.getDescription());
            }
            builder.end();
        }

        /* 
        Returns:
            bool: The return value. True for success, False otherwise.
        */

        builder
                .end()
            .add("\"\"\"")
            .add("if not self.hasConnection(): return None")
            .add("reqJson = self.generateBaseCommand('" + sMethod + "')");
        ;

        // check required
        for (int i = 0; i < vParams.size(); i++) {
            WsjcppJsonRpc20ParamDef paramDef = vParams[i];
            std::string sParamName = paramDef.getName();
            if (paramDef.isRequired()) {
                builder
                .sub("if " + sParamName + " == None: ")
                    .add("raise Exception('Parameter \"" + sParamName + "\" expected (lib: " + m_sClassName + "." + sMethod + ")')")
                    .end();
                exportCliPythonAddCheckDataTypeOfParam(builder, paramDef, m_sClassName, sMethod);
                builder.add("reqJson['params']['" + sParamName + "'] = " + sParamName);
            } else if (paramDef.isOptional()) {
                builder
                    .sub("if " + sParamName + " != None: ");
                exportCliPythonAddCheckDataTypeOfParam(builder, paramDef, m_sClassName, sMethod);
                    builder
                        .add("reqJson['params']['" + sParamName + "'] = " + sParamName)
                        .end();
            } else {
                WsjcppLog::throw_err(TAG, "Prameter must be required or optional");
            }
        }

        builder
            .add("return self.__sendCommand(reqJson)")
            .end()
        .add("");
    }
    builder.end();
    builder.print(clientpy);
    clientpy.close();
    WsjcppLog::ok(TAG, "Done: " + sFilename);
    return true;
}

// ---------------------------------------------------------------------

