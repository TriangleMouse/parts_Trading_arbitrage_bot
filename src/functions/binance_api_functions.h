//
// Created by Артем Белявский on 8/11/21.
//

#ifndef TRADEBOT_BINANCE_API_FUNCTIONS_H
#define TRADEBOT_BINANCE_API_FUNCTIONS_H


#include "../data/types/double.h"
//#include "../data/types/task_type.h"
//#include "../data/types/trade_report.h"
#include "../data/data_box.h"
#include "../threads/http_client.h"
#include "cpprest/http_client.h"
#include "cpprest/details/http_helpers.h"
#include "cpprest/http_msg.h"
#include <string>
#include <memory>

namespace FUNCTIONS{
    bool Active_Binance_Symbols();
    bool Active_Binance_Balance();
    bool Binance_Best_Price_Symbol(const std::string& symbol);

}


#endif //TRADEBOT_BINANCE_API_FUNCTIONS_H
