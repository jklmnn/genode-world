
#include <base/log.h>
#include <util/string.h>

#include <client.h>

/* socket */
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

Sntp::Client::Client(Genode::Env &env) :
    _timer(env), _addr(0), s(0)
{
    struct addrinfo hints;

    Genode::memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    _timer.msleep(6000);
    //FIXME: Error: libc suspend() called from non-user context (0x116949a) - aborting
    while(getaddrinfo("0.pool.ntp.org", "123", 0, &_addr)){
        Genode::warning("getaddrinfo failed, retrying...");
        _timer.msleep(1000);
    }

    s = socket(_addr->ai_family, _addr->ai_socktype, _addr->ai_protocol);
    if(s < 0){
        throw Sntp::Socket_failed();
    }
}

void Sntp::Client::prepare_message(Sntp::Message *msg)
{
    Genode::memset(msg, 0, sizeof(Sntp::Message));

    msg->leap_indicator = Sntp::Leap_indicator::AlarmCondition;
    msg->version = 2;
    msg->mode = 3;//Sntp::Mode::Client;
    msg->poll = 4;
}

Genode::uint64_t Sntp::Client::ntoh64(Genode::uint64_t be){

    Genode::uint64_t le = 0;
    Genode::uint8_t *conv = (Genode::uint8_t*)&le;
    
    conv[0] = be >> 56;
    conv[1] = be >> 48;
    conv[2] = be >> 40;
    conv[3] = be >> 32;
    conv[4] = be >> 24;
    conv[5] = be >> 16;
    conv[6] = be >> 8;
    conv[7] = be >> 0;
    
    return le;
}

Genode::uint64_t Sntp::Client::timestamp()
{
    Sntp::Message msg;
    prepare_message(&msg);

    ssize_t sent = sendto(s, &msg, sizeof(Sntp::Message), 0, _addr->ai_addr, sizeof(struct sockaddr_in));
    if(sent < (ssize_t)sizeof(Sntp::Message)){
        Genode::warning("sendto incomplete");
    }

    unsigned socklen = 0;
    ssize_t received = recvfrom(s, &msg, sizeof(Sntp::Message), 0, _addr->ai_addr, &socklen);
    if(received < (ssize_t)sizeof(Sntp::Message)){
        Genode::warning("recvfrom incomplete");
    }

    return (ntoh64(msg.transmit_timestamp) >> 32) - UNIX_EPOCH;
}
