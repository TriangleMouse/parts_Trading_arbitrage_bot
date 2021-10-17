//
// Created by Артем Белявский on 8/12/21.
//

#include "symbol_name.h"

using namespace DATA;
using namespace TYPES;
using namespace std;

bool DATA::TYPES::operator==(const SymbolName& left_obj, const SymbolName& right_obj) {
    if (left_obj.binance_name == right_obj.binance_name && left_obj.moscow_name == right_obj.moscow_name) {
        return true;
    } else {
        return false;
    }
}

bool DATA::TYPES::operator==(const SymbolName& left_obj, const string& right_obj) {
    if (left_obj.binance_name == right_obj || left_obj.moscow_name == right_obj) {
        return true;
    } else {
        return false;
    }
}

bool DATA::TYPES::operator==(const string& left_obj, const SymbolName& right_obj) {
    if (right_obj.binance_name == left_obj || right_obj.moscow_name == left_obj) {
        return true;
    } else {
        return false;
    }
}
