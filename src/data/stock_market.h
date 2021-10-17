//
// Created by Артем Белявский on 8/15/21.
//

#ifndef TRADEBOT_STOCK_MARKET_H
#define TRADEBOT_STOCK_MARKET_H

#include "market.h"
#include "order_links.h"
#include "types/symbol_information.h"
#include "types/symbol_status.h"
#include "../helpers/non_copyable.h"

#include <string>
#include <vector>
#include <memory>
#include <mutex>

namespace DATA {

    class StockMarket: public HELPERS::NonCopyable {
    public:
        StockMarket();
        ~StockMarket();

        void CreateMarket(std::shared_ptr<TYPES::SymbolInfo>);
        std::shared_ptr<Market> FindMarket(const std::string&);

        void CreadOrdersBox(std::shared_ptr<TYPES::SymbolInfo>);
        std::shared_ptr<OrderLinks> FindOrdersBox(const std::string&);

    private:
        std::vector<std::shared_ptr<Market>> _markets;
        std::unique_ptr<std::mutex> _markets_mutex;

        std::vector<std::shared_ptr<OrderLinks>> _orders;
        std::unique_ptr<std::mutex> _orders_mutex;
    };

}  // namespace DATA

#endif //TRADEBOT_STOCK_MARKET_H
