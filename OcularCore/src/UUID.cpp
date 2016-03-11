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

#ifdef _MSC_VER
// Removes the following error:
// c:\program files (x86)\microsoft visual studio 14.0\vc\include\xutility(2811): error C4996: 'std::_Fill_n': Function call with parameters that may be unsafe - 
// this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. 
#pragma warning(push)
#pragma warning(disable:4996)
#endif

#include "UUID.hpp"
#include "Math/MathCommon.hpp"
#include "Utilities/StringRegistrar.hpp"

#include "OcularEngine.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>

//------------------------------------------------------------------------------------------

static boost::uuids::random_generator g_UUIDGenerator;

namespace Ocular
{
    namespace Core
    {
        OCULAR_REGISTER_TO_STRING(UUID, OCULAR_TO_STRING_LAMBDA
        {
            std::string result;

            if(raw)
            {
                UUID* uuid = void_cast<UUID*>(raw);

                if(uuid)
                {
                    result = uuid->toString();
                }
            }

            return result;
        });

        OCULAR_REGISTER_FROM_STRING(UUID, OCULAR_FROM_STRING_LAMBDA
        {
            if(out)
            {
                UUID* result = void_cast<UUID*>(out);

                if(result)
                {
                    result->set(str);
                }
            }
        });

        struct UUID_Internal
        {
            boost::uuids::uuid uuid;
        };

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        UUID::UUID(std::string const& uuid)
        {
            m_Internal = new UUID_Internal();
            set(uuid);
        }

        UUID::UUID(UUID const& other)
        {
            m_Internal = new UUID_Internal();
            m_Internal->uuid = other.m_Internal->uuid;

            m_String = other.m_String;
            m_Hash32 = other.m_Hash32;
            m_Hash64 = other.m_Hash64;
        }

        UUID::UUID()
        {
            m_Internal = new UUID_Internal();
            m_Internal->uuid = g_UUIDGenerator();
         
            m_String = boost::lexical_cast<std::string>(m_Internal->uuid);
            m_Hash32 = OcularEngine.HashGenerator()->getHash32(m_String);
            m_Hash64 = OcularEngine.HashGenerator()->getHash64(m_String);
        }

        UUID::~UUID()
        {
            delete m_Internal;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        UUID& UUID::operator=(UUID const& rhs)
        {
            const std::string other = rhs.toString();

            m_Internal->uuid = boost::lexical_cast<boost::uuids::uuid>(other);

            m_String = other;
            m_Hash32 = OcularEngine.HashGenerator()->getHash32(m_String);
            m_Hash64 = OcularEngine.HashGenerator()->getHash64(m_String);

            return (*this);
        }

        bool UUID::operator==(UUID const& rhs) const
        {
            boost::uuids::uuid rhsUUID;
            uint8_t rhsRaw[16];

            for(uint32_t i = 0; i < 16; i++)
            {
                rhsRaw[i] = rhs.getData(i);
            }

            memcpy(&rhsUUID, rhsRaw, sizeof(uint8_t) * 16);

            return (m_Internal->uuid == rhsUUID);
        }

        bool UUID::operator!=(UUID const& rhs) const
        {
            return !(*this == rhs);
        }

        //----------------------------------------------------------------------------------

        void UUID::set(std::string const& uuid)
        {
            m_Internal->uuid = boost::lexical_cast<boost::uuids::uuid>(uuid);

            m_String = uuid;
            m_Hash32 = OcularEngine.HashGenerator()->getHash32(m_String);
            m_Hash64 = OcularEngine.HashGenerator()->getHash64(m_String);
        }

        uint8_t UUID::getData(uint32_t const index) const
        {
            return m_Internal->uuid.data[Math::Clamp<uint32_t>(index, 0, 15)];
        }

        std::string const& UUID::toString() const
        {
            return m_String;
        }

        uint32_t UUID::getHash32() const
        {
            return m_Hash32;
        }

        uint64_t UUID::getHash64() const
        {
            return m_Hash64;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif