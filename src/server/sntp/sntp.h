
#include <netdb.h>

extern "C" {
    
    int sntp__c_connect(const char *, size_t, struct addrinfo **);
    uint32_t sntp__get_time(int, struct addrinfo *, unsigned);

}
