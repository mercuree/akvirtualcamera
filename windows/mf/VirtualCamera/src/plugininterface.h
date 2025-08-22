/* akvirtualcamera, virtual camera for Mac and Windows.
 * Copyright (C) 2025  Gonzalo Exequiel Pedone
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

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <string>
#include <combaseapi.h>

namespace AkVCam
{
    class PluginInterfacePrivate;

    class PluginInterface
    {
        public:
            PluginInterface();
            PluginInterface(const PluginInterface &other) = delete;
            ~PluginInterface();

            void setPluginHinstance(HINSTANCE instance);
            bool createDevice(const std::string &deviceId,
                              const std::string &description);
            void destroyDevice(const std::string &deviceId);
            void destroyDevice(const CLSID &clsid);
            void initializeLogger() const;

        private:
            PluginInterfacePrivate *d;
    };
}

#endif // PLUGININTERFACE_H
