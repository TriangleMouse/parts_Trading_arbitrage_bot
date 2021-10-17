//
// Created by Артем Белявский on 8/14/21.
//

#ifndef TRADEBOT_LOG_CREATOR_MSG_QUEUE_H
#define TRADEBOT_LOG_CREATOR_MSG_QUEUE_H

#include "../helpers/non_copyable.h"
//#include <data/types/trade_report.h>
#include "types/log_type.h"

#include <string>
#include <queue>
#include <memory>
#include <mutex>

namespace DATA {

    class LogCreator_Queue: public HELPERS::NonCopyable {
    public:
        LogCreator_Queue();
        ~LogCreator_Queue();
        void Push(std::shared_ptr<std::string>);
        void Push(std::shared_ptr<std::string>, TYPES::Log_Type);
        //void Push(std::shared_ptr<DATA::TYPES::TradeReport>);
        std::shared_ptr<std::string> Front(); // Pop
        unsigned Size();

    private:
        std::queue<std::shared_ptr<std::string>> _queue;
        std::unique_ptr<std::mutex> _queue_mutex;
        std::string _trade_report_patern;
    };

}
#endif //TRADEBOT_LOG_CREATOR_MSG_QUEUE_H
