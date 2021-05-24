#
# MIT License
# Copyright (c) 2021 Nicola Pancheri
# pancheri.nicola@gmail.com
#

QMAKE=/usr/bin/qmake-qt5
BUILD_DIR=$(PWD)/tmp
INCLUDE_DIR=/usr/include/MVCqt
LIB_DIR=/usr/lib/MVCqt
ROOT=$(PWD)/../Lib/Root
DEST_INC=$(ROOT)$(INCLUDE_DIR)
DEST_LIB=$(ROOT)$(LIB_DIR)
ACTOR=MVCqtActor
MODEL=MVCqtModel
VIEW=MVCqtView
ACTORS=$(MODEL) $(VIEW)
CONTROLLER=MVCqtController
FRAMEWORK=MVCqt

.PHONY: all install uninstall clean cp_actors_hdrs

all: $(FRAMEWORK)

$(FRAMEWORK): $(ROOT) make_lib clean_build_dir

make_lib: $(INCLUDE_DIR) $(BUILD_DIR) $(ACTOR) $(ACTORS) $(CONTROLLER)
	cd  $(BUILD_DIR); $(QMAKE) -makefile -unix -o Makefile "CONFIG+=$(FRAMEWORK)" ../$(FRAMEWORK)/$(FRAMEWORK).pro; \
    make -j4 -f Makefile
	cp $(FRAMEWORK)/include/* $(ROOT)$(INCLUDE_DIR)

actor: $(ROOT) $(BUILD_DIR) $(ACTOR)
	mkdir -p $(DEST_LIB)/$(ACTOR)
	mkdir -p $(DEST_INC)/$(ACTOR)
	cd  $(BUILD_DIR); $(QMAKE) -makefile -unix -o Makefile "CONFIG+=$(ACTOR)" ../$(ACTOR)/$(ACTOR).pro; \
	make -f Makefile
	cp $(ACTOR)/include/* $(DEST_INC)/$(ACTOR)
	make clean

model: $(ROOT) $(BUILD_DIR) $(ACTOR) $(MODEL)
	sudo rm -rf $(INCLUDE_DIR)
	make $(INCLUDE_DIR)
	mkdir -p $(DEST_LIB)/$(MODEL)
	cd  $(BUILD_DIR); $(QMAKE) -makefile -unix -o Makefile "CONFIG+=$(MODEL)" ../$(MODEL)/$(MODEL).pro; \
	make -f Makefile
	make clean_build_dir

view: $(ROOT) $(BUILD_DIR) $(ACTOR) $(VIEW)
	sudo rm -rf $(INCLUDE_DIR)
	make $(INCLUDE_DIR)
	mkdir -p $(DEST_LIB)/$(VIEW)
	cd  $(BUILD_DIR); $(QMAKE) -makefile -unix -o Makefile "CONFIG+=$(VIEW)" ../$(VIEW)/$(VIEW).pro; \
	make -f Makefile
	make clean_build_dir

controller: $(ROOT) $(BUILD_DIR) $(ACTOR) $(VIEW) $(MODEL) $(CONTROLLER)
	sudo rm -rf $(INCLUDE_DIR)
	make $(INCLUDE_DIR)
	mkdir -p $(DEST_LIB)/$(CONTROLLER)
	cd  $(BUILD_DIR); $(QMAKE) -makefile -unix -o Makefile "CONFIG+=$(CONTROLLER)" ../$(CONTROLLER)/$(CONTROLLER).pro; \
	make -f Makefile
	make clean_build_dir

$(ROOT):
	rm -rf $(ROOT)
	mkdir -p $(DEST_LIB)
	mkdir -p $(DEST_INC)

$(INCLUDE_DIR):
	sudo mkdir -p $(INCLUDE_DIR)
	sudo mkdir -p $(INCLUDE_DIR)/{MVCqtActor,MVCqtModel,MVCqtView,MVCqtController}
	sudo make cp_actors_hdrs

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

cp_actors_hdrs: $(INCLUDE_DIR) $(ACTOR) $(ACTORS) $(CONTROLLER)
	for act in $(ACTOR) $(ACTORS) $(CONTROLLER); \
		do sudo cp $$act/include/*  $(INCLUDE_DIR)/$$act; done

clean_build_dir:
	sudo rm -rf $(BUILD_DIR)
	sudo rm -rf $(DEST_INC)/*/
	sudo mv $(INCLUDE_DIR)/* $(DEST_INC)
	sudo rm -rf $(INCLUDE_DIR)

clean:
	rm -rf $(BUILD_DIR)

install:
	sudo cp -rv $(ROOT)/* /

rem_root:
	sudo rm -rf $(ROOT)

uninstall:
	sudo rm -rf $(INCLUDE_DIR)
	sudo rm -rf $(LIB_DIR)
	sudo rm -rf $(ROOT)
