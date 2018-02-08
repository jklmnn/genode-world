
#include <libc/component.h>
#include <util/string.h>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

extern "C" {

    int libc_getaddrinfo(char *address, struct addrinfo **addr)
    {
        struct addrinfo hints;
        int status = -1;

        Libc::with_libc([&] () {
                Genode::memset(&hints, 0, sizeof(struct addrinfo));
                
                hints.ai_family = AF_UNSPEC;
                hints.ai_socktype = SOCK_DGRAM;

                status = getaddrinfo(address, "123", &hints, addr);
                });

        return status;
    }

    int libc_socket(struct addrinfo **ai_ptr)
    {
        struct addrinfo *ai = *ai_ptr;
        int status = -1;

        Libc::with_libc([&] () {
                status = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
                });

        return status;
    }

    long libc_send(int s, void *data, size_t length, struct addrinfo *ai)
    {
        long sent = 0;
        Libc::with_libc([&] (){
                sent = sendto(s, data, length, 0, ai->ai_addr, sizeof(struct sockaddr_in));
                });
        return sent;
    }

    long libc_recv(int s, void *data, size_t length, struct addrinfo *ai)
    {
        long received = 0;
        unsigned socklen = 0;
        Libc::with_libc([&] (){
                received = recvfrom(s, data, length, 0, ai->ai_addr, &socklen);
                });
        return received;
    }

    Genode::uint32_t libc_ntohl(Genode::uint32_t net)
    {
        return ntohl(net);
    }

} // extern C
