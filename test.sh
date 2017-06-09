#!/bin/bash

./nsh tests/test.nsh >> out.txt
cmp --silent out.txt tests/outtest.txt && echo '### SUCCESS: tests pass!' || echo '### FAILURE: tests fail!'

rm out.txt

