
#ifndef _LV_CONF_DEFAULT_H_
#define _LV_CONF_DEFAULT_H_

#define LV_VDB_SIZE (LV_HOR_RES * LV_VER_RES * LV_COLOR_DEPTH / 8)

#ifndef LV_DPI
#define LV_DPI 100
#endif

#define LV_VDB_ADR LV_VDB_ADR_INV
#define LV_VDB_ADR2 LV_VDB_ADR_INV
#define LV_VDB_DOUBLE 0
#define LV_VDB_PX_BPP LV_COLOR_SIZE

#define LV_ANTIALIAS 1

#define LV_MEM_CUSTOM 0
#define LV_MEM_SIZE (32U * 1024U)
#define LV_MEM_ATTR
#define LV_MEM_DEFRAG 1

#define LV_INV_FIFO_SIZE 32
#define LV_REFR_PERIOD 30

#include <lv_misc/lv_font.h>
LV_FONT_DECLARE(lv_font_dejavu_20);
#define LV_FONT_DEFAULT &lv_font_dejavu_20

#define LV_COLOR_TRANSP LV_COLOR_LIME

#endif
