
#include <libc/component.h>
#include <clock.h>
#include <time.h>

Clock::Clock::Clock(Genode::Env &env) :
    _timer(env), _sync_sigh(env.ep(), *this, &Clock::Clock::synchronize), _rtc(env)
{
    _timer.sigh(_sync_sigh);
    _synced_timestamp = _rtc.current_time();
    _local_timestamp = _timer.elapsed_ms() / 1000;
    _skew = 0;
    _skew_periods = 24;

    _timer.trigger_once(SYNC_TIMEOUT);
}

void Clock::Clock::synchronize()
{
    Rtc::Timestamp synced;
    unsigned long local;
    if(_skew_periods == 24){
        synced = _rtc.current_time();
        local = (_timer.elapsed_ms() / 1000) - _local_timestamp;
        _skew += convert(_synced_timestamp) + local + _skew - convert(synced);
        _synced_timestamp = synced;
        _local_timestamp = local;
        _skew_periods = 0;
        Genode::log("clock synchronized, current skew is ", _skew);
    }else{
        _skew_periods += 1;
    }

    _timer.trigger_once(SYNC_TIMEOUT);
}

unsigned long Clock::Clock::convert(Rtc::Timestamp rtc_ts)
{
    time_t time;
    struct tm stm;

    Genode::memset(&stm, 0, sizeof(struct tm));
    stm.tm_sec = rtc_ts.second;
    stm.tm_min = rtc_ts.minute;
    stm.tm_hour = rtc_ts.hour;
    stm.tm_mday = rtc_ts.day;
    stm.tm_mon = rtc_ts.month - 1;
    stm.tm_year = rtc_ts.year - 1900;

    Libc::with_libc([&] () {
            time = mktime(&stm);
            });

    return (unsigned long)time;
}

Rtc::Timestamp Clock::Clock::convert(unsigned long time)
{
    Rtc::Timestamp ts;
    struct tm *stm;

    Libc::with_libc([&] () {
            stm = gmtime((time_t*)&time);

            ts.second = stm->tm_sec;
            ts.minute = stm->tm_min;
            ts.hour = stm->tm_hour;
            ts.day = stm->tm_mday;
            ts.month = stm->tm_mon + 1;
            ts.year = stm->tm_year + 1900;
            });

    return ts;
}

Rtc::Timestamp Clock::Clock::gettime()
{
    return convert(convert(_synced_timestamp) +
            (_timer.elapsed_ms() / 1000 - _local_timestamp) +
            _skew * _skew_periods);
}
