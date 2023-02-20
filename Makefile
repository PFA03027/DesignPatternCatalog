SUBDIRS += CreationPattern01_AbstractFactory/cpp_src
SUBDIRS += CreationPattern01_AbstractFactory/rust_src
SUBDIRS += CreationPattern01_AbstractFactory_Practical/cpp_src
SUBDIRS += CreationPattern02_Builder/cpp_src
SUBDIRS += CreationPattern03_FactoryMethod/cpp_src
SUBDIRS += CreationPattern03_FactoryMethod/cpp_src2
SUBDIRS += CreationPattern03_FactoryMethod/rust_src
SUBDIRS += CreationPattern04_Prototype/cpp_src
SUBDIRS += CreationPattern05_Singleton/cpp_src
SUBDIRS += CreationPattern05_Singleton/cpp_src2
SUBDIRS += CreationPattern05_Singleton/cpp_src3
SUBDIRS += CreationPattern05_Singleton/cpp_src4
SUBDIRS += CreationPattern05_Singleton/cpp_srcX
SUBDIRS += CreationPattern05_Singleton/rust_src
SUBDIRS += CreationPattern05_Singleton/rust_src2
SUBDIRS += StructurePattern01_Adapter/cpp_src
SUBDIRS += StructurePattern01_Adapter/cpp_src2
SUBDIRS += StructurePattern02_Bridge/cpp_src
SUBDIRS += StructurePattern03_Composite/cpp_src
SUBDIRS += StructurePattern03_Composite/cpp_src2
SUBDIRS += StructurePattern03_Composite/cpp_src3
SUBDIRS += StructurePattern03_Composite/rust_src
SUBDIRS += StructurePattern03_Composite/rust_src2
SUBDIRS += StructurePattern04_Decorator/cpp_src
SUBDIRS += StructurePattern04_Decorator/rust_src
SUBDIRS += StructurePattern05_Facade/cpp_src
SUBDIRS += BehaviorPattern01_ChainOfResponsibility/cpp_src
SUBDIRS += BehaviorPattern01_ChainOfResponsibility/cpp_src2
SUBDIRS += BehaviorPattern01_ChainOfResponsibility/cpp_src3
SUBDIRS += BehaviorPattern01_ChainOfResponsibility/rust_src
SUBDIRS += BehaviorPattern07_Observer/cpp_src
SUBDIRS += BehaviorPattern07_Observer/rust_src
SUBDIRS += BehaviorPattern07_Observer/rust_src2
SUBDIRS += BehaviorPattern07_Observer/rust_src3
SUBDIRS += BehaviorPattern08_State/cpp_src
SUBDIRS += BehaviorPattern09_Strategy/cpp_src
SUBDIRS += BehaviorPattern09_Strategy/cpp_src2
SUBDIRS += BehaviorPattern09_Strategy/cpp_src3
SUBDIRS += BehaviorPattern09_Strategy/rust_src
SUBDIRS += BehaviorPattern10_TemplateMethod/cpp_src
SUBDIRS += BehaviorPattern10_TemplateMethod/rust_src

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

