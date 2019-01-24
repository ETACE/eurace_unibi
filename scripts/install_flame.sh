#!/usr/bin/env bash

set -x
set -e

LIBMBOARD_VER=5fd34e83b932dcda5bb6c177277b8557fbe01229
XPARSER_VER=0.17.1

# install libmboard
wget https://github.com/FLAME-HPC/libmboard/archive/$LIBMBOARD_VER.tar.gz
tar xf $LIBMBOARD_VER.tar.gz
mkdir libmboard
cd libmboard-$LIBMBOARD_VER
chmod +x autogen.sh  # TODO remove this once the version is updated
./autogen.sh
./configure --prefix="$(cd ../libmboard; pwd)" --disable-parallel
make
make install

cd ..
wget https://github.com/FLAME-HPC/xparser/archive/$XPARSER_VER.tar.gz
tar xf $XPARSER_VER.tar.gz
mv xparser-$XPARSER_VER xparser
cd xparser
make
