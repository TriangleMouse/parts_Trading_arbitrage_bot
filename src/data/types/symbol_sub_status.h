//
// Created by Артем Белявский on 8/12/21.
//

#ifndef TRADEBOT_SYMBOL_SUB_STATUS_H
#define TRADEBOT_SYMBOL_SUB_STATUS_H
namespace DATA {
    namespace TYPES {

        struct SymbolSubStatus {
            bool moscow_sub=false;
            bool binance_sub = false;
        };

    }
}
#endif //TRADEBOT_SYMBOL_SUB_STATUS_H
