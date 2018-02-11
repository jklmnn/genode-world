with sntp_types;
with libc_types;

package libc
with
SPARK_Mode => On
is

    function getaddrinfo(Address : String; Ai : libc_types.Addrinfo) return Integer
      with
        Pre => Address'Last < Integer'Last,
        Global => null;

    function getsocket(Ai : libc_types.Addrinfo) return libc_types.Socket;

    procedure send(Sock : libc_types.Socket; Msg : sntp_types.Message;
                   Ai : libc_types.Addrinfo; Sent : out Long_Integer)
      with
        Pre => libc_types.">="(Sock, 0);

    procedure recv(Sock : libc_types.Socket; Msg : out sntp_types.Message;
                   Ai : libc_types.Addrinfo; Timeout : Long_Integer; Received : out Long_Integer)
      with
        Pre => libc_types.">="(Sock, 0);

    function ntohl(net : sntp_types.Timestamp) return sntp_types.Timestamp;

end libc;
