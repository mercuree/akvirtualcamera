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

#ifndef ENUMPINS_H
#define ENUMPINS_H

#include <strmif.h>

#include "PlatformUtils/src/cunknown.h"

namespace AkVCam
{
    class EnumPinsPrivate;
    class BaseFilter;

    class EnumPins:
            public IEnumPins,
            public CUnknown
    {
        public:
            EnumPins();
            EnumPins(const EnumPins &other);
            virtual ~EnumPins();

            size_t count() const;
            void addPin(IPin *pin, bool changed=true);
            void removePin(IPin *pin, bool changed=true);
            void setBaseFilter(AkVCam::BaseFilter *baseFilter);

            DECLARE_IUNKNOWN(IID_IEnumPins)

            // IEnumPins
            HRESULT STDMETHODCALLTYPE Next(ULONG cPins,
                                           IPin **ppPins,
                                           ULONG *pcFetched) override;
            HRESULT STDMETHODCALLTYPE Skip(ULONG cPins) override;
            HRESULT STDMETHODCALLTYPE Reset() override;
            HRESULT STDMETHODCALLTYPE Clone(IEnumPins **ppEnum) override;

        private:
            EnumPinsPrivate *d;
    };
}

#endif // ENUMPINS_H
