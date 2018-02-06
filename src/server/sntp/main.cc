
#include <libc/component.h>
#include <base/log.h>

#include <client.h>

namespace Sntp {
    struct Main;
};

struct Sntp::Main
{
    Genode::Env &_env;

    Sntp::Client _client;

    Main(Genode::Env &env) :
        _env(env), _client(env)
    {
        Genode::log("---sntp---");
        Genode::log(_client.timestamp());
    }
};

void Libc::Component::construct(Libc::Env &env)
{
    static Sntp::Main main(env);
}
