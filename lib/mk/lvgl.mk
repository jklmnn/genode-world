
include $(REP_DIR)/lib/import/import-lvgl.mk

CC_OPT += -DLV_CONF_INCLUDE_SIMPLE

SRC_CC += lvgl.cc

vpath lvgl.cc $(REP_DIR)/src/lib/lvgl
