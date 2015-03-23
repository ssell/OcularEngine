/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Utilities/Endianness.hpp"
#include "SystemInfo.hpp"

#include <boost/endian/conversion.hpp>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Utils
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Endianness::Endianness()
        {
        
        }

        Endianness::~Endianness()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Endianness::convertBigToNative(char& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertBigToNative(short& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }
        void Endianness::convertBigToNative(long& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertBigToNative(long long& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertBigToNative(unsigned char& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertBigToNative(unsigned short& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertBigToNative(unsigned long& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertBigToNative(unsigned long long& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertBigToNative(float& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertBigToNative(double& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
            {
                convertToReverse(value);
            }
        }

        //----------------------------------------------------------------------------------

        void Endianness::convertLittleToNative(char& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(short& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(long& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(long long& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(unsigned char& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(unsigned short& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(unsigned long& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(unsigned long long& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(float& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        void Endianness::convertLittleToNative(double& value)
        {
            if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
            {
                convertToReverse(value);
            }
        }

        //----------------------------------------------------------------------------------

        void Endianness::convertToReverse(char& value)
        {
            value = boost::endian::endian_reverse(static_cast<int8_t>(value));
        }

        void Endianness::convertToReverse(short& value)
        {
            value = boost::endian::endian_reverse(static_cast<int16_t>(value));
        }
        void Endianness::convertToReverse(long& value)
        {
            value = boost::endian::endian_reverse(static_cast<int32_t>(value));
        }

        void Endianness::convertToReverse(long long& value)
        {
            value = boost::endian::endian_reverse(static_cast<int64_t>(value));
        }

        void Endianness::convertToReverse(unsigned char& value)
        {
            value = boost::endian::endian_reverse(static_cast<uint8_t>(value));
        }

        void Endianness::convertToReverse(unsigned short& value)
        {
            value = boost::endian::endian_reverse(static_cast<uint16_t>(value));
        }

        void Endianness::convertToReverse(unsigned long& value)
        {
            value = boost::endian::endian_reverse(static_cast<uint32_t>(value));
        }

        void Endianness::convertToReverse(unsigned long long& value)
        {
            value = boost::endian::endian_reverse(static_cast<uint64_t>(value));
        }

        void Endianness::convertToReverse(float& value)
        {
            value = boost::endian::endian_reverse(value);
        }

        void Endianness::convertToReverse(double& value)
        {
            value = boost::endian::endian_reverse(value);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

//------------------------------------------------------------------------------------------