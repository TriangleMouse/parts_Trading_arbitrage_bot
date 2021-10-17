//
// Created by Артем Белявский on 8/14/21.
//

#ifndef TRADEBOT_DATA_BOX_H
#define TRADEBOT_DATA_BOX_H

#include "stock_market.h"
#include "stock_market_info.h"

#include "local_config.h"
//#include <data/capacitor.h>
//#include "export_task_queue.h"
#include "log_creator_msg_queue.h"
//#include <data/msg_queue.h>

#include <memory>

namespace DATA {

    struct DataBox {
        std::unique_ptr<StockMarketInfo> market_info;

        std::unique_ptr<StockMarket> binance_market;
        std::unique_ptr<StockMarket> moscow_market;
    //    std::unique_ptr<ExportTask_Queue> binance_task;
        //std::unique_ptr<Capacitor> market_capasitor;
        std::unique_ptr<LocalConfig> market_config;
        std::unique_ptr<LogCreator_Queue> log_box;
        std::unique_ptr<time_t> time;
    };

    extern DataBox* g_data_box;

}

#endif //TRADEBOT_DATA_BOX_H
