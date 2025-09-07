/* akvirtualcamera, virtual camera for Mac and Windows.
 * Copyright (C) 2020  Gonzalo Exequiel Pedone
 *
 * akvirtualcamera is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * akvirtualcamera is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with akvirtualcamera. If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: http://webcamoid.github.io/
 */

#ifndef AKVCAMUTILS_FRACTION_H
#define AKVCAMUTILS_FRACTION_H

#include <cstdint>
#include <string>

namespace AkVCam
{
    class Fraction;
    class FractionPrivate;
    using FractionRange = std::pair<Fraction, Fraction>;

    class Fraction
    {
        public:
            Fraction();
            Fraction(int64_t num, int64_t den);
            Fraction(const std::string &str);
            Fraction(const Fraction &other);
            virtual ~Fraction();
            Fraction &operator =(const Fraction &other);
            bool operator ==(const Fraction &other) const;
            bool operator <(const Fraction &other) const;
            operator bool() const;

            int64_t num() const;
            int64_t &num();
            int64_t den() const;
            int64_t &den();
            double value() const;
            std::string toString() const;
            bool isValid() const;
            bool isNull() const;
            bool isInfinity() const;
            int sign() const;
            static bool isFraction(const std::string &str);

        private:
            FractionPrivate *d;
    };
}

std::ostream &operator <<(std::ostream &os, const AkVCam::Fraction &fraction);

#endif // AKVCAMUTILS_FRACTION_H
