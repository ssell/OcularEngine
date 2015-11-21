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

#include "Graphics/Shader/Uniform/Uniform.hpp"
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
            : m_Size(0), m_Data(nullptr), m_Register(0)
        {
            
        }

        Uniform::~Uniform()
        {
            clearData();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------
        // Data Methods
        //----------------------------------------------------------------

        void Uniform::setData(float const data)
        {
            clearData();

            m_Size = 1;
            m_Data = new float[1];
            m_Data[0] = data;
        }

        void Uniform::setData(Math::Vector4f const& data)
        {
            clearData();

            m_Size = 4;
            m_Data = new float[4];
            
            for(int i = 0; i < 4; i++)
            {
                m_Data[i] = data[i];
            }
        }

        void Uniform::setData(Math::Matrix3x3f const& data)
        {
            clearData();

            m_Size = 12;
            m_Data = new float[12];
            
            for(int i = 0; i < 12; i++)
            {
                m_Data[i] = data.getElement(i);
            }
        }

        void Uniform::setData(Math::Matrix4x4f const& data)
        {
            clearData();

            m_Size = 16;
            m_Data = new float[16];
            
            for(int i = 0; i < 16; i++)
            {
                m_Data[i] = data.getElement(i);
            }
        }

        bool Uniform::setData(uint32_t const count, float const* data)
        {
            bool result = false;

            clearData();

            if(data)
            {
                if((count == 1) || (count == 4) || (count == 12) || (count == 16))
                {
                    m_Size = count;
                    m_Data = new float[m_Size];

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

            if(m_Data)
            {
                if(index < m_Size)
                {
                    result = m_Data[index];
                }
                else
                {
                    OcularLogger->warning("Attempting to access out-of-bounds index ", index, OCULAR_INTERNAL_LOG("Uniform", "getElement"));
                }
            }
            else
            {
                OcularLogger->warning("Attempting to access Uniform data without properly initializing Uniform (element data is NULL)", OCULAR_INTERNAL_LOG("Uniform", "getElement"));
            }

            return result;
        }

        float* Uniform::getData() const
        {
            return m_Data;
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

        void Uniform::clearData()
        {
            m_Size = 0;

            if(m_Data)
            {
                delete[] m_Data;
                m_Data = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}