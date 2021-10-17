//
// Created by Артем Белявский on 8/9/21.
//

#ifndef TRADEBOT_DOUBLE_H
#define TRADEBOT_DOUBLE_H

#include <string>

namespace DATA {
    namespace TYPES {

        class Double {
        public:
            Double();
            ~Double() = default;

            Double(const Double&);
            Double(const double&);
            Double(const Double&&);
            Double(const double&&);

            std::string ToString() const;
            double Get() const;

            Double& operator=(const Double&);
            Double& operator=(const double&);
            Double& operator=(const int&);
            Double& operator=(const Double&&);
            Double& operator=(const double&&);
            Double& operator=(const int&&);

            Double& operator*=(Double);
            Double& operator/=(Double);
            Double& operator+=(Double);
            Double& operator-=(Double);

            bool operator==(Double) const;
            bool operator==(double) const;
            bool operator!=(Double) const;
            bool operator!=(double) const;
            bool operator<=(Double) const;
            bool operator<=(double) const;
            bool operator>=(Double) const;
            bool operator>=(double) const;
            bool operator<(Double) const;
            bool operator<(double) const;
            bool operator>(Double) const;
            bool operator>(double) const;

            Double operator*(Double) const;
            Double operator*(double) const;
            Double operator/(Double) const;
            Double operator/(double) const;
            Double operator+(Double) const;
            Double operator+(double) const;
            Double operator-(Double) const;
            Double operator-(double) const;

            operator double() const;
            operator int() const;
            operator bool() const;

        private:
            double _val;
        };

    } /* namespace TYPES */
} /* namespace DATA */

#endif //TRADEBOT_DOUBLE_H
