
#include <base/attached_dataspace.h>
#include <util/reconstructible.h>

#include <lvgl.h>
#include <lv_core/lv_obj.h>
#include <lv_core/lv_vdb.h>

static Genode::Constructible<Genode::Attached_dataspace> _fb_ds;

void lvgl_init(Genode::Env &env, Genode::Dataspace_capability ds, lv_disp_drv_t &drv)
{
    _fb_ds.construct(env.rm(), ds);
    if(_fb_ds.constructed()){
        lv_vdb_set_adr(_fb_ds->local_addr<void>(), nullptr);
        lv_init();
        lv_disp_drv_init(&drv);
    }else{
        throw Genode::Exception();
    }
}
