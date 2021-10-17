//
// Created by Артем Белявский on 8/11/21.
//

#ifndef TRADEBOT_NON_COPYABLE_H
#define TRADEBOT_NON_COPYABLE_H

namespace HELPERS {

    class NonCopyable {
    protected:
        NonCopyable() = default;
        virtual ~NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
        NonCopyable(NonCopyable&&) = delete;
        NonCopyable& operator=(NonCopyable&&) = delete;
    };

}  // namespace HELPERS
#endif //TRADEBOT_NON_COPYABLE_H
