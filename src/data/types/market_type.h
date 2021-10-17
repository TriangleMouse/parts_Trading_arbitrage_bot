//
// Created by Артем Белявский on 8/15/21.
//

#ifndef TRADEBOT_MARKET_TYPE_H
#define TRADEBOT_MARKET_TYPE_H


#include <string>

namespace DATA {
    namespace TYPES {

        enum class Market_Type
                : unsigned char {
            UNDEFINED,MOSCOW_EXCHANGE,BINANCE
        };

        std::string MarketTypeToString(const Market_Type&);

    }  // namespace TYPES
}

#endif //TRADEBOT_MARKET_TYPE_H
