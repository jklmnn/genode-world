
#include <util/string.h>

extern "C" {

    inline void *memcpy(void *dst, const void *src, Genode::size_t size)
    {
        return Genode::memcpy(dst, src, size);
    }

}
