QT5_PORT_DIR := $(call select_from_ports,qt5)
QT5_CONTRIB_DIR := $(QT5_PORT_DIR)/src/lib/qt5/qt5

QUATERION_DIR := $(call select_from_ports,quaternion)/qmatrixclient/quaternion
QMATRIX_DIR := $(call select_from_ports,quaternion)/qmatrixclient/libqmatrixclient

QMAKE_PROJECT_PATH = $(QUATERION_DIR)/client
QMAKE_PROJECT_FILE = $(QUATERION_DIR)/quaternion.pro

INC_DIR += $(QMATRIX_DIR)/lib \
	   $(QMATRIX_DIR)/lib/events \
	   $(QMATRIX_DIR)/lib/jobs

vpath % \
    $(QMAKE_PROJECT_PATH) \
    $(QMAKE_PROJECT_PATH)/models \
    $(QMATRIX_DIR)/lib \
    $(QMATRIX_DIR)/lib/events \
    $(QMATRIX_DIR)/lib/jobs

include $(call select_from_repositories,src/app/qt5/tmpl/target_defaults.inc)
include $(call select_from_repositories,src/app/qt5/tmpl/target_final.inc)

LIBS += qt5_component qt5_network stdcxx libc

CC_CXX_OPT_STD = -std=gnu++14
CC_CXX_WARN_STRICT =
