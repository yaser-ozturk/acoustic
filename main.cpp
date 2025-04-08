#include "acoustic.h"
#include "SimpleSerial.h"

int main() {

    /*

    Acoustic a;

    std::string sms = a.send_just("AUV IS OPEN");


    a.recive(">SMS:2209,R1,|AUV IS OKEY");
    a.detalied_recive(">SMS:2209,R1|AUV IS OKEY");

    */



    char com_port[] = R"(\\.\COM15)";
    DWORD COM_BAUD_RATE = CBR_9600;
    SimpleSerial Serial(com_port, COM_BAUD_RATE);


    if(Serial.IsConnected()) {
        Serial.WriteSerialPort("<SMS:2309|test");
    }
    /*
    int reply_wait_time = 7;
    std::string syntax_type = "mine";

    std::string incoming = Serial.ReadSerialPort(reply_wait_time, syntax_type);

    //Serial.WriteSerialPort("<SMS:2309|test");

    */



    return 0;
}
