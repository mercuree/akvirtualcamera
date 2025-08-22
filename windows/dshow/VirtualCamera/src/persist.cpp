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

#include "persist.h"
#include "PlatformUtils/src/utils.h"
#include "VCamUtils/src/utils.h"

namespace AkVCam
{
    class PersistPrivate
    {
        public:
            CLSID m_clsid;
    };
}

AkVCam::Persist::Persist(const IID &classCLSID):
    CUnknown(this, IID_IPersist)
{
    this->d = new PersistPrivate;
    this->d->m_clsid = classCLSID;
}

AkVCam::Persist::~Persist()
{
    delete this->d;
}

HRESULT AkVCam::Persist::GetClassID(CLSID *pClassID)
{
    AkLogFunction();

    if (!pClassID)
        return E_POINTER;

    *pClassID = this->d->m_clsid;

    return S_OK;
}
