#ifndef PACKAGER_H
#define PACKAGER_H


#include <iostream>
#include <string>

class SendMessageClass {

    public:

        struct FillBuffer {
        public:

            bool m_send_immediate_buf{false};
            bool m_load_into_long_data_buf{false};
            bool m_load_into_short_data_buf{false};
        };

        struct ExchangeType {
        public:

            bool m_standart_exchange{false};
            bool m_ack_only{false};
            bool m_do_not_respoud{false};

        };

        struct RangingEnabled {

        public:
            bool m_ranging_enabled{false};
        };

        struct OnPortZero {

        public:
            bool m_on_port_zero{false};
        };

        std::string adress{};
        std::string sms{};
        std::string b_value{};
        std::string a_value{};
        std::string r_value{};
        std::string p_value{};


        FillBuffer fill_buffer;
        ExchangeType exchange_type;
        RangingEnabled ranging;
        OnPortZero on_port;
};

class Packager{



public:

    std::string create_message(SendMessageClass Sms) {

        if (Sms.fill_buffer.m_send_immediate_buf) {
            Sms.b_value = ",B0";
        } else if (Sms.fill_buffer.m_load_into_long_data_buf) {
            Sms.b_value = ",B1";
        } else if (Sms.fill_buffer.m_load_into_short_data_buf) {
            Sms.b_value = ",B2";
        }

        if (Sms.exchange_type.m_standart_exchange) {
            Sms.a_value = ",A0";
        } else if (Sms.exchange_type.m_ack_only) {
            Sms.a_value = ",A1";
        } else if (Sms.exchange_type.m_do_not_respoud) {
            Sms.a_value = ",A3";
        }

        if (Sms.ranging.m_ranging_enabled) {
            Sms.r_value = ",R1";
        }

        if (Sms.on_port.m_on_port_zero) {
            Sms.p_value = ",P0";
        }

        returned_sms = begin + Sms.adress + Sms.p_value + Sms.b_value + Sms.a_value + Sms.r_value + line + Sms.sms + end;

        if (Sms.adress.empty()) {
            returned_sms.erase(5, 1);
        }

        return returned_sms;
    }

private:
    std::string returned_sms{};
    std::string begin {"<SMS:"};
    std::string comma {","};
    std::string line {"|"};
    std::string end = {"\r\n"};


};



#endif //PACKAGER_H
