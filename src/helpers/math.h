//
// Created by Артем Белявский on 8/8/21.
//

#include "../data/types/double.h"
#include <string>

#ifndef TRADEBOT_MATH_H
#define TRADEBOT_MATH_H

namespace HELPERS {

    double Round4(double);
    double Round8(double);
    double Round(double, int);
    double Floor(double, int);

    std::string DoubleToString(double);

    DATA::TYPES::Double fRand(const DATA::TYPES::Double& fMin, const DATA::TYPES::Double& fMax);
    time_t tRand(time_t tMin, time_t tMax);

    std::string convertToString(const double &x, const int &precision=8);

    char *settime(tm *u);
}  // namespace HELPERS


#endif //TRADEBOT_MATH_H
