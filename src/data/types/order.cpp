//
// Created by Артем Белявский on 8/15/21.
//

#include "order.h"
#include "../../helpers/locker.h"
#include "../../helpers/math.h"
#include "../data_box.h"
#include <limits>

using namespace DATA;
using namespace TYPES;
using namespace HELPERS;
using namespace std;

Order::Order() :
        _order_type(Order_Type::UNDEFINED), _export_trade_type(
        Trade_Type::UNDEFINED), _warning_number(0), _des_warning_number(0), _creation_time(
        *g_data_box->time), _kill_time(
        tRand(*g_data_box->time + g_data_box->market_config->first_kill_time,
              *g_data_box->time + g_data_box->market_config->last_kill_time)),_death_send_task_timer(0),_waiting_ticket_event(0), _rw_mutex(
        new mutex) {
}

Order::Order(const Order& obj) :
        _user_id(obj._user_id),_opening_id(obj._opening_id), _closing_id(obj._closing_id), _order_type(obj._order_type), _export_trade_type(obj._export_trade_type), _order_price(
        obj._order_price), _warning_number(obj._warning_number), _des_warning_number(
        obj._des_warning_number), _creation_time(obj._creation_time), _kill_time(
        obj._kill_time),_death_send_task_timer(obj._death_send_task_timer) ,_rw_mutex(new mutex) {
}

Order& Order::operator=(const Order& obj) {
    if (this != &obj) {
        _user_id = obj._user_id;
        _opening_id = obj._opening_id;
        _closing_id = obj._closing_id;
        _order_type = obj._order_type;
        _export_trade_type = obj._export_trade_type;
        _order_price = obj._order_price;
        _warning_number = obj._warning_number;
        _des_warning_number = obj._des_warning_number;
        _creation_time = obj._creation_time;
        _kill_time = obj._kill_time;
        _death_send_task_timer=obj._death_send_task_timer;
        _waiting_ticket_event=obj._waiting_ticket_event;
    }
    return *this;
}

int Order::user_id() {
    locker_t locker(*_rw_mutex);
    return _user_id;
}

void Order::user_id(const int& user_id) {
    locker_t locker(*_rw_mutex);
    _user_id = user_id;
}

string Order::opening_id() {
    locker_t locker(*_rw_mutex);
    return _opening_id;
}

void Order::opening_id(const string& opening_id) {
    locker_t locker(*_rw_mutex);
    _opening_id = opening_id;
}

string Order::closing_id() {
    locker_t locker(*_rw_mutex);
    return _closing_id;
}

void Order::closing_id(const string& closing_id) {
    locker_t locker(*_rw_mutex);
    _closing_id = closing_id;
}

Order_Type Order::order_type() {
    locker_t locker(*_rw_mutex);
    return _order_type;
}

void Order::order_type(Order_Type order_type) {
    locker_t locker(*_rw_mutex);
    _order_type = order_type;
}


Trade_Type Order::export_trade_type() {
    locker_t locker(*_rw_mutex);
    return _export_trade_type;
}

void Order::export_trade_type(Trade_Type trade_type) {
    locker_t locker(*_rw_mutex);
    _export_trade_type = trade_type;
}

MarketItem Order::order_price() {
    locker_t locker(*_rw_mutex);
    return _order_price;
}

void Order::order_price(MarketItem order_price) {
    locker_t locker(*_rw_mutex);
    _order_price = order_price;
}

Double Order::price() {
    locker_t locker(*_rw_mutex);
    return _order_price.price;
}

void Order::price(Double price) {
    locker_t locker(*_rw_mutex);
    _order_price.price = price;
}

Double Order::markup() {
    locker_t locker(*_rw_mutex);
    return _order_price.markup;
}

void Order::markup(Double markup) {
    locker_t locker(*_rw_mutex);
    _order_price.markup = markup;
}


Double Order::size() {
    locker_t locker(*_rw_mutex);
    return _order_price.size;
}

void Order::size(Double size) {
    locker_t locker(*_rw_mutex);
    _order_price.size = size;
}

time_t Order::timer_task_kill(){
    locker_t locker(*_rw_mutex);
    return _death_send_task_timer;
}

void Order::timer_task_kill(int death_send_task_timer) {
    locker_t locker(*_rw_mutex);
    _death_send_task_timer=death_send_task_timer;
}

time_t Order::timer_task_add(){
    locker_t locker(*_rw_mutex);
    return _waiting_ticket_event;
}





/*

void Order::warning_up() {
    locker_t locker(*_rw_mutex);
    if (++_warning_number > 2) {
        _order_type = Order_Type::LAST;
    }

}

void Order::warning_zero() {
    locker_t locker(*_rw_mutex);
    _warning_number = 0;
}

void Order::destroy_warning_up() {
    ++_des_warning_number;
}

void Order::destroy_warning_zero() {
    _des_warning_number = 0;
}

bool Order::permission_destroyed() {
    locker_t locker(*_rw_mutex);
    return (_des_warning_number > tRand(1, 5)) ? true : false;
}

time_t Order::creation_time() {
    return _creation_time;
}

void Order::creation_time(time_t creation_time) {
    _creation_time = creation_time;
    _kill_time = tRand(_creation_time + g_data_box->market_config->first_kill_time,
                       _creation_time + g_data_box->market_config->last_kill_time);
}

bool Order::need_kill() {
    return *g_data_box->time > _kill_time;
}
*/







void Order::timer_task_add(int waiting_ticket_event) {
    locker_t locker(*_rw_mutex);
    _waiting_ticket_event=waiting_ticket_event;
}

