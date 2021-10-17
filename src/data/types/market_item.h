//
// Created by Артем Белявский on 8/15/21.
//

#ifndef TRADEBOT_MARKET_ITEM_H
#define TRADEBOT_MARKET_ITEM_H

#include "double.h"

namespace DATA {
    namespace TYPES {

        struct MarketItem {
            Double price;
            Double size;
            Double markup;
        };

    }  // namespace TYPES
}  // namespace DATA

#endif //TRADEBOT_MARKET_ITEM_H
