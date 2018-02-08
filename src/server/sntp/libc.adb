package body libc
is

    function getaddrinfo(Address : String; Ai : Addrinfo) return Integer
    is
        C_Address : String := Address & Character'Val(0);
    begin
        return lc_getaddrinfo(C_Address'Address, Ai);
    end getaddrinfo;

    function send(Sock : Socket; Msg : Data; Ai : Addrinfo) return Long_Integer
    is
    begin
        return lc_send(Sock, Msg'Address, Msg'Size / 8, Ai);
    end send;

    function recv(Sock : Socket; Ai : Addrinfo) return Data
    is
        Msg : Data;
        Received : Long_Integer := lc_recv(Sock, Msg'Address, Msg'Size / 8, Ai);
    begin
        return Msg;
    end recv;

end libc;
        
