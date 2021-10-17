//
// Created by Артем Белявский on 8/15/21.
//

#ifndef TRADEBOT_TRADE_TYPE_H
#define TRADEBOT_TRADE_TYPE_H

#include <string>

namespace DATA {
    namespace TYPES {

        enum class Trade_Type
                : unsigned char {
            UNDEFINED, ASK_LINK, BID_LINK, BUY, SELL, LAST
        };

        bool TradeTypeIsValide(const Trade_Type&);
        std::string TradeTypeToString(const Trade_Type&);

    }  // namespace TYPES
}  // namespace DATA

#endif //TRADEBOT_TRADE_TYPE_H
