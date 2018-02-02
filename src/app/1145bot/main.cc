
#include <libc/component.h>
#include <base/log.h>

#include <telebot.h>

namespace Bot_1145 {
    struct Main;
};

struct Bot_1145::Main
{
    Genode::Env &_env;
    
    Main(Genode::Env &env) : _env(env)
    {
        Genode::log("Bot_1145");
    }
};

void Libc::Component::construct(Libc::Env &env)
{
    static Bot_1145::Main main(env);
}

