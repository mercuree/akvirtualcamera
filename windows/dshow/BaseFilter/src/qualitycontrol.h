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

#ifndef QUALITYCONTROL_H
#define QUALITYCONTROL_H

#include <strmif.h>

#include "PlatformUtils/src/cunknown.h"

namespace AkVCam
{
    class QualityControl:
            public IQualityControl,
            public CUnknown
    {
        public:
            QualityControl();
            virtual ~QualityControl();

            DECLARE_IUNKNOWN(IID_IQualityControl)

            // ISpecifyPropertyPages
            HRESULT STDMETHODCALLTYPE Notify(IBaseFilter *pSelf, Quality q) override;
            HRESULT STDMETHODCALLTYPE SetSink(IQualityControl *piqc) override;
    };
}

#endif // QUALITYCONTROL_H
