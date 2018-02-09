with System;


package libc
is

    type Addrinfo is new System.Address;
    type Socket is new Integer;

    function getaddrinfo(Address : String; Ai : Addrinfo) return Integer;

    function getsocket(Ai : Addrinfo) return Socket
    with
        Import,
        Convention => C,
        External_Name => "libc_socket";

    generic
        type Data is private;
    function send(Sock : Socket; Msg : Data; Ai : Addrinfo) return Long_Integer;

    generic
        type Data is private;
    function recv(Sock : Socket; Msg : out Data; Ai : Addrinfo; Timeout : Long_Integer) return Long_Integer;

    generic
        type U32 is private;
    function ntohl(Net : U32) return U32
    with
        Import,
        Convention => C,
        External_Name => "libc_ntohl";

    private

    function lc_getaddrinfo(Addr : System.Address; Ai : Addrinfo) return Integer
    with
        Import,
        Convention => C,
        External_Name => "libc_getaddrinfo";

    function lc_send(S : Socket; Data : System.Address; Size : Integer; Ai : Addrinfo) return Long_Integer
    with
        Import,
        Convention => C,
        External_Name => "libc_send";

    function lc_recv(S : Socket; Data : System.Address; Size : Integer; Ai : Addrinfo; Timeout : Long_Integer) return Long_Integer
    with
        Import,
        Convention => C,
        External_Name => "libc_recv";

end libc;
