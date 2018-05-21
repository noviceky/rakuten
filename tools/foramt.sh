#!/bin/sh

find `dirname $0`/../Classes/ -name "*.h" -or -name "*.hpp" -or -name "*.c" -or -name "*.cpp" | xargs clang-format -i
