//
// Created by Артем Белявский on 8/14/21.
//

#include "log_creator_msg_queue.h"
#include "types/log_type.h"
#include "../helpers/locker.h"
#include "../helpers/math.h"
#include <ctime>

using namespace DATA;
using namespace TYPES;
using namespace HELPERS;
using namespace std;

LogCreator_Queue::LogCreator_Queue() :
        _queue_mutex(new mutex), _trade_report_patern(
        "{\"method\":\"trade_bot_log\",\"data\":{\"order_id\":\"") {
}

LogCreator_Queue::~LogCreator_Queue() {
}

void LogCreator_Queue::Push(shared_ptr<string> msg) {
    locker_t locker(*_queue_mutex);
    _queue.push(msg);
}

void LogCreator_Queue::Push(std::shared_ptr<std::string> msg, TYPES::Log_Type type) {
    if (type == Log_Type::SITE_DEBUG) {
        return;
    }
    auto doc = make_shared<string>();
    doc->append(string("{\"msg_type\":\"") + LogTypeToString(type) + "\",");
    doc->append(string("\"msg\":") + *msg + "}");
    locker_t locker(*_queue_mutex);
    _queue.push(doc);
}



std::shared_ptr<string> LogCreator_Queue::Front() {
    shared_ptr<string> result;
    locker_t locker(*_queue_mutex);
    if (_queue.size() > 0) {
        result = _queue.front();
        _queue.pop();
    }
    return result;
}

unsigned LogCreator_Queue::Size() {
    locker_t locker(*_queue_mutex);
    return _queue.size();
}
