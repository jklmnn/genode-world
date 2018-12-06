
#include <util/string.h>
#include <stdint.h>

extern "C" {

    void *memcpy(void *dst, const void *src, size_t size)
    {
        return Genode::memcpy(dst, src, size);
    }

    void *memset(void *s, int c, size_t n)
    {
        return Genode::memset(s, c, n);
    }

    size_t strlen(const char *s)
    {
        return Genode::strlen(s);
    }

    char *strcpy(char *dest, const char *src)
    {
        return Genode::strncpy(dest, src, Genode::strlen(src) + 1);
    }
}
