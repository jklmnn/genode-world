
#include <libc/component.h>
#include <base/component.h>
#include <rtc_session/connection.h>
#include <timer_session/connection.h>
#include <base/attached_rom_dataspace.h>
#include <util/xml_node.h>

#include <time.h>

struct Main
{
    Genode::Env &_env;

    Timer::Connection _timer;

    Rtc::Connection _x86;
    Rtc::Connection _sntp;

    Genode::Attached_rom_dataspace _config { _env, "config" };

    time_t convert(Rtc::Timestamp ts)
    {
        time_t time;
        struct tm stm;
        
        Genode::memset(&stm, 0, sizeof(struct tm));
        stm.tm_sec = ts.second;
        stm.tm_min = ts.minute;
        stm.tm_hour = ts.hour;
        stm.tm_mday = ts.day;
        stm.tm_mon = ts.month - 1;
        stm.tm_year = ts.year - 1900;

        Libc::with_libc([&] (){
                time = mktime(&stm);
                });

        return time;
    }

    Rtc::Timestamp convert(time_t ts)
    {
        Rtc::Timestamp rts;
        struct tm *stm;
        Libc::with_libc([&] (){
                stm = gmtime(&ts);

                rts.second = stm->tm_sec;
                rts.minute = stm->tm_min;
                rts.hour = stm->tm_hour;
                rts.day = stm->tm_mday;
                rts.month = stm->tm_mon + 1;
                rts.year = stm->tm_year + 1900;
                });

        return rts;
    }

    void print_time(Genode::String<64> label, Rtc::Timestamp ts)
    {
        Genode::log(label, " : ",
            ts.year, "-",ts.month, "-",ts.day, " ",
            ts.hour, ":",ts.minute, ":",ts.second, " ",
                convert(ts));
    }

    Main(Genode::Env &env) : _env(env), _timer(env), _x86(env, "x86"), _sntp(env, "sntp")
    {
        unsigned long timeout = _config.xml().attribute_value<unsigned long>("timeout", 60);
        Genode::log("--- timeskew test (", timeout, "s) ---");
        Rtc::Timestamp sntp_ts_start = _sntp.current_time();
        Rtc::Timestamp x86_ts_start = _x86.current_time();
        Rtc::Timestamp sntp_ts_end;
        Rtc::Timestamp x86_ts_end;

        Genode::log("###");
        print_time(Genode::Cstring("Sntp"), sntp_ts_start);
        print_time(Genode::Cstring("X86"), x86_ts_start);
        Genode::log("###");

        Genode::log("sleeping ", timeout, "s");
        _timer.msleep(timeout * 1000);

        sntp_ts_end = _sntp.current_time();
        x86_ts_end = _x86.current_time();
        
        Genode::log("###");
        print_time(Genode::Cstring("Sntp"), sntp_ts_end);
        print_time(Genode::Cstring("X86"), x86_ts_end);
        print_time(Genode::Cstring("Sntp timer"), convert(convert(sntp_ts_start) + timeout));
        print_time(Genode::Cstring("X86 timer"), convert(convert(x86_ts_start) + timeout));
        Genode::log("Sntp skew: ", convert(sntp_ts_end) - (convert(sntp_ts_start) + timeout));
        Genode::log("X86 skew: ", convert(x86_ts_end) - (convert(x86_ts_start) + timeout));
        Genode::log("###");
    }
};

void Libc::Component::construct(Libc::Env &env)
{
    static Main main(env);
}
