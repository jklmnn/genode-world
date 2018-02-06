
#include <base/fixed_stdint.h>
#include <timer_session/connection.h>

#include <netdb.h>

namespace Sntp {
    class Client;
    struct Message;
    enum Leap_indicator {
        NoWarning = 0,
        SixtyOneSec = 1,
        FiftyOneSec = 2,
        AlarmCondition = 3
    };
    enum Mode {
        Reserved = 0,
        SymmetricActive = 1,
        SymmetricPassive = 2,
//        Client = 3,
        Server = 4,
        Broadcast = 5,
        ReservedNTP = 6,
        ReservedPrivate = 7
    };
    enum {
        UNIX_EPOCH = 2208988800UL
    };
    class Socket_failed : Genode::Exception {};
    class Getaddrinfo_failed : Genode::Exception {};
    class Sendto_failed : Genode::Exception {};
    class Recvfrom_failed : Genode::Exception {};
};

class Sntp::Client
{
    private:

        Timer::Connection _timer;

        struct addrinfo *_addr;
        int s;
    
        Genode::uint64_t ntoh64(Genode::uint64_t);
        void prepare_message(Sntp::Message *);

    public:
        Client(Genode::Env &);

        Genode::uint64_t timestamp();
};

struct Sntp::Message
{
    Genode::uint8_t leap_indicator : 2;
    Genode::uint8_t version : 3;
    Genode::uint8_t mode : 3;
    Genode::uint8_t stratum;
    Genode::uint8_t poll;
    Genode::uint8_t precision;
    Genode::uint32_t root_delay;
    Genode::uint32_t root_dispersion;
    Genode::uint32_t reference_identifier;
    Genode::uint64_t reference_timestamp;
    Genode::uint64_t originate_timestamp;
    Genode::uint64_t receive_timestamp;
    Genode::uint64_t transmit_timestamp;
};
