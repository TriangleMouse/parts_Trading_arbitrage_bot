//
// Created by Артем Белявский on 8/15/21.
//

#ifndef TRADEBOT_LOCAL_CONFIG_H
#define TRADEBOT_LOCAL_CONFIG_H


#include "types/double.h"
#include <list>
#include <string>

namespace DATA {

    struct LocalConfig{
        std::string aserco_key;
        std::string moscow_key;
        std::string binance_key;
        std::string binance_secret;
        int aserco_bot_user_id= -1;
        std::string aserco_host;
        std::string moscow_host;
        std::string binance_host;
        int first_kill_time = 21600;
        int last_kill_time = 43200;
        int time_upd_orderbook = 10;
        int time_upd_balance= 5;
        int death_task_timer = 15;
        int waiting_ticket_event = 15;
        int time_check_arbitrage = 5;

        double starting_volume=1;
        double disregarded_offer_vol=1;
        double to_hedge_vol=1;
        bool binance_enable = false;
        bool moscow_enable = false;
        std::list<int> _id_bots;
    };

}  // namespace DATA


#endif //TRADEBOT_LOCAL_CONFIG_H
