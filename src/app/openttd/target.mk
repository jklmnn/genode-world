TARGET := openttd

OPENTTD_DIR := $(call select_from_ports,openttd)/openttd
OPENTTD_SRC := $(OPENTTD_DIR)/src
OPENTTD_OBJ := $(OPENTTD_DIR)/objs

SRC_CC := $(wildcard $(OPENTTD_SRC)/*.cpp)

INC_DIR += $(OPENTTD_SRC)/core
INC_DIR += $(OPENTTD_SRC)/table

INC_DIR += $(OPENTTD_OBJ)/release

vpath %.cpp $(OPENTTD_SRC)

LIBS += posix sdl sdl_net icu stdcxx

CC_OPT += -std=c99 -DTARGET_UNIX

CC_WARN += -Wno-implicit-function-declaration

CONFIGURE_ARGS = --without-liblzo2
