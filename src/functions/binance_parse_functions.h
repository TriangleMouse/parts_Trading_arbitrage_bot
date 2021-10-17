//
// Created by Артем Белявский on 8/11/21.
//

#ifndef TRADEBOT_BINANCE_PARSE_FUNCTIONS_H
#define TRADEBOT_BINANCE_PARSE_FUNCTIONS_H

#include "../data/types/market_item.h"
//#include "../data/types/task_type.h"
//#include "../data/types/trade_report.h"
#include "../data/types/symbol_status.h"
#include "../data/data_box.h"
#include "../helpers/math.h"
#include "rapidjson/document.h"


#include <memory>
#include <list>
#include <string>
using namespace DATA;
using namespace TYPES;
using namespace std;
using namespace rapidjson;

namespace FUNCTIONS {
    unsigned Parse_Active_BinanceSymbols(std::shared_ptr < std::string > );
    bool Parse_Active_BinanceBalance(std::shared_ptr<std::string>);
    bool Parse_BinanceMarketTickets(std::list<DATA::TYPES::MarketItem>&,
                                    std::list<DATA::TYPES::MarketItem>&, std::shared_ptr<std::string>);
    bool Parse_Binance_Best_Price_Symbol(std::shared_ptr<std::string>,const std::string& symbol);
    //std::list<DATA::TYPES::OrderReportItem> Parse_Active_BinanceTrade(DATA::TYPES::Task_Type, std::shared_ptr<std::string>);
};
#endif //TRADEBOT_BINANCE_PARSE_FUNCTIONS_H
