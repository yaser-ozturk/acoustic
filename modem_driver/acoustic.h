//
// Created by User on 27.03.2025.
//

#ifndef ACOUSTIC_H
#define ACOUSTIC_H



#include <iostream>
#include <string>
#include <vector>

// To read Message
class MessageClass {

public:
    std::string adres{" Nothing "};
    std::string val{" Nothing "};
    std::string sms{" Nothing "};
};


// To create Message
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


class Acoustic{

    public:

    std::string send_just(const std::string& sms) {

        SendMessageClass S;

        S.sms = sms;
        S.adress = "2209";
        S.fill_buffer.m_send_immediate_buf = false;
        S.exchange_type.m_ack_only = false;
        S.ranging.m_ranging_enabled = false;
        S.on_port.m_on_port_zero=false;



        std::string sms_message = create_message(S);
        std::cout << "Sms sended: " << sms_message << std::endl;

        return sms_message;

    }

    void recive(const std::string& sms){

        std::cout << message_find(sms);
    }

    void detalied_recive(const std::string& sms){

        parser(sms);
    }


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

        std::string comma = ",";
        std::vector<int> s_comma;
        std::string line = "|";
        std::string colon = ":";
        std::string end = "\r\n";




    MessageClass parser(const std::string& sms_message) {

            const std::string flag = ">SMS:";

            size_t found = sms_message.find(flag);

            if (found == std::string::npos) {

                std::cout << "SMS  bulunamadı!" << std::endl;
                return {};
            }

            const std::string values = value_find(sms_message);
            std::cout << std::endl << ":::  Read Values ::: "<< std::endl <<  values << std::endl;

            const std::string message = message_find(sms_message);
            std::cout << std::endl << ":::  Read Message ::: "<< std::endl <<  message << std::endl;
            SmsObj.sms=message;
            return SmsObj;

        }

    static bool is_it_sms(std::string &sms_message) {

            const std::string flag = ">SMS:";
            size_t found = sms_message.find(flag);

            if (found == std::string::npos) {
                std::cout << "SMS  bulunamadı!" << std::endl;
                return false;
            }
            return true;

        }

    MessageClass SmsObj;

    std::string message_find(const std::string& sms_message) const {

        std::string readed_sms;
        const size_t s_end = sms_message.find(end);
        const size_t s_line = sms_message.find(line);

        std::string message;

        if (s_line != std::string::npos) {

            message = sms_message.substr(s_line + 1,s_end-s_line-1);
            readed_sms += " Messages " + message + end;
        }
        else {

            readed_sms += " Message Not Found ";
        }


        return message ;

    }


    std::string value_find(const std::string& sms_message) {
        std::string readed_sms;
        size_t s_colon = sms_message.find(colon);
        size_t s_line = sms_message.find(line);

        if (sms_message.find(comma) == std::string::npos) {

            std::string val = sms_message.substr(s_colon + 1, s_line -1);
            readed_sms += " val : " + val + end;
            return readed_sms;
        }


        s_comma.push_back(sms_message.find(comma));
        int i = 0;
        int finded_comma = s_comma[0];
        std::string trim_for_vir = sms_message;

        while (finded_comma != std::string::npos) {

            trim_for_vir = trim_for_vir.substr(finded_comma + 1, (s_line - finded_comma));
            finded_comma = trim_for_vir.find(comma);
            s_comma.push_back(trim_for_vir.find(comma) + s_comma[i] + 1);
            i++;
        }

        for(int j=0 ; j <= s_comma.size() ; j++ ) {

            if (s_comma[j] != 0 && j == 0) {

                std::string address = sms_message.substr(s_colon + 1, (s_comma[j]-s_colon) -1);
                //readed_sms += " adress " + address + end;
                SmsObj.adres = address;
            }
            if (s_comma[j] != 0 && j != 0 && j < s_comma.size()-1 ) {

                std::string val = sms_message.substr((s_comma[j-1]+1), (s_comma[j]- s_comma[j-1]) -1 );
                readed_sms += " val : " + val + end;

            }
            if (s_comma[j] != 0 && j == s_comma.size()) {

                std::string val = sms_message.substr((s_comma[j-1]+1), (s_line- s_comma[j-1]) -1 );
                readed_sms += " val : " + val + end;
            }

        }
        SmsObj.val = readed_sms;

        return readed_sms;

    }


};

#endif //ACOUSTIC_H
