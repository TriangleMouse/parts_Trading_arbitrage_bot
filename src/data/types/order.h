//
// Created by Артем Белявский on 8/15/21.
//

#ifndef TRADEBOT_ORDER_H
#define TRADEBOT_ORDER_H

#include "market_item.h"
#include "order_type.h"
#include "trade_type.h"

#include <string>
#include <memory>
#include <mutex>

namespace DATA {
    namespace TYPES {

        class Order{
        public:
            Order();
            Order(const Order&);
            Order& operator=(const Order&);
            Order(Order&&) = default;
            Order& operator=(Order&&) = default;
            ~Order() = default;

            int user_id();
            void user_id(const int& user_id);

            std::string opening_id();
            void opening_id(const std::string&);
            std::string closing_id();
            void closing_id(const std::string&);
            Order_Type order_type();
            void order_type(Order_Type);

            Trade_Type export_trade_type();
            void export_trade_type(Trade_Type);


            MarketItem order_price();
            void order_price(MarketItem);
            Double price();
            void price(Double);
            Double markup();
            void markup(Double);
            Double size();
            void size(Double);
            time_t timer_task_kill();
            time_t timer_task_add();
            void timer_task_kill(int death_send_task_timer);//редактирует время ожидания для повторного отправления задачи на уничтожение
            void timer_task_add(int waiting_ticket_event);// редактирует время ожидание эвента

        private:
            int _user_id=0;
            std::string _opening_id;
            std::string _closing_id;
            Order_Type _order_type;
            Trade_Type _export_trade_type;
            MarketItem _order_price;
            unsigned _warning_number;
            unsigned _des_warning_number;
            time_t _creation_time;
            time_t _kill_time;
            time_t _death_send_task_timer;
            time_t _waiting_ticket_event;
            std::shared_ptr<std::mutex> _rw_mutex;

        };

    }  // namespace TYPES
}  // namespace DATA

#endif //TRADEBOT_ORDER_H
