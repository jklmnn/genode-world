
#include <base/log.h>
#include <util/string.h>

#include <client.h>
#include <sntp.h>

/* socket */

Sntp::Client::Client() :
    _addr(0), s(0)
{
    const char host[] = "0.pool.ntp.org";
    s = sntp__c_connect(host, Genode::strlen(host), &_addr);
    if(s < 0){
        throw Sntp::Connection_failed();
    }
}


Genode::uint64_t Sntp::Client::timestamp()
{
    return (Genode::uint64_t)sntp__get_time(s, _addr);
}
