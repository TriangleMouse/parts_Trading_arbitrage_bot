//
// Created by Артем Белявский on 8/12/21.
//

#ifndef TRADEBOT_SYMBOL_STATUS_H
#define TRADEBOT_SYMBOL_STATUS_H

#include "symbol_name.h"
#include "symbol_sub_status.h"
#include "../../helpers/non_copyable.h"

#include <string>
#include <mutex>
#include <memory>
#include <string>

namespace DATA {
    namespace TYPES {

        class SymbolStatus: public HELPERS::NonCopyable {
        public:
            SymbolStatus();
            ~SymbolStatus() = default;

            SymbolName name() const;
            void name(SymbolName);

            SymbolSubStatus sub_status() const;
            void sub_status(SymbolSubStatus);
            bool binance_sub_status() const;
            void binance_sub_status(bool);
            bool moscow_sub_status() const;
            void moscow_sub_status(bool);

        private:
            SymbolName _name;
            SymbolSubStatus _sub_status;
            mutable std::unique_ptr<std::mutex> _rw_mutex;
        };

    }
}

#endif //TRADEBOT_SYMBOL_STATUS_H
