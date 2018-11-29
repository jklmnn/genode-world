
LVGL_DIR = $(call select_from_ports,lvgl)/lvgl/
INC_DIR += $(GENODE_DIR)/repos/world/src/lib/lvgl/include \
	   $(LVGL_DIR) \
	   $(PRG_DIR)
