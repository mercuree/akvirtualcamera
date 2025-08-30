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

#ifndef MEDIASAMPLE2_H
#define MEDIASAMPLE2_H

#include "mediasample.h"

namespace AkVCam
{
    class MediaSample2Private;

    class MediaSample2:
            public IMediaSample2,
            public MediaSample
    {
        public:
            MediaSample2(IMemAllocator *memAllocator,
                         LONG bufferSize, LONG align, LONG prefix);
            virtual ~MediaSample2();

            DECLARE_IMEDIASAMPLE(IID_IMediaSample2)

            // IMediaSample2
            HRESULT STDMETHODCALLTYPE GetProperties(DWORD cbProperties,
                                                    BYTE *pbProperties) override;
            HRESULT STDMETHODCALLTYPE SetProperties(DWORD cbProperties,
                                                    const BYTE *pbProperties) override;

        private:
            MediaSample2Private *d;
    };
}

#endif // MEDIASAMPLE2_H
