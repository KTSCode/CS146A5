#!/bin/bash
./runTest.sh "echo cd pwd" "test1.nsh" "outtest1.txt"
./runTest.sh "ls" "test2.nsh" "outtest2.txt"
./runTest.sh "cat" "test3.nsh" "outtest3.txt"

