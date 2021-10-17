//
// Created by Артем Белявский on 8/15/21.
//

#include "stock_market_info.h"
#include "../helpers/locker.h"

using namespace DATA;
using namespace TYPES;
using namespace HELPERS;

using namespace std;

StockMarketInfo::StockMarketInfo() :
        _symbols_info_mutex(new mutex), _markets_status_mutex(new mutex), _symbol_names_mutex(
        new mutex) {
}

StockMarketInfo::~StockMarketInfo() {
    locker_t symbol_locker(*_symbols_info_mutex, defer_lock);
    locker_t market_locker(*_markets_status_mutex, defer_lock);
    lock(symbol_locker, market_locker);
}

void StockMarketInfo::PushSymbolInfo(shared_ptr<SymbolInfo> symbol_info) {
    locker_t info_locker(*_symbols_info_mutex, defer_lock);
    locker_t name_locker(*_symbol_names_mutex, defer_lock);
    lock(info_locker, name_locker);

    for (auto& it : _symbols_info) {
        if (it == symbol_info) {
            return;
        }
    }

    for (auto& it : _symbols_info) {
        if (it->name() == symbol_info->name()) {
            return;
        }
    }

    _symbols_info.push_back(symbol_info);

    switch(symbol_info->flagship_store()){
        case Market_Type::BINANCE:
            _binance_symbol_names.insert(symbol_info->binance_name());
            break;
        default:
            break;
    }

    switch(symbol_info->market_type()){
        case Market_Type::MOSCOW_EXCHANGE:
            _moscow_symbol_names.insert(symbol_info->moscow_name());
            break;
        default:
            break;
    }

}

void StockMarketInfo::PushSymbolStatus(shared_ptr<SymbolStatus> symbol_status) {
    locker_t status_locker(*_markets_status_mutex);

    for (auto& it : _markets_status) {
        if (it == symbol_status) {
            return;
        }
    }

    for (auto& it : _markets_status) {
        if (it->name() == symbol_status->name()) {
            return;
        }
    }

    _markets_status.push_back(symbol_status);
}

shared_ptr<SymbolInfo> StockMarketInfo::FindSymbolInfo(
        const string& symbol_name) {
    locker_t symbols_locker(*_symbols_info_mutex);
    for (auto& it : _symbols_info) {
        if (it->name() == symbol_name) {
            return it;
        }
    }

    return shared_ptr<SymbolInfo>();
}

shared_ptr<SymbolStatus> StockMarketInfo::FindSymbolStatus(
        const string& symbol_name) {
    locker_t status_locker(*_markets_status_mutex);
    for (auto& it : _markets_status) {
        if (it->name() == symbol_name) {
            return it;
        }
    }

    return shared_ptr<SymbolStatus>();
}



set<string> StockMarketInfo::GetBinanceSymbolNames(){
    locker_t locker(*_symbol_names_mutex);
    return _binance_symbol_names;
}

set<string> StockMarketInfo::GetMoscowSymbolNames() {
    locker_t locker(*_symbol_names_mutex);
    return _moscow_symbol_names;
}


size_t StockMarketInfo::Size() {
    locker_t locker(*_symbols_info_mutex);
    return _symbols_info.size();
}
