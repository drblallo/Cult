#!/bin/bash
cd cmake-build-coverage/
rm test.info
rm filtered.info
rm base.info
rm total.info
lcov --capture --initial --directory . --output-file ./base.info
./test/runTest
lcov --capture --directory . --output-file ./test.info
lcov --add-tracefile ./base.info --add-tracefile ./test.info --output-file ./total.info
lcov --remove ./total.info 'usr/*' 'gtest/*' 'test/*' 'g3log/*' 'glm/*' --output-file ./filtered.info
genhtml ./filtered.info --output-directory ./Coverage
vivaldi ./Coverage/index.html
