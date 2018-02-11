with System;
with libc_types;
with sntp_types;

use all type libc_types.Socket;

package sntp
with
    SPARK_Mode => On
is

    function c_connect(Host : System.Address; Length : Integer; Ai : libc_types.Addrinfo)
                       return libc_types.Socket;
    function connect(Host : String; Ai : libc_types.Addrinfo) return libc_types.Socket
      with
        Pre => Host'Last < Integer'Last;
    function get_time(Sock : libc_types.Socket; Ai : libc_types.Addrinfo; Timeout : Long_Integer)
                      return sntp_types.Timestamp;

end sntp;
