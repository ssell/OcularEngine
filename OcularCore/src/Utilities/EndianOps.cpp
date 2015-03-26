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

#include "Utilities/EndianOps.hpp"
#include "SystemInfo.hpp"

#include <boost/endian/conversion.hpp>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Utils
    {
        namespace EndianOps
        {
            void convertBigToNative(char& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertBigToNative(short& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }
            void convertBigToNative(long& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertBigToNative(long long& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertBigToNative(unsigned char& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertBigToNative(unsigned short& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertBigToNative(unsigned long& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertBigToNative(unsigned long long& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertBigToNative(float& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertBigToNative(double& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::LittleEndian)
                {
                    convertToReverse(value);
                }
            }

            //------------------------------------------------------------------------------

            void convertLittleToNative(char& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(short& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(long& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(long long& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(unsigned char& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(unsigned short& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(unsigned long& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(unsigned long long& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(float& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            void convertLittleToNative(double& value)
            {
                if(Core::SystemInfo::getEndianness() == Core::Endianness::BigEndian)
                {
                    convertToReverse(value);
                }
            }

            //------------------------------------------------------------------------------

            void convertToReverse(char& value)
            {
                value = boost::endian::endian_reverse(static_cast<int8_t>(value));
            }

            void convertToReverse(short& value)
            {
                value = boost::endian::endian_reverse(static_cast<int16_t>(value));
            }
            void convertToReverse(long& value)
            {
                value = boost::endian::endian_reverse(static_cast<int32_t>(value));
            }

            void convertToReverse(long long& value)
            {
                value = boost::endian::endian_reverse(static_cast<int64_t>(value));
            }

            void convertToReverse(unsigned char& value)
            {
                value = boost::endian::endian_reverse(static_cast<uint8_t>(value));
            }

            void convertToReverse(unsigned short& value)
            {
                value = boost::endian::endian_reverse(static_cast<uint16_t>(value));
            }

            void convertToReverse(unsigned long& value)
            {
                value = boost::endian::endian_reverse(static_cast<uint32_t>(value));
            }

            void convertToReverse(unsigned long long& value)
            {
                value = boost::endian::endian_reverse(static_cast<uint64_t>(value));
            }

            void convertToReverse(float& value)
            {
                value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(double& value)
            {
                value = boost::endian::endian_reverse(value);
            }
        }
    }
}

//------------------------------------------------------------------------------------------