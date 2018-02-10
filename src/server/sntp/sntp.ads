with System;
with libc;
use all type libc.Socket;
pragma Elaborate_All (libc);

package sntp
with
    SPARK_Mode => On
is

    type Leap_Indicator is ( NoWarning, SixtyOneSec, FiftyOneSec, AlarmCondition );
    for Leap_Indicator use ( 0, 1, 2, 3 );
    
    type Ntp_Mode is ( Reserved, SymmetricActive, SymmetricPassive, Client, Server,
        Broadcast, ReservedNTP, ReservedPrivate );
    for Ntp_Mode use ( 0, 1, 2, 3, 4, 5, 6, 7 );

    type Ntp_Version is mod 2**3;

    type Byte is mod 2**8;

    type Timestamp is mod 2**32;
    
    Unix_Epoch : constant Timestamp := 2208988800;

    type Message is
        record
            Leap : Leap_Indicator;
            Version : Ntp_Version;
            Mode : Ntp_Mode;
            Stratum : Byte;
            Poll : Byte;
            Precision : Byte;
            Root_Delay : Integer;
            Root_Dispersion : Integer;
            Reference_Identifier : Timestamp;
            Reference_Timestamp_Sec : Timestamp;
            Reference_Timestamp_Frac : Timestamp;
            Originate_Timestamp_Sec : Timestamp;
            Originate_Timestamp_Frac : Timestamp;
            Receive_Timestamp_Sec : Timestamp;
            Receive_Timestamp_Frac : Timestamp;
            Transmit_Timestamp_Sec : Timestamp;
            Transmit_Timestamp_Frac : Timestamp;
        end record;

    for Message use
        record
            Leap                        at 0 range 0 .. 1;
            Version                     at 0 range 2 .. 4;
            Mode                        at 0 range 5 .. 7;
            Stratum                     at 1 range 0 .. 7;
            Poll                        at 2 range 0 .. 7;
            Precision                   at 3 range 0 .. 7;
            Root_Delay                  at 4 range 0 .. 31;
            Root_Dispersion             at 8 range 0 .. 31;
            Reference_Identifier        at 12 range 0 .. 31;
            Reference_Timestamp_Sec     at 16 range 0 .. 31;
            Reference_Timestamp_Frac    at 20 range 0 .. 31;
            Originate_Timestamp_Sec     at 24 range 0 .. 31;
            Originate_Timestamp_Frac    at 28 range 0 .. 31;
            Receive_Timestamp_Sec       at 32 range 0 .. 31;
            Receive_Timestamp_Frac      at 36 range 0 .. 31;
            Transmit_Timestamp_Sec      at 40 range 0 .. 31;
            Transmit_Timestamp_Frac     at 44 range 0 .. 31;
        end record;
    for Message'Size use 384;

    private

    function Swap is new libc.ntohl(Timestamp);
    procedure Send is new libc.send(Message, Message'Size);
    procedure Recv is new libc.recv(Message, Message'Size);

    function c_connect(Host : System.Address; Length : Integer; Ai : libc.Addrinfo) return libc.Socket;
    function connect(Host : String; Ai : libc.Addrinfo) return libc.Socket
      with
        Pre => Host'Last < Integer'Last;
    function get_time(Sock : libc.Socket; Ai : libc.Addrinfo; Timeout : Long_Integer) return Timestamp;

end sntp;
