//
// Created by Артем Белявский on 8/15/21.
//

#include "trade_type.h"

using namespace DATA;
using namespace TYPES;
using namespace std;

bool DATA::TYPES::TradeTypeIsValide(const Trade_Type& type){
    if(Trade_Type::UNDEFINED < type && type < Trade_Type::LAST ){
        return true;
    }

    return false;
}

string DATA::TYPES::TradeTypeToString(const Trade_Type& type) {
    switch (type) {
        case Trade_Type::ASK_LINK:
            return "ASK_LINK";
        case Trade_Type::BID_LINK:
            return "BID_LINK";
        case Trade_Type::BUY:
            return "BUY";
        case Trade_Type::SELL:
            return "SELL";
        default:
            return "UNDEFINED";
    }
}
