//
// Created by User on 12.03.2025.
//

#ifndef PARSER_H
#define PARSER_H

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

class MessageClass {

public:
    std::string adres{" Nothing "} ;
    std::string val{" Nothing "} ;
    std::string sms{" Nothing "} ;
};

class Parser {

private:
    std::string comma = ",";
    std::vector<int> s_comma;
    std::string line = "|";
    std::string colon = ":";
    std::string end = "\r\n";

    std::string value_find(const std::string sms_message) {
        std::string readed_sms;
        size_t s_colon = sms_message.find(colon);
        size_t s_line = sms_message.find(line);

        if (sms_message.find(comma) == std::string::npos) {

            std::string val = sms_message.substr(s_colon + 1, s_line -1);
            readed_sms += " val 1 : " + val + end;
            return readed_sms;
        }


        s_comma.push_back(sms_message.find(comma));
        int i = 0;
        int finded_comma = s_comma[0];
        std::string trim_for_vir = sms_message;

        while (finded_comma != std::string::npos) {

            trim_for_vir = trim_for_vir.substr(finded_comma + 1, (s_line - finded_comma));
            finded_comma = trim_for_vir.find(",");
            s_comma.push_back(trim_for_vir.find(",") + s_comma[i] + 1);
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
                readed_sms += " val " + std::to_string(j) + ": " + val + end;

            }
            if (s_comma[j] != 0 && j == s_comma.size()) {

                std::string val = sms_message.substr((s_comma[j-1]+1), (s_line- s_comma[j-1]) -1 );
                readed_sms += " val " + std::to_string(j) + ": " + val + end;
            }

        }
        SmsObj.val = readed_sms;

        return readed_sms;

    }


public:

    MessageClass SmsObj;

    std::string message_find(const std::string sms_message) {

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

    bool is_it_sms(std::string &sms_message) {

        const std::string flag = ">SMS:";
        size_t found = sms_message.find(flag);

        if (found == std::string::npos) {
            std::cout << "SMS  bulunamadı!" << std::endl;
            return false;
        }
            return true;

    }
    MessageClass parser(std::string sms_message) {

        const std::string flag = ">SMS:";

        size_t found = sms_message.find(flag);

        if (found == std::string::npos) {

            std::cout << "SMS  bulunamadı!" << std::endl;
            return MessageClass();
        }

        std::string values = value_find(sms_message);
        std::cout << std::endl << ":::  Readed Values ::: "<< std::endl <<  values << std::endl;

        std::string message = message_find(sms_message);
        std::cout << std::endl << ":::  Readed Message ::: "<< std::endl <<  message << std::endl;
        SmsObj.sms=message;
        return SmsObj;

    }
};






#endif //PARSER_H
