/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "Graphics/Shader/Uniform/Uniform.hpp"
#include "Math/Matrix3x3.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Uniform::Uniform()
            : m_Size(0),
              m_Register(0)
        {
            m_Data.fill(0.0f);
        }

        Uniform::~Uniform()
        {

        }

        Uniform::Uniform(Uniform const& other)
        {
            m_Name     = other.getName();
            m_Type     = other.getType();
            m_Size     = Math::Clamp<uint32_t>(other.getSize(), 0, Uniform::MaxDataSize);
            m_Register = other.getRegister();

            float const* otherData = other.getData();

            if(otherData)
            {
                memcpy(&m_Data[0], otherData, sizeof(float) * m_Size);
            }
        }

        void Uniform::operator=(Uniform const& other)
        {
            m_Name     = other.getName();
            m_Type     = other.getType();
            m_Size     = Math::Clamp<uint32_t>(other.getSize(), 0, Uniform::MaxDataSize);
            m_Register = other.getRegister();

            float const* otherData = other.getData();

            if(otherData)
            {
                memcpy(&m_Data[0], otherData, sizeof(float) * m_Size);
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------
        // Data Methods
        //----------------------------------------------------------------

        void Uniform::setData(float const data)
        {
            m_Size = 1;
            m_Data[0] = data;
        }

        void Uniform::setData(Math::Vector4f const& data)
        {
            m_Size = 4;
            
            for(int i = 0; i < 4; i++)
            {
                m_Data[i] = data[i];
            }
        }

        void Uniform::setData(Math::Matrix3x3 const& data)
        {
            m_Size = 9;
            
            for(int i = 0; i < 9; i++)
            {
                m_Data[i] = data.getElement(i);
            }
        }

        void Uniform::setData(Math::Matrix4x4 const& data)
        {
            m_Size = 16;
            
            for(int i = 0; i < 16; i++)
            {
                m_Data[i] = data.getElement(i);
            }
        }

        bool Uniform::setData(uint32_t const count, float const* data)
        {
            bool result = false;

            const uint32_t clampedCount = Math::Clamp<uint32_t>(count, 0, Uniform::MaxDataSize);

            if(data)
            {
                if((clampedCount == 1) || (clampedCount == 4) || (clampedCount == 12) || (clampedCount == 16))
                {
                    m_Size = count;

                    for(uint8_t i = 0; i < m_Size; i++)
                    {
                        m_Data[i] = data[i];
                    }
                }
                else
                {
                    OcularLogger->error("Invalid number of elements. Valid counts are 1, 4, 12, and 16", OCULAR_INTERNAL_LOG("Uniform", "setData"));
                }
            }
            else
            {
                OcularLogger->error("Provided data is NULL", OCULAR_INTERNAL_LOG("Uniform", "setData"));
            }

            return result;
        }

        uint32_t Uniform::getSize() const
        {
            return m_Size; 
        }

        float Uniform::getElement(uint32_t const index) const
        {
            float result = 0.0f;

            if(index < m_Size)
            {
                result = m_Data[index];
            }
            else
            {
                OcularLogger->warning("Attempting to access out-of-bounds index ", index, OCULAR_INTERNAL_LOG("Uniform", "getElement"));
            }

            return result;
        }

        float const* Uniform::getData() const
        {
            return &m_Data[0];
        }

        //----------------------------------------------------------------
        // Name Methods
        //----------------------------------------------------------------

        void Uniform::setName(std::string const& name)
        {
            m_Name = name;
        }

        std::string const& Uniform::getName() const
        {
            return m_Name;
        }

        //----------------------------------------------------------------
        // Type Methods
        //----------------------------------------------------------------

        void Uniform::setType(std::string const& type)
        {
            m_Type = type;
        }

        std::string const& Uniform::getType() const
        {
            return m_Type;
        }

        //----------------------------------------------------------------
        // Register Methods
        //----------------------------------------------------------------

        void Uniform::setRegister(uint32_t const index)
        {
            m_Register = index;
        }

        uint32_t Uniform::getRegister() const
        {
            return m_Register;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}