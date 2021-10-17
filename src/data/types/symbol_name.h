//
// Created by Артем Белявский on 8/12/21.
//

#ifndef TRADEBOT_SYMBOL_NAME_H
#define TRADEBOT_SYMBOL_NAME_H

#include <string>

namespace DATA {
    namespace TYPES {

        struct SymbolName {
            std::string moscow_name;
            std::string binance_name;
            std::string binance_base_cur;
            std::string binance_quote_cur;
        };

        bool operator==(const SymbolName&, const SymbolName&);
        bool operator==(const SymbolName&, const std::string&);
        bool operator==(const std::string&, const SymbolName&);

    }  // namespace TYPES
}
#endif //TRADEBOT_SYMBOL_NAME_H
