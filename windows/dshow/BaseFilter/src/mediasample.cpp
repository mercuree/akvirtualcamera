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

#include <dshow.h>

#include "mediasample.h"
#include "PlatformUtils/src/utils.h"
#include "VCamUtils/src/utils.h"

namespace AkVCam
{
    class MediaSamplePrivate
    {
        public:
            IMemAllocator *m_memAllocator {nullptr};
            BYTE *m_buffer {nullptr};
            LONG m_bufferSize {0};
            LONG m_dataLength {0};
            LONG m_prefix {0};
            AM_MEDIA_TYPE *m_mediaType {nullptr};
            REFERENCE_TIME m_sampleTimeStart {-1};
            REFERENCE_TIME m_sampleTimeEnd {-1};
            REFERENCE_TIME m_mediaTimeStart {-1};
            REFERENCE_TIME m_mediaTimeEnd {-1};
            BOOL m_syncPoint {S_FALSE};
            BOOL m_preroll {S_FALSE};
            BOOL m_discontinuity {S_FALSE};
            BOOL m_mediaTypeChanged {S_FALSE};
    };
}

AkVCam::MediaSample::MediaSample(IMemAllocator *memAllocator,
                                 LONG bufferSize,
                                 LONG align,
                                 LONG prefix):
    CUnknown(this, IID_IMediaSample)
{
    this->d = new MediaSamplePrivate;
    this->d->m_memAllocator = memAllocator;
    this->d->m_bufferSize = bufferSize;
    this->d->m_dataLength = bufferSize;
    this->d->m_prefix = prefix;
    auto realSize = size_t(bufferSize + prefix + align - 1) & ~size_t(align - 1);
    this->d->m_buffer = new BYTE[realSize];
    memset(this->d->m_buffer, 0, realSize * sizeof(BYTE));
}

AkVCam::MediaSample::~MediaSample()
{
    delete [] this->d->m_buffer;
    deleteMediaType(&this->d->m_mediaType);
    delete this->d;
}

ULONG AkVCam::MediaSample::Release()
{
    auto result = CUnknown::Release();
    this->d->m_memAllocator->ReleaseBuffer(this);

    if (!result)
        delete this;

    return result;
}

HRESULT AkVCam::MediaSample::GetPointer(BYTE **ppBuffer)
{
    AkLogFunction();

    if (!ppBuffer)
        return E_POINTER;

    *ppBuffer = this->d->m_buffer + this->d->m_prefix;

    return S_OK;
}

LONG AkVCam::MediaSample::GetSize()
{
    AkLogFunction();

    return this->d->m_bufferSize;
}

HRESULT AkVCam::MediaSample::GetTime(REFERENCE_TIME *pTimeStart,
                                     REFERENCE_TIME *pTimeEnd)
{
    AkLogFunction();

    if (!pTimeStart || !pTimeEnd)
        return E_POINTER;

    *pTimeStart = this->d->m_sampleTimeStart;
    *pTimeEnd = this->d->m_sampleTimeEnd;

    if (*pTimeStart < 0)
        return VFW_E_SAMPLE_TIME_NOT_SET;

    if (*pTimeEnd < 0) {
        *pTimeEnd = *pTimeStart + 1;

        return VFW_S_NO_STOP_TIME;
    }

    return S_OK;
}

HRESULT AkVCam::MediaSample::SetTime(REFERENCE_TIME *pTimeStart,
                                     REFERENCE_TIME *pTimeEnd)
{
    AkLogFunction();

    this->d->m_sampleTimeStart = pTimeStart? *pTimeStart: -1;
    this->d->m_sampleTimeEnd = pTimeEnd? *pTimeEnd: -1;

    return S_OK;
}

HRESULT AkVCam::MediaSample::IsSyncPoint()
{
    AkLogFunction();

    return this->d->m_syncPoint? S_OK: S_FALSE;
}

HRESULT AkVCam::MediaSample::SetSyncPoint(BOOL bIsSyncPoint)
{
    AkLogFunction();
    this->d->m_syncPoint = bIsSyncPoint;

    return S_OK;
}

HRESULT AkVCam::MediaSample::IsPreroll()
{
    AkLogFunction();

    return this->d->m_preroll? S_OK: S_FALSE;
}

HRESULT AkVCam::MediaSample::SetPreroll(BOOL bIsPreroll)
{
    AkLogFunction();
    this->d->m_preroll = bIsPreroll;

    return S_OK;
}

LONG AkVCam::MediaSample::GetActualDataLength()
{
    AkLogFunction();

    return this->d->m_dataLength;
}

HRESULT AkVCam::MediaSample::SetActualDataLength(LONG lLen)
{
    AkLogFunction();

    if (lLen < 0 || lLen > this->d->m_bufferSize)
        return VFW_E_BUFFER_OVERFLOW;

    this->d->m_dataLength = lLen;

    return S_OK;
}

HRESULT AkVCam::MediaSample::GetMediaType(AM_MEDIA_TYPE **ppMediaType)
{
    AkLogFunction();

    if (!ppMediaType)
        return E_POINTER;

    *ppMediaType = nullptr;

    if (this->d->m_mediaTypeChanged == S_FALSE)
        return S_FALSE;

    *ppMediaType = createMediaType(this->d->m_mediaType);

    if (!*ppMediaType)
        return E_OUTOFMEMORY;

    return S_OK;
}

HRESULT AkVCam::MediaSample::SetMediaType(AM_MEDIA_TYPE *pMediaType)
{
    AkLogFunction();

    if (!pMediaType)
        return E_POINTER;

    if (isEqualMediaType(pMediaType, this->d->m_mediaType, true)) {
        this->d->m_mediaTypeChanged = S_FALSE;

        return S_OK;
    }

    deleteMediaType(&this->d->m_mediaType);
    this->d->m_mediaType = createMediaType(pMediaType);
    this->d->m_mediaTypeChanged = S_OK;

    return S_OK;
}

HRESULT AkVCam::MediaSample::IsDiscontinuity()
{
    AkLogFunction();

    return this->d->m_discontinuity? S_OK: S_FALSE;
}

HRESULT AkVCam::MediaSample::SetDiscontinuity(BOOL bDiscontinuity)
{
    AkLogFunction();
    this->d->m_discontinuity = bDiscontinuity;

    return S_OK;
}

HRESULT AkVCam::MediaSample::GetMediaTime(LONGLONG *pTimeStart,
                                          LONGLONG *pTimeEnd)
{
    AkLogFunction();

    if (!pTimeStart || !pTimeEnd)
        return E_POINTER;

    *pTimeStart = this->d->m_mediaTimeStart;
    *pTimeEnd = this->d->m_mediaTimeEnd;

    if (*pTimeStart < 0 || *pTimeEnd < 0)
        return VFW_E_MEDIA_TIME_NOT_SET;

    return S_OK;
}

HRESULT AkVCam::MediaSample::SetMediaTime(LONGLONG *pTimeStart,
                                          LONGLONG *pTimeEnd)
{
    AkLogFunction();

    this->d->m_mediaTimeStart = pTimeStart? *pTimeStart: -1;
    this->d->m_mediaTimeEnd = pTimeEnd? *pTimeEnd: -1;

    return S_OK;
}
