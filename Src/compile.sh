#!/bin/bash
# References: https://doc.qt.io/archives/qt-4.8/qmake-running.html
#

QMAKE=qmake-qt5
ROOT="../Lib/Root"
DEST_INC=$ROOT"/usr/include/MVCqt"
DEST_LIB=$ROOT"/usr/lib/MVCqt"


create_root()
{
	if [ -d $ROOT ] 
	then
	       rm -rf $ROOT
        fi

	mkdir -p $DEST_LIB/{MVCqtModel,MVCqtView,MVCqtController}
	mkdir -p $DEST_INC/{MVCqtModel,MVCqtView,MVCqtController}
	
	local HEADER=$DEST_INC"/mvcqt.h"

	echo "#ifndef MVCqt_INCLUDE" > $HEADER
	echo "#define MVCqt_INCLUDE" >> $HEADER
	echo >> $HEADER
	echo "#include \"MVCqtModel/mvcqtModel.h\"" >> $HEADER
#	echo "#include \"MVCqtView/mvcqtView.h\"" >> $HEADER
#	echo "#include \"MVCqtController/mvcqtController.h\"" >> $HEADER
	echo >> $HEADER
	echo "#endif" >> $HEADER

}

create_root

#creating building dir
mkdir tmp
cd tmp

#compiling 
#TO DO WINZOZ
$QMAKE -makefile -unix -o Makefile "CONFIG+=MVCqtModel" ../MVCqtModel/MVCqtModel.pro
make

#cleaning building dir
cd ..
rm -rf tmp

#coping headers
cp MVCqtModel/include/* $DEST_INC/MVCqtModel
