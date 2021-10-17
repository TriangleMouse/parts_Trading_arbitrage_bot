//
// Created by Артем Белявский on 8/15/21.
//

#include "stock_market.h"
#include "../helpers/locker.h"

using namespace DATA;
using namespace TYPES;
using namespace HELPERS;
using namespace std;

StockMarket::StockMarket() :
        _markets_mutex(new mutex), _orders_mutex(new mutex) {
}

StockMarket::~StockMarket() {
    locker_t locker(*_markets_mutex);
}

void StockMarket::CreateMarket(shared_ptr<TYPES::SymbolInfo> symbol_info) {
    if (!symbol_info) {
        return;
    }

    if (!FindMarket(symbol_info->binance_name())) {
        locker_t markets_locker(*_markets_mutex);
        _markets.push_back(make_shared<Market>(symbol_info));
    }
}

shared_ptr<Market> StockMarket::FindMarket(const string& symbol_name) {
    locker_t locker(*_markets_mutex);
    for (auto& it : _markets) {
        if (it->CheckSymbolName(symbol_name)) {
            return it;
        }
    }

    return shared_ptr<Market>();
}

void StockMarket::CreadOrdersBox(shared_ptr<SymbolInfo> symbol_info) {
    if (!symbol_info) {
        return;
    }

    if (!FindOrdersBox(symbol_info->binance_name())) {
        locker_t markets_locker(*_orders_mutex);
        _orders.push_back(make_shared<OrderLinks>(symbol_info));
    }
}

shared_ptr<OrderLinks> StockMarket::FindOrdersBox(const string& symbol_name) {
    locker_t locker(*_orders_mutex);
    for (auto& it : _orders) {
        if (it->CheckSymbolName(symbol_name)) {
            return it;
        }
    }
    return shared_ptr<OrderLinks>();
}
