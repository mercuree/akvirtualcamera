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

#include <strmif.h>
#include <amvideo.h>
#include <dvdmedia.h>
#include <uuids.h>

#include "latency.h"
#include "PlatformUtils/src/utils.h"
#include "VCamUtils/src/utils.h"

namespace AkVCam
{
    class LatencyPrivate
    {
        public:
            IAMStreamConfig *m_streamConfig {nullptr};
    };
}

AkVCam::Latency::Latency(IAMStreamConfig *streamConfig):
    CUnknown(this, IID_IAMLatency)
{
    this->d = new LatencyPrivate;
    this->d->m_streamConfig = streamConfig;
}

AkVCam::Latency::~Latency()
{
    delete this->d;
}

HRESULT AkVCam::Latency::GetLatency(REFERENCE_TIME *prtLatency)
{
    AkLogFunction();

    if (!prtLatency)
        return E_POINTER;

    *prtLatency = 0;

    if (this->d->m_streamConfig) {
        AM_MEDIA_TYPE *mediaType = nullptr;

        if (SUCCEEDED(this->d->m_streamConfig->GetFormat(&mediaType))) {
            if (IsEqualGUID(mediaType->formattype, FORMAT_VideoInfo)) {
                auto format = reinterpret_cast<VIDEOINFOHEADER *>(mediaType->pbFormat);
                *prtLatency = format->AvgTimePerFrame;
            } else if (IsEqualGUID(mediaType->formattype, FORMAT_VideoInfo2)) {
                auto format = reinterpret_cast<VIDEOINFOHEADER2 *>(mediaType->pbFormat);
                *prtLatency = format->AvgTimePerFrame;
            }

            deleteMediaType(&mediaType);
        }
    }

    return S_OK;
}
