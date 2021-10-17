//
// Created by Артем Белявский on 8/9/21.
//

#include "double.h"
#include "../../helpers/math.h"

#include <cmath>
#include <cstdio>

using namespace DATA;
using namespace TYPES;
using namespace HELPERS;
using namespace std;

Double::Double() :
        _val(NAN) {
}

Double::Double(const Double& val) {
    _val = val._val;
}

Double::Double(const double& val) {
    _val = Round(val, 12);
}

Double::Double(const Double&& val) {
    _val = val._val;
}

Double::Double(const double&& val) {
    _val = Round(val, 12);
}

double Double::Get() const {
    return _val;
}

Double& Double::operator=(const Double& val) {
    if (this != &val)
        _val = val._val;
    return *this;
}

Double& Double::operator=(const double& val) {
    _val = Round(val, 12);
    return *this;
}

Double& Double::operator=(const int& val) {
    _val = Round(static_cast<double>(val), 12);
    return *this;
}

Double& Double::operator=(const Double&& val) {
    if (this != &val)
        _val = val._val;
    return *this;
}

Double& Double::operator=(const double&& val) {
    _val = Round(val, 12);
    return *this;
}

Double& Double::operator=(const int&& val) {
    _val = Round(static_cast<double>(val), 12);
    return *this;
}

Double& Double::operator*=(Double val) {
    _val *= val._val;
    _val = Round(_val, 12);
    return *this;
}

Double& Double::operator/=(Double val) {
    _val /= val._val;
    _val = Round(_val, 12);
    return *this;
}

Double& Double::operator+=(Double val) {
    _val += val._val;
    _val = Round(_val, 12);
    return *this;
}

Double& Double::operator-=(Double val) {
    _val -= val._val;
    _val = Round(_val, 12);
    return *this;
}

bool Double::operator==(Double r_val) const {
    return _val == r_val._val;
}

bool Double::operator==(double r_val) const {
    return _val == r_val;
}

bool Double::operator!=(Double r_val) const {
    return _val != r_val._val;
}

bool Double::operator!=(double r_val) const {
    return _val != r_val;
}

bool Double::operator<=(Double r_val) const {
    return _val <= r_val._val;
}

bool Double::operator<=(double r_val) const {
    return _val <= r_val;
}

bool Double::operator>=(Double r_val) const {
    return _val >= r_val._val;
}

bool Double::operator>=(double r_val) const {
    return _val >= r_val;
}

bool Double::operator<(Double r_val) const {
    return _val < r_val._val;
}

bool Double::operator<(double r_val) const {
    return _val < r_val;
}

bool Double::operator>(Double r_val) const {
    return _val > r_val._val;
}

bool Double::operator>(double r_val) const {
    return _val > r_val;
}

Double Double::operator*(Double r_val) const {
    return Double(_val * r_val._val);
}

Double Double::operator*(double r_val) const {
    return Double(_val * r_val);
}

Double Double::operator/(Double r_val) const {
    return Double(_val / r_val._val);
}

Double Double::operator/(double r_val) const {
    return Double(_val / r_val);
}

Double Double::operator+(Double r_val) const {
    return Double(_val + r_val._val);
}

Double Double::operator+(double r_val) const {
    return Double(_val + r_val);
}

Double Double::operator-(Double r_val) const {
    return Double(_val - r_val._val);
}

Double Double::operator-(double r_val) const {
    return Double(_val - r_val);
}

Double::operator double() const {
    return _val;
}

Double::operator int() const {
    return static_cast<int>(_val);
}

Double::operator bool() const {
    return !isnan(_val);
}

string Double::ToString() const {
    char buf[25];
    sprintf(buf, "%.12f", _val);
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