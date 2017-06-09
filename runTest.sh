#!/bin/bash -
#===============================================================================
#
#          FILE: runTest.sh
#
#         USAGE: ./runTest.sh
#
#   DESCRIPTION:
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: YOUR NAME (),
#  ORGANIZATION:
#       CREATED: 06/08/2017 10:09:49 PM
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error

testName=$1
testScript=$2
testFile=$3

./nsh tests/${testScript} >> out.txt

cmp --silent out.txt tests/${testFile} && echo "### SUCCESS: $testName tests pass!" || echo "### FAILURE: $testName tests failed!"; diff out.txt tests/${testFile}

rm out.txt

