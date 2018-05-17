#!/bin/sh

find ../Classes/ -name "*.h" -or -name "*.hpp" -or -name "*.c" -or -name "*.cpp" | xargs clang-format -i
