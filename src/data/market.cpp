//
// Created by Артем Белявский on 8/15/21.
//

#include "market.h"
#include "../helpers/locker.h"
#include "../helpers/math.h"

#include <limits>
#include <mutex>

using namespace DATA;
using namespace TYPES;
using namespace HELPERS;
using namespace std;

Market::Market(shared_ptr<SymbolInfo> symbol_info) :
        _symbol_info(symbol_info), _ask_mutex(new mutex), _bid_mutex(new mutex) {
}

Market::~Market() {
    locker_t ask_locker(*_ask_mutex, defer_lock);
    locker_t bid_locker(*_ask_mutex, defer_lock);
    lock(ask_locker, bid_locker);
}

void Market::UpdateAskItem(const MarketItem& delta) {
    locker_t locker(*_ask_mutex);
    double price = Round(delta.price, _symbol_info->precession());
    auto it = _ask_items.find(price);
    if (it != _ask_items.end()) {
        it->second += delta.size;
        if (it->second < _symbol_info->min_amount()) {
            _ask_items.erase(it);
        }
    } else {
        if (delta.size > _symbol_info->min_amount()) {
            _ask_items[price] = delta.size;
        }
    }
}

void Market::UpdateBidItem(const MarketItem& delta) {
    locker_t locker(*_bid_mutex);
    double price = Round(delta.price, _symbol_info->precession());
    auto it = _bid_items.find(price);
    if (it != _bid_items.end()) {
        it->second += delta.size;
        if (it->second < _symbol_info->min_amount()) {
            _bid_items.erase(it);
        }
    } else {
        if (delta.size > _symbol_info->min_amount()) {
            _bid_items[price] = delta.size;
        }
    }
}

void Market::UpdateAskItem(const list<MarketItem>& chenge) {
    locker_t locker(*_ask_mutex);
    _ask_items.clear();
    int precession = _symbol_info->precession();
    for (auto it : chenge) {
        double price = Round(it.price, precession);
        if (_ask_items.find(price) == _ask_items.end())
            _ask_items[price] = it.size;
        else
            _ask_items[price] += it.size;
    }
}

void Market::UpdateBidItem(const list<MarketItem>& chenge) {
    locker_t locker(*_bid_mutex);
    _bid_items.clear();
    int precession = _symbol_info->precession();
    for (auto it : chenge) {
        double price = Round(it.price, precession);
        if (_bid_items.find(price) == _bid_items.end())
            _bid_items[price] = it.size;
        else
            _bid_items[price] += it.size;
    }
}

Double Market::GetAskSize(Double price) {
    locker_t locker(*_ask_mutex);
    auto size_it = _ask_items.find(price);
    if (size_it != _ask_items.end()) {
        return size_it->second;
    } else {
        return 0.0;
    }
}

Double Market::GetBidSize(Double price) {
    locker_t locker(*_bid_mutex);
    auto size_it = _bid_items.find(price);
    if (size_it != _bid_items.end()) {
        return size_it->second;
    } else {
        return 0.0;
    }
}

list<MarketItem> Market::GetAskItemsBySize(Double start_price, Double size) {
    list<MarketItem> result;
    locker_t locker(*_ask_mutex);
    for (auto it : _ask_items) {
        if (it.first >= start_price) {
            if (it.second < size) {
                result.push_back( { it.first, it.second });
                size -= it.second;
            } else {
                result.push_back( { it.first, size });
                break;
            }
        }
    }
    return result;
}

list<MarketItem> Market::GetBidItemsBySize(Double start_price, Double size) {
    list<MarketItem> result;
    locker_t locker(*_bid_mutex);
    for (auto it : _bid_items) {
        if (it.first <= start_price) {
            if (it.second < size) {
                result.push_back( { it.first, it.second });
                size -= it.second;
            } else {
                result.push_back( { it.first, size });
                break;
            }
        }
    }
    return result;
}

list<MarketItem> Market::GetAskItemsByPrice(Double start_price, Double stop_price) {
    list<MarketItem> result;
    locker_t locker(*_ask_mutex);
    for (auto it : _ask_items) {
        if (it.first >= start_price) {
            if (it.first <= stop_price) {
                result.push_back( { it.first, it.second });
            } else {
                break;
            }
        }
    }
    return result;
}

list<MarketItem> Market::GetBidItemsByPrice(Double start_price, Double stop_price) {
    list<MarketItem> result;
    locker_t locker(*_bid_mutex);
    for (auto it : _bid_items) {
        if (it.first <= start_price) {
            if (it.first >= stop_price) {
                result.push_back( { it.first, it.second });
            } else {
                break;
            }
        }
    }
    return result;
}

list<MarketItem> Market::GetAskItems() {
    list<MarketItem> result;
    locker_t locker(*_ask_mutex);
    for (auto it : _ask_items) {
        result.push_back( { it.first, it.second });
    }
    return result;
}

list<MarketItem> Market::GetBidItems() {
    list<MarketItem> result;
    locker_t locker(*_bid_mutex);
    for (auto it : _bid_items) {
        result.push_back( { it.first, it.second });
    }
    return result;
}
/*
BestPrice Market::GetBestPrise() {
    BestPrice result;

    {
        locker_t locker(*_ask_mutex);
        auto it = _ask_items.begin();
        if (it != _ask_items.end()) {
            result.ask = it->first;
        } else {
            result.ask = _symbol_info->max_price();
        }
    }

    {
        locker_t locker(*_bid_mutex);
        auto it = _bid_items.begin();
        if (it != _bid_items.end()) {
            result.bid = it->first;
        } else {
            result.bid = _symbol_info->min_price();
        }
    }

    return result;
}
*/

bool Market::CheckSymbolName(const string& symbol_name) {
    if (_symbol_info->name() == symbol_name) {
        return true;
    } else {
        return false;
    }
}
