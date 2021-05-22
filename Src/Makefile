QMAKE=/usr/bin/qmake-qt5
BUILD_DIR=$(PWD)/tmp
INCLUDE_DIR=/usr/include/MVCqt
LIB_DIR=/usr/lib/MVCqt
ROOT=$(PWD)/../Lib/Root
DEST_INC=$(ROOT)$(INCLUDE_DIR)
DEST_LIB=$(ROOT)$(LIB_DIR)
ACTOR=MVCqtActor
ACTORS=MVCqtModel MVCqtView
CONTROLLER=MVCqtController
FRAMEWORK=MVCqt

.PHONY: all install uninstall clean cp_actors_hdrs

all: $(FRAMEWORK)

$(FRAMEWORK): $(ROOT) make_lib clean_build_dir

make_lib: $(INCLUDE_DIR) $(BUILD_DIR) $(ACTOR) $(ACTORS) $(CONTROLLER)
	cd  $(BUILD_DIR); $(QMAKE) -makefile -unix -o Makefile "CONFIG+=$(FRAMEWORK)" ../$(FRAMEWORK)/$(FRAMEWORK).pro; \
    make -f Makefile
	cp $(FRAMEWORK)/include/* $(ROOT)$(INCLUDE_DIR)

actor: MVCqtActor
	cd  $(BUILD_DIR); $(QMAKE) -makefile -unix -o Makefile "CONFIG+=$<" ../$</$<.pro; \
	make -f Makefile

actors: $(INCLUDE_DIR) $(BUILD_DIR) $(ACTOR) $(ACTORS) $(CONTROLLER)
	for act in $(ACTORS); \
	 do echo "Building $$act..."; echo $(PWD); \
	 cd  $(BUILD_DIR); $(QMAKE) -makefile -unix -o Makefile "CONFIG+=$$act" ../$$act/$$act.pro; \
 	 make -f Makefile; \
	done

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
		do cp $$act/include/*  $(INCLUDE_DIR)/$$act; done

clean_build_dir:
	rm -rf $(BUILD_DIR)
	sudo mv $(INCLUDE_DIR)/* $(DEST_INC)
	sudo rm -rf $(INCLUDE_DIR)

clean:
	rm -rf $(BUILD_DIR)

install:
	sudo cp -r $(ROOT)/* /

uninstall:
	sudo rm -rf $(INCLUDE_DIR)
	sudo rm -rf $(LIB_DIR)
	sudo rm -r $(ROOT)
