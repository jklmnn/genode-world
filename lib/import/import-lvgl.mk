
LVGL_DIR := $(call select_from_ports,lvgl)/lvgl/
INC_DIR += $(call select_from_repositories,src/lib/lvgl/include) \
	   $(LVGL_DIR)

CC_OPT += -DLV_CONF_INCLUDE_SIMPLE

SRC_CC += lvgl.cc

SHARED_LIB = no

vpath lvgl.cc $(REP_DIR)/src/lib/lvgl
