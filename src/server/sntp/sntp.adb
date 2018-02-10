package body sntp
with
    SPARK_Mode => On
is

    function c_connect(Host : System.Address; Length : Integer; Ai : libc.Addrinfo) return libc.Socket
    with
        SPARK_Mode => Off
    is
        S_Host : String (1 .. Length);
        for S_Host'Address use Host;
    begin
        return connect(S_Host, Ai);
    end c_connect;

    function connect(Host : String; Ai : libc.Addrinfo) return libc.Socket
    is
        Addr_status : Integer := libc.getaddrinfo(Host, Ai);
        Sock : libc.Socket := -42;
    begin
        if Addr_status = 0 then
            Sock := libc.getsocket(Ai);
        end if;
        return Sock;
    end connect;

    function get_time(Sock : libc.Socket; Ai : libc.Addrinfo; Timeout : Long_Integer) return Timestamp
    is
        Msg : Message := ( Leap => AlarmCondition, Version => 2, Mode => Client, Poll => 4,
            Precision => 0, Root_Delay => 0, Root_Dispersion => 0, Stratum => 0, others => 0);
        Sent : Long_Integer;
        Received : Long_Integer;
        Ts : Timestamp;
    begin
        Send(Sock, Msg, Ai, Sent);
        if Sent > 0 then
            Recv(Sock, Msg, Ai, Timeout, Received);
            if Received > 0 then
                Ts := Swap(Msg.Transmit_Timestamp_Sec) - Unix_Epoch;
            end if;
        end if;
        return Ts;
    end get_time;

end sntp;
        
