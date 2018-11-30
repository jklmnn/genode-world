
LVGL_DIR := $(call select_from_ports,lvgl)/lvgl/
INC_DIR += $(call select_from_repositories,src/lib/lvgl/include) \
	   $(LVGL_DIR)

CC_OPT += -DLV_CONF_INCLUDE_SIMPLE

SRC_CC += lvgl.cc \
	  string.cc

SRC_C += lv_obj.c \
	 lv_ll.c \
	 lv_mem.c \
	 lv_task.c \
	 lv_font.c \
	 lv_style.c \
	 lv_refr.c \
	 lv_area.c \
	 lv_theme.c \
	 lv_vdb.c \
	 lv_circ.c \
	 lv_draw.c \
	 lv_draw_rect.c \
	 lv_draw_vbasic.c \
	 lv_hal_tick.c \
	 lv_hal_disp.c \
	 lv_font_dejavu_20.c

SHARED_LIB = no

vpath lvgl.cc $(REP_DIR)/src/lib/lvgl
vpath string.cc $(REP_DIR)/src/lib/lvgl
vpath %.c $(LVGL_DIR)/lv_core $(LVGL_DIR)/lv_misc $(LVGL_DIR)/lv_draw $(LVGL_DIR)/lv_themes $(LVGL_DIR)/lv_hal $(LVGL_DIR)/lv_fonts
