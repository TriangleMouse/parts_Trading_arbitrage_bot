//
// Created by Артем Белявский on 8/12/21.
//

#ifndef TRADEBOT_ORDERBOOK_THREAD_H
#define TRADEBOT_ORDERBOOK_THREAD_H

#include "my_thread.h"

#include <memory>
#include <thread>

namespace THREADS {

    class OrderBook_Thread: public MyThread {
    public:
        static std::shared_ptr<MyThread> GetThread();
        virtual ~OrderBook_Thread();

        virtual bool Run();
        virtual void Terminate();
        virtual void Check();

    private:
        OrderBook_Thread();
        std::unique_ptr<std::thread> _binance_thread;
        bool _is_runing;
    };

}
#endif //TRADEBOT_ORDERBOOK_THREAD_H
