
#include <framebuffer_session/framebuffer_session.h>

#ifndef LV_VDB_SIZE
#error Unbuffered mode not supported
#endif

#include <lv_hal/lv_hal_disp.h>

void lvgl_init(Genode::Dataspace_capability ds, lv_disp_drv_t &drv);
