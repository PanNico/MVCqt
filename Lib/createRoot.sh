#!/bin/bash

mkdir -p Root/usr/lib/MVCqt/{MVCqtModel,MVCqtView,MVCqtController}
mkdir -p Root/usr/include/MVCqt/{MVCqtModel,MVCqtView,MVCqtController}

HEADER="Root/usr/include/MVCqt/mvcqt.h"

echo "#ifndef MVCqt_INCLUDE" > $HEADER
echo "#define MVCqt_INCLUDE" >> $HEADER
echo >> $HEADER
echo "#include \"MVCqtModel/mvcqtModel.h\"" >> $HEADER
echo >> $HEADER
echo "#endif" >> $HEADER
