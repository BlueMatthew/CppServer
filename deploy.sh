#!/bin/bash

# Define installation prefix
PREFIX="/usr/local"

cp -f temp/libcppserver.a $PREFIX/lib/
cp -rf include/server $PREFIX/include/

cp -f temp/modules/libasio.a $PREFIX/lib/
cp -f modules/asio/asio/include/asio.hpp $PREFIX/include/
cp -rf modules/asio/asio/include/asio $PREFIX/include/

cp -f temp/modules/CppCommon/libcppcommon.a $PREFIX/lib/

if [ -d "$PREFIX/include/cppcommon/" ]; then
    rm -rf $PREFIX/include/cppcommon/
fi
mkdir -p $PREFIX/include/cppcommon/
cp -rf modules/CppCommon/include/* $PREFIX/include/cppcommon/

cp -f temp/modules/CppCommon/modules/libfmt.a $PREFIX/lib/
cp -rf modules/CppCommon/modules/fmt/include/fmt $PREFIX/include/

