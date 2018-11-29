
#include <lvgl.h>



void lvgl_init(Genode::Dataspace_capability ds, lv_disp_drv_t &drv)
{
    lv_init();
    lv_disp_drv_init(&drv);
}
