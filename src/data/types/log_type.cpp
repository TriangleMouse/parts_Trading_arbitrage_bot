//
// Created by Артем Белявский on 8/14/21.
//

#include "log_type.h"

using namespace DATA;
using namespace TYPES;
using namespace std;

string DATA::TYPES::LogTypeToString(Log_Type type) {
    switch (type) {
        case Log_Type::TRADE:
            return "LOG_TRADE";
        case Log_Type::ERR_BINANCE:
            return "LOG_ERR_BINANCE";
        case Log_Type::ERR_MODEL:
            return "LOG_ERR_PARSE";
        case Log_Type::ERR_PARSE:
            return "LOG_ERR_MODEL";
        case Log_Type::DEBUG:
            return "LOG_DEBUG";
        default:
            return "LOG_UNDEFINED";
    }
}
