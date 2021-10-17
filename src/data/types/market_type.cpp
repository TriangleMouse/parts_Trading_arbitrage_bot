//
// Created by Артем Белявский on 8/15/21.
//

#include "market_type.h"

using namespace DATA;
using namespace TYPES;
using namespace std;

string DATA::TYPES::MarketTypeToString(const Market_Type& type) {
    switch (type) {
        case Market_Type::MOSCOW_EXCHANGE:
            return "MOSCOW_EXCHANGE";
        case Market_Type::BINANCE:
            return "BINANCE";
        default:
            return "UNDEFINED";
    }
}
