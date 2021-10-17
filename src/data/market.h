//
// Created by Артем Белявский on 8/15/21.
//

#ifndef TRADEBOT_MARKET_H
#define TRADEBOT_MARKET_H

//#include <data/types/best_price.h>
#include "types/symbol_information.h"
#include "types/market_item.h"
#include "types/double.h"
#include "../helpers/non_copyable.h"

#include <string>
#include <map>
#include <list>
#include <memory>
#include <functional>
#include <mutex>

namespace DATA {

    class Market: public HELPERS::NonCopyable {
    public:
        explicit Market(std::shared_ptr<TYPES::SymbolInfo>);
        ~Market();

        void UpdateAskItem(const TYPES::MarketItem& delta);
        void UpdateBidItem(const TYPES::MarketItem& delta);
        void UpdateAskItem(const std::list<TYPES::MarketItem>&);
        void UpdateBidItem(const std::list<TYPES::MarketItem>&);

        TYPES::Double GetAskSize(TYPES::Double);
        TYPES::Double GetBidSize(TYPES::Double);

        std::list<TYPES::MarketItem> GetAskItemsBySize(TYPES::Double start_price,
                                                       TYPES::Double size);
        std::list<TYPES::MarketItem> GetBidItemsBySize(TYPES::Double start_price,
                                                       TYPES::Double size);
        std::list<TYPES::MarketItem> GetAskItems();

        std::list<TYPES::MarketItem> GetAskItemsByPrice(TYPES::Double start_price,
                                                        TYPES::Double stop_price);
        std::list<TYPES::MarketItem> GetBidItemsByPrice(TYPES::Double start_price,
                                                        TYPES::Double stop_price);
        std::list<TYPES::MarketItem> GetBidItems();

        //TYPES::BestPrice GetBestPrise();
        bool CheckSymbolName(const std::string&);


    private:
        std::shared_ptr<TYPES::SymbolInfo> _symbol_info;

        std::map<TYPES::Double, TYPES::Double, std::less<TYPES::Double>> _ask_items;
        std::unique_ptr<std::mutex> _ask_mutex;

        std::map<TYPES::Double, TYPES::Double, std::greater<TYPES::Double>> _bid_items;
        std::unique_ptr<std::mutex> _bid_mutex;
    };

}  // namespace DATA

#endif //TRADEBOT_MARKET_H
