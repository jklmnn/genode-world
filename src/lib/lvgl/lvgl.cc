
#include <os/pixel_rgb565.h>

#include <lvgl.h>
#include <lv_core/lv_obj.h>
#include <lv_core/lv_vdb.h>

static void *_framebuffer = nullptr;

Lvgl::Lvgl(Genode::Env &env) :
    _disp_drv(),
    _fb(env, Framebuffer::Mode {LV_HOR_RES, LV_VER_RES, Framebuffer::Mode::RGB565}),
    _fb_ds(env.rm(), _fb.dataspace())
{
    _framebuffer = _fb_ds.local_addr<void>();
    lv_init();
    lv_disp_drv_init(&_disp_drv);
    _disp_drv.disp_fill = Lvgl::disp_fill;
    _disp_drv.disp_map = Lvgl::disp_map;
}

void Lvgl::disp_fill(Genode::int32_t x1, Genode::int32_t y1, Genode::int32_t x2, Genode::int32_t y2, lv_color_t color)
{
    using namespace Genode;

    uint32_t const c_x = x1 < 0 ? 0U : x1;
    uint32_t const c_y = y1 < 0 ? 0U : y1;
    uint32_t const c_w = x2 < 0 ? 0U : x2;
    uint32_t const c_h = y2 < 0 ? 0U : y2;

    uint32_t const u_x = min(LV_HOR_RES, max(c_x, 0U));
    uint32_t const u_y = min(LV_VER_RES, max(c_y, 0U));
    uint32_t const u_w = min(LV_HOR_RES, max(c_w, 0U) + u_x);
    uint32_t const u_h = min(LV_VER_RES, max(c_h, 0U) + u_y);

    if(_framebuffer){
        Pixel_rgb565 * const fb = static_cast<Pixel_rgb565 * const>(_framebuffer);

        for (uint32_t r = u_y; r < u_h; ++r) {
            for (uint32_t c = u_x; c < u_w; ++c) {
                uint32_t const d = c + r * LV_HOR_RES;
                fb[d].rgba(color.red, color.green, color.blue, 0);
            }
        }
        lv_flush_ready();
    }else{
        throw Lvgl_Framebuffer_Uninitialized();
    }
}
void Lvgl::disp_map(Genode::int32_t x1, Genode::int32_t y1, Genode::int32_t x2, Genode::int32_t y2, const lv_color_t *color)
{
    using namespace Genode;

    uint32_t const c_x = x1 < 0 ? 0U : x1;
    uint32_t const c_y = y1 < 0 ? 0U : y1;
    uint32_t const c_w = x2 < 0 ? 0U : x2;
    uint32_t const c_h = y2 < 0 ? 0U : y2;

    uint32_t const u_x = min(LV_HOR_RES, max(c_x, 0U));
    uint32_t const u_y = min(LV_VER_RES, max(c_y, 0U));
    uint32_t const u_w = min(LV_HOR_RES, max(c_w, 0U) + u_x);
    uint32_t const u_h = min(LV_VER_RES, max(c_h, 0U) + u_y);

    if(_framebuffer){
        Pixel_rgb565 * const fb = static_cast<Pixel_rgb565 * const>(_framebuffer);

        for (uint32_t r = u_y; r < u_h; ++r) {
            for (uint32_t c = u_x; c < u_w; ++c) {
                uint32_t const d = c + r * LV_HOR_RES;
                fb[d].rgba(color[d].red, color[d].green, color[d].blue, 0);
            }
        }
        lv_flush_ready();
    }else{
        throw Lvgl_Framebuffer_Uninitialized();
    }
}
