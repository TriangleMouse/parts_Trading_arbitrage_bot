//
// Created by Артем Белявский on 8/18/21.
//

#ifndef TRADEBOT_CONFIG_THREAD_H
#define TRADEBOT_CONFIG_THREAD_H

#include "my_thread.h"

#include <memory>
#include <thread>

namespace THREADS {

    class ConfigThread: public MyThread  {
    public:
        static std::shared_ptr<MyThread> GetThread();
        virtual ~ConfigThread();

        virtual bool Run();
        virtual void Terminate();
        virtual void Check();

    private:
        ConfigThread();

        std::unique_ptr<std::thread> _thread;
        bool _is_runing;
    };

} /* namespace THREADS */

#endif //TRADEBOT_CONFIG_THREAD_H
