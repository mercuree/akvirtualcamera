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

#ifndef AKVCAMUTILS_ALGORITHM_H
#define AKVCAMUTILS_ALGORITHM_H

#include <cctype>

namespace AkVCam
{
    namespace Algorithm
    {
        template<typename T>
        inline T alignUp(const T &value, const T &align)
        {
            return (value + align - 1) & ~(align - 1);
        }

        inline size_t multBytesRequired(size_t nbits)
        {
            if (nbits <= 4)
                return 1;
            else if (nbits <= 8)
                return 2;
            else if (nbits <= 16)
                return 4;
            else if (nbits <= 32)
                return 8;

            return 0;
        }

        // Endianness conversion functions for color

        inline uint8_t swapBytes(uint8_t value)
        {
            return value;
        }

        inline uint16_t swapBytes(uint16_t value)
        {
            return ((value & 0xff00) >> 8)
                 | ((value & 0x00ff) << 8);
        }

        inline uint32_t swapBytes(uint32_t value)
        {
            return ((value & 0xff000000) >> 24)
                 | ((value & 0x00ff0000) >>  8)
                 | ((value & 0x0000ff00) <<  8)
                 | ((value & 0x000000ff) << 24);
        }

        inline uint64_t swapBytes(uint64_t value)
        {
            return ((value & 0xff00000000000000) >> 56)
                 | ((value & 0x00ff000000000000) >> 40)
                 | ((value & 0x0000ff0000000000) >> 24)
                 | ((value & 0x000000ff00000000) >>  8)
                 | ((value & 0x00000000ff000000) <<  8)
                 | ((value & 0x0000000000ff0000) << 24)
                 | ((value & 0x000000000000ff00) << 40)
                 | ((value & 0x00000000000000ff) << 56);
        }

        template <typename T>
        inline void swapDataBytes(T *data, size_t sizeInBytes)
        {
            auto n = sizeInBytes / sizeof(T);

            for (size_t i = 0; i < n; ++i) {
                *data = swapBytes(static_cast<T>(*data));
                ++data;
            }
        }
    }
}

#endif // AKVCAMUTILS_ALGORITHM_H
