
#include <base/attached_dataspace.h>
#include <framebuffer_session/connection.h>
#include <lv_conf.h>

#include <lv_hal/lv_hal_disp.h>
#include <lv_core/lv_obj.h>
#include <lv_objx/lv_label.h>

void lvgl_init(Genode::Env &, Genode::Dataspace_capability, lv_disp_drv_t &);

class Lvgl_Framebuffer_Uninitialized : public Genode::Exception {};

class Lvgl
{
    private:
        lv_disp_drv_t _disp_drv;
        Framebuffer::Connection _fb;
        Genode::Attached_dataspace _fb_ds;

    public:
        Lvgl(Genode::Env &);
        static void disp_fill(Genode::int32_t, Genode::int32_t, Genode::int32_t, Genode::int32_t, lv_color_t);
        static void disp_map(Genode::int32_t, Genode::int32_t, Genode::int32_t, Genode::int32_t, const lv_color_t *);
};
