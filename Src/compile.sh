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

	#mkdir -p $DEST_LIB/{MVCqtActor,MVCqtModel,MVCqtView,MVCqtController}
	mkdir -p $DEST_LIB
	mkdir -p $DEST_INC/{MVCqtActor,MVCqtModel,MVCqtView,MVCqtController}
	
#	local HEADER=$DEST_INC"/mvcqt.h"

#	echo "#ifndef MVCqt_INCLUDE" > $HEADER
#	echo "#define MVCqt_INCLUDE" >> $HEADER
#	echo >> $HEADER
#	echo "#include \"MVCqtActor/mvcqtActor.h\"" >> $HEADER
#	echo "#include \"MVCqtModel/mvcqtModel.h\"" >> $HEADER
#	echo "#include \"MVCqtView/mvcqtView.h\"" >> $HEADER
#	echo "#include \"MVCqtController/mvcqtController.h\"" >> $HEADER
#	echo >> $HEADER
#	echo "#endif" >> $HEADER

}

compile_module()
{
	local MODULE_NAME=$1
	$QMAKE -makefile -unix -o Makefile "CONFIG+=$MODULE_NAME" ../$MODULE_NAME/$MODULE_NAME.pro
	make

	rm -rf *

	#coping headers
	if [ "$MODULE_NAME" == "MVCqt" ]
	then
		for dir in ../MVC*/
		do
			local dir=${dir:3:-1}
			if [ "$dir" == "MVCqt" ]
			then
				cp -v ../$dir/include/* ../$DEST_INC/
			else
				cp -v ../$dir/include/* ../$DEST_INC/$dir
			fi
		done
	else
		cp -v ../$MODULE_NAME/include/* ../$DEST_INC/$MODULE_NAME
	fi

}

create_root

#creating building dir
mkdir tmp
cd tmp

#compiling 
#TO DO WINZOZ
#compile_module "MVCqtActor"
#compile_module "MVCqtModel"
#compile_module "MVCqtView"
#compile_module "MVCqtController"
compile_module "MVCqt"

#cleaning building dir
cd ..
rm -rf tmp

