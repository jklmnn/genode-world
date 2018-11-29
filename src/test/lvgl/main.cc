
#include <base/component.h>
#include <framebuffer_session/connection.h>

#include <lv_conf.h>
#include <lvgl.h>

struct Main
{
    Genode::Env &_env;
    Framebuffer::Mode _mode { LV_HOR_RES, LV_VER_RES, Framebuffer::Mode::RGB565 };
    Framebuffer::Connection _framebuffer { _env, _mode };
    lv_disp_drv_t drv {};

    Main(Genode::Env &env) : _env(env)
    {
        lvgl_init(_framebuffer.dataspace(), drv);
    }
};

void Component::construct(Genode::Env &env)
{
    static Main inst(env);
}
