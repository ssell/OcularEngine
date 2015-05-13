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

// FNV-1A Algorithm 'Copyright'

/**
 * Please do not copyright this code.  This code is in the public domain.
 *
 * LANDON CURT NOLL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
 * EVENT SHALL LANDON CURT NOLL BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * By:
 *  chongo <Landon Curt Noll> /\oo/\
 *      http://www.isthe.com/chongo/
 *
 * Share and Enjoy! :-)
 */

#include "Utilities/HashGenerator.hpp"

static const uint32_t FNV_PRIME_32 = static_cast<uint32_t>(0x01000193);
static const uint64_t FNV_PRIME_64 = static_cast<uint64_t>(0x100000001b3ULL);

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Utils
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        HashGenerator::HashGenerator()
        {
            m_LastHash32 = 0;
            m_LastHash64 = 0;
        }

        HashGenerator::~HashGenerator()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        uint32_t HashGenerator::getHash32(std::string const& str)
        {
            uint32_t result = m_LastHash32;

            const char* buffer = str.c_str();
            uint8_t* s = (uint8_t*)buffer;

            //----------------------------------------
            // FNV-1a hash each octet of the string

            while(*s)
            {
                result ^= static_cast<uint32_t>(*s++);
                result *= FNV_PRIME_32;
            }

            //----------------------------------------
            // Store and return result

            m_LastHash32 = result;
            return result;
        }

        uint64_t HashGenerator::getHash64(std::string const& str)
        {
            uint64_t result = m_LastHash64;

            const char* buffer = str.c_str();
            uint8_t* s = (uint8_t*)buffer;

            //----------------------------------------
            // FNV-1a hash each octet of the string

            while(*s)
            {
                result ^= static_cast<uint64_t>(*s++);
                result *= FNV_PRIME_64;
            }

            //----------------------------------------
            // Store and return result

            m_LastHash64 = result;
            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}