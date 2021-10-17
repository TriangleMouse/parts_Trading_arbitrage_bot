//
// Created by Артем Белявский on 8/14/21.
//

#ifndef TRADEBOT_SYMBOL_INFORMATION_H
#define TRADEBOT_SYMBOL_INFORMATION_H

#include "symbol_name.h"
#include "../../helpers/non_copyable.h"
#include "double.h"
#include "market_type.h"
//#include "markup_type.h"

#include <string>
#include <mutex>
#include <memory>

namespace DATA {
    namespace TYPES {

        class SymbolInfo: public HELPERS::NonCopyable {
        public:
            SymbolInfo();
            ~SymbolInfo() = default;

            SymbolName name() const;
            void name(SymbolName);
            Market_Type market_type() const;
            void market_type(Market_Type);
            Market_Type flagship_store() const;
            void flagship_store(Market_Type);
            Double min_spread() const;
            void min_spread(Double);
            Double binance_disregarded_bid_vol() const;
            void binance_disregarded_bid_vol(Double);
            Double binance_disregarded_ask_vol() const;
            void binance_disregarded_ask_vol(Double);

            std::string moscow_name() const;
            void moscow_name(const std::string&);
            std::string binance_name() const;
            void binance_name(const std::string&);
            std::string binance_base_cur() const;
            void binance_base_cur(const std::string&);
            std::string binance_quote_cur() const;
            void binance_quote_cur(const std::string&);



            Double min_amount() const;
            void min_amount(Double);
            Double ask_limit() const; // Хранит баланс второй валюты в паре
            void ask_limit(Double);
            Double bid_limit() const; // Хранит баланс первой валюты в паре
            void bid_limit(Double);


            Double min_price() const;
            void min_price(Double);
            Double max_price() const;
            void max_price(Double);
            Double export_min_amount() const;
            void export_min_amount(Double);
            Double binance_min_total() const;
            void binance_min_total(Double);
            Double binance_bid_price() const;
            void binance_bid_price(Double);// лучшая цена бид по символу
            Double binance_ask_price() const;// лучшая цена аск по символу
            void binance_ask_price(Double);




            Double new_order_barrier() const;
            void new_order_barrier(Double);
            Double min_rand() const;
            void min_rand(Double);
            Double max_rand() const;
            void max_rand(Double);
            int precession() const;
            void precession(int);
            int volume_precession() const;
            void volume_precession(int);

        private:
            SymbolName _name;
            Market_Type _market_type;
            Market_Type _flagship_store;

            Double _min_amount;
            Double _export_min_amount;

            Double _ask_markup_val;
            Double _bid_markup_val;
            Double _ask_limit;
            Double _bid_limit;
            Double _min_price;
            Double _max_price;

            Double _new_order_barrier;
            Double _min_rand;
            Double _max_rand;
            Double _min_spread;
            Double _binance_disregarded_bid_vol;
            Double _binance_disregarded_ask_vol;
            Double _binance_min_total;
            Double _binance_bid_price;
            Double _binance_ask_price;

            int _precession;
            int _volume_precession;
            mutable std::unique_ptr<std::mutex> _rw_mutex;
        };

    }  // namespace TYPES
}  // namespace DATA


#endif //TRADEBOT_SYMBOL_INFORMATION_H
