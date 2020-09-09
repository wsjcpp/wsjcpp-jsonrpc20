#ifndef WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H
#define WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H

class WsjcppJsonRpc20ExportCliPython {
    public:
        void exportLib();
    private:
        void exportSetupPy();
        void exportAPImd();
        void export__init__py();
        void exportPrepareDirs();
};

#endif // WSJCPP_JSONRPC20_EXPORT_CLI_PYTHON_H
