//
// Created by Артем Белявский on 8/12/21.
//

#include "symbol_status.h"
#include "../../helpers/locker.h"

using namespace DATA;
using namespace TYPES;
using namespace HELPERS;
using namespace std;

SymbolStatus::SymbolStatus() :
        _rw_mutex(new mutex) {
}

SymbolName SymbolStatus::name() const {
    locker_t locker(*_rw_mutex);
    return _name;
}

void SymbolStatus::name(SymbolName name) {
    locker_t locker(*_rw_mutex);
    _name = name;
}

SymbolSubStatus SymbolStatus::sub_status() const {
    locker_t locker(*_rw_mutex);
    return _sub_status;
}

void SymbolStatus::sub_status(SymbolSubStatus sub_status) {
    locker_t locker(*_rw_mutex);
    _sub_status = sub_status;
}



bool SymbolStatus::binance_sub_status() const {
    locker_t locker(*_rw_mutex);
    return _sub_status.binance_sub;
}

void SymbolStatus::binance_sub_status(bool binance_sub_status) {
    locker_t locker(*_rw_mutex);
    _sub_status.binance_sub = binance_sub_status;
}

bool SymbolStatus::moscow_sub_status() const {
    locker_t locker(*_rw_mutex);
    return _sub_status.moscow_sub;
}

void SymbolStatus::moscow_sub_status(bool moscow_sub_status) {
    locker_t locker(*_rw_mutex);
    _sub_status.moscow_sub = moscow_sub_status;
}

