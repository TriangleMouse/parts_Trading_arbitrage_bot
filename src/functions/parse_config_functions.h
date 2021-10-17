//
// Created by Артем Белявский on 8/16/21.
//

#ifndef TRADEBOT_PARSE_CONFIG_FUNCTIONS_H
#define TRADEBOT_PARSE_CONFIG_FUNCTIONS_H

#include <string>

namespace FUNCTIONS {

    bool Parse_Local_ConfigFile();
    bool Parse_RemoteConfig(std::shared_ptr<std::string>);
}

#endif //TRADEBOT_PARSE_CONFIG_FUNCTIONS_H
