#!/usr/bin/env bash

set -x
# set -e

run_test() {
    echo "$1/$2"
    cd "$1" || return
    sh "$2"
    ./a.out
    cd - || return
}

run_test Credit/unittests compile_unittest.bat
run_test Financial/unittests compile_unittest_clearinghouse.bat
run_test Financial/unittests compile_unittest_firm.bat
run_test Financial/unittests compile_unittest_household.bat
run_test Financial_Management/unittests compile_unittest.bat
run_test Financial_Management/unittests compile_unittest_ref.bat
#run_test Government/unittests compile_unittest.bat
#run_test Government/unittests compile_unittest_global.bat

run_test Labour/unittests compile_unittest.bat
run_test Statistical_Office/unittests compile_unittest.bat
run_test Statistical_Office/unittests compile_unittest_eurostat.bat
run_test Statistical_Office/unittests compile_unittest_household.bat
run_test my_library_unittests/unittests compile_unittest_library.bat
