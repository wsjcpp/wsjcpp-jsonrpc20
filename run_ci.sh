#!/bin/bash

check_ret() {
    if [ $1 -ne 0 ]; then
        echo ""
        echo "!!! FAIL: $3"
        echo "********************************************************************************"
        echo ""
        exit $1
    else
        echo ""
        echo "*** SUCCESS: $2"
        echo "********************************************************************************"
        echo ""
    fi
}

./build_simple.sh
check_ret $? "build wsjcpp-jsonrpc20"

./wsjcpp-jsonrpc20
check_ret $? "run wsjcpp-jsonrpc20"

cd unit-tests.wsjcpp
check_ret $? "change directory to unit-tests.wsjcpp"

./build_simple.sh
check_ret $? "build unit-tests"

./unit-tests
check_ret $? "run unit-tests"

cd ../tests-client-py3
check_ret $? "change directory to ../tests-client-py3"

python3 run_tests.py
check_ret $? "run python tests"
