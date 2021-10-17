//
// Created by Артем Белявский on 8/14/21.
//

#ifndef TRADEBOT_LOG_TYPE_H
#define TRADEBOT_LOG_TYPE_H

#include <string>

namespace DATA {
    namespace TYPES {
        enum class Log_Type
                : unsigned char {
            UNDEFINED,
            TRADE,
            ERR_ASERCO,
            ERR_BINANCE,
            ERR_MODEL,
            ERR_PARSE,
            SITE_DEBUG,
            DEBUG
        };

        std::string LogTypeToString(Log_Type);

    }  // namespace TYPES
}
#endif //TRADEBOT_LOG_TYPE_H
