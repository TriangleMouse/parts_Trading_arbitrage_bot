//
// Created by Артем Белявский on 8/12/21.
//

#ifndef TRADEBOT_LOCKER_H
#define TRADEBOT_LOCKER_H
#include <mutex>
#include <memory>

namespace HELPERS {
    typedef std::unique_lock<std::mutex> locker_t;
}
#endif //TRADEBOT_LOCKER_H
