SUBDIRS += CreationPattern01_AbstractFactory/cpp_src
SUBDIRS += CreationPattern01_AbstractFactory/rust_src
SUBDIRS += CreationPattern01_AbstractFactory_Practical/cpp_src
SUBDIRS += CreationPattern03_FactoryMethod/cpp_src
SUBDIRS += CreationPattern03_FactoryMethod/cpp_src2
SUBDIRS += CreationPattern03_FactoryMethod/rust_src
SUBDIRS += StructurePattern01_Adapter\cpp_src
SUBDIRS += StructurePattern01_Adapter\cpp_src2

SUBDIRS_TARGET_ALL := $(addsuffix .dir_all,$(SUBDIRS))
SUBDIRS_TARGET_RUN := $(addsuffix .dir_run,$(SUBDIRS))
SUBDIRS_TARGET_CLN := $(addsuffix .dir_clean,$(SUBDIRS))

all: $(SUBDIRS_TARGET_ALL)

run: $(SUBDIRS_TARGET_RUN)

clean: $(SUBDIRS_TARGET_CLN)

%.dir_all:
	make -C $* all

%.dir_run:
	make -C $* run

%.dir_clean:
	make -C $* clean

