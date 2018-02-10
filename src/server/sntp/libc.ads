with System;

package libc
with
SPARK_Mode => On
is

    type Addrinfo is new System.Address;
    type Socket is new Integer;

    function getaddrinfo(Address : String; Ai : Addrinfo) return Integer
      with
        Pre => Address'Last < Integer'Last,
        Global => null;

    function getsocket(Ai : Addrinfo) return Socket
    with
        Import,
        Convention => C,
        External_Name => "libc_socket",
        Global => null;

    generic
        type Data is private;
        Data_Size : Integer;
    procedure send(Sock : Socket; Msg : Data; Ai : Addrinfo; Sent : out Long_Integer)
      with
        Pre => Sock >= 0 and Data_Size <= Integer'Last;

    generic
        type Data is private;
        Data_Size : Integer;
    procedure recv(Sock : Socket; Msg : out Data; Ai : Addrinfo; Timeout : Long_Integer; Received : out Long_Integer)
      with
        Pre => Sock >= 0 and Data_Size <= Integer'Last;

    generic
        type U32 is private;
    function ntohl(Net : U32) return U32
    with
        Import,
        Convention => C,
        External_Name => "libc_ntohl",
        Global => null;

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
        External_Name => "libc_send",
        Global => null;

    function lc_recv(S : Socket; Data : System.Address; Size : Integer; Ai : Addrinfo; Timeout : Long_Integer) return Long_Integer
    with
        Import,
        Convention => C,
        External_Name => "libc_recv",
        Global => null;

end libc;
