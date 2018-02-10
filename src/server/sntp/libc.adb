package body libc
with
SPARK_Mode => Off
is

    function getaddrinfo(Address : String; Ai : Addrinfo) return Integer
    is
        C_Address : String := Address & Character'Val(0);
    begin
        return lc_getaddrinfo(C_Address'Address, Ai);
    end getaddrinfo;

    procedure send(Sock : Socket; Msg : Data; Ai : Addrinfo; Sent : out Long_Integer)
    is
    begin
        Sent := lc_send(Sock, Msg'Address, Data_Size / 8, Ai);
    end send;

    procedure recv(Sock : Socket; Msg : out Data; Ai : Addrinfo; Timeout : Long_Integer; Received : out Long_Integer)
    is
    begin
        Received := lc_recv(Sock, Msg'Address, Data_Size / 8, Ai, Timeout);
    end recv;

end libc;
        
