//
// Created by Артем Белявский on 8/15/21.
//

#ifndef TRADEBOT_STOCK_MARKET_INFO_H
#define TRADEBOT_STOCK_MARKET_INFO_H


#include "../data/types/symbol_information.h"
#include "../data/types/symbol_status.h"
#include "../helpers/non_copyable.h"

#include <string>
#include <vector>
#include <set>
#include <memory>
#include <mutex>

namespace DATA {

    class StockMarketInfo: public HELPERS::NonCopyable {
    public:
        StockMarketInfo();
        ~StockMarketInfo();

        void PushSymbolInfo(std::shared_ptr<TYPES::SymbolInfo>);
        void PushSymbolStatus(std::shared_ptr<TYPES::SymbolStatus>);

        std::shared_ptr<TYPES::SymbolInfo> FindSymbolInfo(const std::string&);
        std::shared_ptr<TYPES::SymbolStatus> FindSymbolStatus(const std::string&);

        std::set<std::string> GetBinanceSymbolNames();
        std::set<std::string> GetMoscowSymbolNames();


        size_t Size();

    private:
        std::vector<std::shared_ptr<TYPES::SymbolInfo>> _symbols_info;
        std::unique_ptr<std::mutex> _symbols_info_mutex;

        std::vector<std::shared_ptr<TYPES::SymbolStatus>> _markets_status;
        std::unique_ptr<std::mutex> _markets_status_mutex;

        std::set<std::string> _binance_symbol_names;
        std::set<std::string> _moscow_symbol_names;
        std::unique_ptr<std::mutex> _symbol_names_mutex;
    };

}  // namespace DATA


#endif //TRADEBOT_STOCK_MARKET_INFO_H
