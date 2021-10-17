//
// Created by Артем Белявский on 8/12/21.
//

#ifndef TRADEBOT_MY_THREAD_H
#define TRADEBOT_MY_THREAD_H
#include "../helpers/non_copyable.h"

#include <memory>

namespace THREADS {

    class MyThread: public HELPERS::NonCopyable {
    public:
        virtual ~MyThread() = default;

        virtual bool Run() = 0;
        virtual void Terminate() = 0;
        virtual void Check() = 0;

    protected:
        MyThread() = default;
    };

}
#endif //TRADEBOT_MY_THREAD_H
