#include "math.h"
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace HELPERS;
using namespace DATA;
using namespace TYPES;
using namespace std;

double HELPERS::Round4(double val) {
    return round(val * double(1e4)) / double(1e4);
}

double HELPERS::Round8(double val) {
    return round(val * double(1e8)) / double(1e8);
}

double HELPERS::Round(double val, int digit) {
    return round(val * double(pow(10, digit))) / double(pow(10, digit));
}

double HELPERS::Floor(double val, int digit) {
    return floor(val * double(pow(10, digit))) / double(pow(10, digit));
}

string HELPERS::DoubleToString(double val){
    char buf[25];
    sprintf(buf, "%.11f", val);
    auto result = string(buf);

    while (true) {
        if (result.size() == 0) {
            break;
        }
        if (result[result.size() - 1] == '0') {
            result.resize(result.size() - 1);
        } else {
            break;
        }
    }

    if (result.size() > 0 && result[result.size() - 1] == '.') {
        result.resize(result.size() - 1);
    }

    return result;
}


string HELPERS::convertToString(const double & x, const int & precision)
{
    static std::ostringstream ss;
    ss.str("");
    ss << fixed << setprecision(precision) << x;
    return ss.str();
}

Double HELPERS::fRand(const Double& fMin, const Double& fMax) {
    Double f = (double) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

time_t HELPERS::tRand(time_t tMin, time_t tMax){
    auto t = (double)rand() / RAND_MAX;
    return tMin + t * (tMax - tMin);
}


char * HELPERS::settime(struct tm *u)
{
    char s[40];
    char *tmp;
    for (int i = 0; i<40; i++) s[i] = 0;
    int length = strftime(s, 40, "%H:%M:%S", u);
    tmp = (char*)malloc(sizeof(s));
    strcpy(tmp, s);
    return(tmp);
}