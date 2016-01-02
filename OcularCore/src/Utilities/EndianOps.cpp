/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
            void convert(Endianness from, Endianness to, int8_t& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        // Make sure native is known, and that we are not trying to convert to  
                        // native if it is already in native ordering.

                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, int16_t& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, int32_t& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, int64_t& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, uint8_t& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, uint16_t& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, uint32_t& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, uint64_t& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, float& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            void convert(Endianness from, Endianness to, double& value)
            {
                if((from != Endianness::Unknown) && (to != Endianness::Unknown) && (from != to))
                {
                    if((from != Endianness::Native) && (to != Endianness::Native))
                    {
                        convertToReverse(value);
                    }
                    else
                    {
                        Endianness native = Core::SystemInfo::getEndianness();

                        if((native != Endianness::Unknown) && ((from != native) || (to != native)))
                        {
                            convertToReverse(value);
                        }
                    }
                }
            }

            //------------------------------------------------------------------------------
            // CONVERT TO REVERSE
            //------------------------------------------------------------------------------

            void convertToReverse(int8_t& value)
            {
                value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(int16_t& value)
            {
                value = boost::endian::endian_reverse(value);
            }
            void convertToReverse(int32_t& value)
            {
                value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(int64_t& value)
            {
                value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(uint8_t& value)
            {
                value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(uint16_t& value)
            {
                value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(uint32_t& value)
            {
                value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(uint64_t& value)
            {
                value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(float& value)
            {
                //value = boost::endian::endian_reverse(value);
            }

            void convertToReverse(double& value)
            {
                //value = boost::endian::endian_reverse(value);
            }
        }
    }
}