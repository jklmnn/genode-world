
#include <base/fixed_stdint.h>

#include <netdb.h>

namespace Sntp {
    class Client;
    struct Message;
    enum {
        Li_NoWarning = 0,
        Li_SixtyOneSec = 1,
        Li_FiftyOneSec = 2,
        Li_AlarmCondition = 3
    };
    enum {
        Mode_Reserved = 0,
        Mode_SymmetricActive = 1,
        Mode_SymmetricPassive = 2,
        Mode_Client = 3,
        Mode_Server = 4,
        Mode_Broadcast = 5,
        Mode_ReservedNTP = 6,
        Mode_ReservedPrivate = 7
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

        struct addrinfo *_addr;
        int s;
    
        Genode::uint64_t ntoh64(Genode::uint64_t);
        void prepare_message(Sntp::Message *);

    public:
        Client();

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
} __attribute__((packed));
