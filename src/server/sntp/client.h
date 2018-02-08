
#include <base/fixed_stdint.h>

#include <netdb.h>

namespace Sntp {
    class Client;
    class Connection_failed : Genode::Exception {};
};

class Sntp::Client
{
    private:

        struct addrinfo *_addr;
        int s;

    public:
        Client();

        Genode::uint64_t timestamp();
};

