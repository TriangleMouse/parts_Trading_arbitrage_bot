//
// Created by Артем Белявский on 8/14/21.
//

#include "symbol_information.h"
#include "../../helpers/locker.h"

#include <cmath>
#include <limits>

using namespace DATA;
using namespace TYPES;
using namespace HELPERS;
using namespace std;

const double d_min = numeric_limits<double>::min();
const double d_max = numeric_limits<double>::max();

SymbolInfo::SymbolInfo() :
        _market_type(Market_Type::UNDEFINED), _flagship_store(Market_Type::UNDEFINED), _export_min_amount(d_min),
        _ask_limit(0.0), _bid_limit(0.0), _min_price(d_min), _max_price(d_max),_new_order_barrier(0.2),
        _min_rand(0.2), _max_rand(0.4),  _precession(8), _rw_mutex(new mutex) {
}

SymbolName SymbolInfo::name() const {
    locker_t locker(*_rw_mutex);
    return _name;
}

void SymbolInfo::name(SymbolName name) {
    locker_t locker(*_rw_mutex);
    _name = name;
}

Market_Type SymbolInfo::market_type() const {
    locker_t locker(*_rw_mutex);
    return _market_type;
}

void SymbolInfo::market_type(Market_Type market_type) {
    locker_t locker(*_rw_mutex);
    _market_type = market_type;
}

Market_Type SymbolInfo::flagship_store() const {
    locker_t locker(*_rw_mutex);
    return _flagship_store;
}

void SymbolInfo::flagship_store(Market_Type flagship_store) {
    locker_t locker(*_rw_mutex);
    _flagship_store = flagship_store;
}

Double SymbolInfo::min_spread() const {
    locker_t locker(*_rw_mutex);
    return _min_spread;
}

void SymbolInfo::min_spread(Double min_spread) {
    locker_t locker(*_rw_mutex);
    _min_spread = min_spread;
}

Double SymbolInfo::binance_disregarded_bid_vol() const {
    locker_t locker(*_rw_mutex);
    return _binance_disregarded_bid_vol;
}

void SymbolInfo::binance_disregarded_bid_vol(Double binance_disregarded_bid_vol) {
    locker_t locker(*_rw_mutex);
    _binance_disregarded_bid_vol = binance_disregarded_bid_vol;
}
Double SymbolInfo::binance_disregarded_ask_vol() const {
    locker_t locker(*_rw_mutex);
    return _binance_disregarded_ask_vol;
}

void SymbolInfo::binance_disregarded_ask_vol(Double binance_disregarded_ask_vol) {
    locker_t locker(*_rw_mutex);
    _binance_disregarded_ask_vol = binance_disregarded_ask_vol;
}

string SymbolInfo::moscow_name() const {
    locker_t locker(*_rw_mutex);
    return _name.moscow_name;
}

void SymbolInfo::moscow_name(const string& moscow_name) {
    locker_t locker(*_rw_mutex);
    _name.moscow_name = moscow_name;
}

string SymbolInfo::binance_name() const {
    locker_t locker(*_rw_mutex);
    return _name.binance_name;
}

void SymbolInfo::binance_name(const string& binance_name) {
    locker_t locker(*_rw_mutex);
    _name.binance_name = binance_name;
}

string SymbolInfo::binance_base_cur() const {
    locker_t locker(*_rw_mutex);
    return _name.binance_base_cur;
}

void SymbolInfo::binance_base_cur(const string& binance_base_cur) {
    locker_t locker(*_rw_mutex);
    _name.binance_base_cur = binance_base_cur;
}

string SymbolInfo::binance_quote_cur() const {
    locker_t locker(*_rw_mutex);
    return _name.binance_quote_cur;
}

void SymbolInfo::binance_quote_cur(const string& binance_quote_cur) {
    locker_t locker(*_rw_mutex);
    _name.binance_quote_cur = binance_quote_cur;
}

Double SymbolInfo::min_amount() const {
    locker_t locker(*_rw_mutex);
    return _min_amount;
}

void SymbolInfo::min_amount(Double min_trading_valume) {
    locker_t locker(*_rw_mutex);
    _min_amount = min_trading_valume;
}

Double SymbolInfo::export_min_amount() const {
    locker_t locker(*_rw_mutex);
    return _export_min_amount;
}

void SymbolInfo::export_min_amount(Double min_trading_valume) {
    locker_t locker(*_rw_mutex);
    _export_min_amount = min_trading_valume;
}


Double SymbolInfo::ask_limit() const {
    locker_t locker(*_rw_mutex);
    return _ask_limit;
}

void SymbolInfo::ask_limit(Double links_limet) {
    locker_t locker(*_rw_mutex);
    _ask_limit = links_limet;
}

Double SymbolInfo::bid_limit() const {
    locker_t locker(*_rw_mutex);
    return _bid_limit;
}

void SymbolInfo::bid_limit(Double links_limet) {
    locker_t locker(*_rw_mutex);
    _bid_limit = links_limet;
}

Double SymbolInfo::min_price() const {
    locker_t locker(*_rw_mutex);
    return _min_price;
}

void SymbolInfo::min_price(Double min_price) {
    locker_t locker(*_rw_mutex);
    _min_price = min_price;
}

Double SymbolInfo::max_price() const {
    locker_t locker(*_rw_mutex);
    return _max_price;
}

void SymbolInfo::max_price(Double max_price) {
    locker_t locker(*_rw_mutex);
    _max_price = max_price;
}



Double SymbolInfo::binance_min_total() const {
    locker_t locker(*_rw_mutex);
    return _binance_min_total;
}

void SymbolInfo::binance_min_total(Double binance_min_total) {
    locker_t locker(*_rw_mutex);
    _binance_min_total = binance_min_total;
}

Double SymbolInfo::binance_bid_price() const {
    locker_t locker(*_rw_mutex);
    return _binance_bid_price;
}

void SymbolInfo::binance_bid_price(Double binance_bid_price) {
    locker_t locker(*_rw_mutex);
    _binance_bid_price = binance_bid_price;
}

Double SymbolInfo::binance_ask_price() const {
    locker_t locker(*_rw_mutex);
    return _binance_ask_price;
}

void SymbolInfo::binance_ask_price(Double binance_ask_price) {
    locker_t locker(*_rw_mutex);
    _binance_ask_price = binance_ask_price;
}

Double SymbolInfo::new_order_barrier() const {
    locker_t locker(*_rw_mutex);
    return _new_order_barrier;
}

void SymbolInfo::new_order_barrier(Double new_order_barrier) {
    locker_t locker(*_rw_mutex);
    _new_order_barrier = new_order_barrier;
}

Double SymbolInfo::min_rand() const {
    locker_t locker(*_rw_mutex);
    return _min_rand;
}

void SymbolInfo::min_rand(Double min_rand) {
    locker_t locker(*_rw_mutex);
    _min_rand = min_rand;
}

Double SymbolInfo::max_rand() const {
    locker_t locker(*_rw_mutex);
    return _max_rand;
}

void SymbolInfo::max_rand(Double max_rand) {
    locker_t locker(*_rw_mutex);
    _max_rand = max_rand;
}


int SymbolInfo::precession() const {
    locker_t locker(*_rw_mutex);
    return _precession;
}

void SymbolInfo::precession(int precession) {
    locker_t locker(*_rw_mutex);
    _precession = precession;
}

int SymbolInfo::volume_precession() const {
    locker_t locker(*_rw_mutex);
    return _volume_precession;
}

void SymbolInfo::volume_precession(int volume_precession) {
    locker_t locker(*_rw_mutex);
    _volume_precession = volume_precession;
}

