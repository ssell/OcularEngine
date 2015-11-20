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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_SHADER_UNIFORM__H__
#define __H__OCULAR_GRAPHICS_SHADER_UNIFORM__H__

#include "Math/Matrix4x4.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \class Uniform
         */
        class Uniform
        {
        public:
            
            /**
             *
             */
            Uniform();
            ~Uniform();

            //------------------------------------------------------------
            // Data Methods
            //------------------------------------------------------------

            /**
             * Sets the uniform data.
             * \param[in] data Single float value for the Uniform to represent.
             */
            void setData(float data);

            /**
             * Sets the uniform data.
             * \param[in] data A four-component vector for the Uniform to represent.
             */
            void setData(Math::Vector4f const& data);

            /**
             * Sets the uniform data.
             * \param[in] data A 3x3 matrix for the Uniform to represent.
             */
            void setData(Math::Matrix3x3f const& data);

            /**
             * Sets the uniform data.
             * \param[in] data A 4x4 matrix for the Uniform to represent.
             */
            void setData(Math::Matrix4x4f const& data);

            /**
             * Sets the uniform data.
             *
             * \param[in] size Number of elements being passed. Valid values are: 1, 4, 12, 16.
             * \param[in] data Uniform data to set.
             *
             * \return TRUE if successful. May return false if size is invalid, or elements is NULL.
             */
            bool setData(uint32_t size, float const* data);

            /**
             * \return Number of data elements stored in this uniform.
             */
            uint32_t getSize() const;
            
            /**
             * Retrieves the data at the specified index.
             * 
             * \param[in] index Index of data to retrieve. Depending on the type of underlying uniform
             *                  (float, vector, matrix), this may be on the range of [0,16).
             *
             * \return The data at the specified index. If index or underlying data is invalid, will return 0.0.
             */
            float getElement(uint32_t index) const;
            
            /**
             * \return A pointer to all data. May be NULL if data elements were never set or there was an error during creation.
             */
            float* getAllElements() const;

            //------------------------------------------------------------
            // Name Methods
            //------------------------------------------------------------

            /** 
             * Sets the name of this uniform.
             * \param[in] name
             */
            void setName(std::string const& name);
            
            /**
             * \return The string name of this Uniform.
             */
            std::string const& getName() const;

            //------------------------------------------------------------
            // Register Methods
            //------------------------------------------------------------

            /**
             * Sets the register index of this uniform.
             * \param[in] index
             */
            void setRegister(uint32_t index);

            /**
             * \return The register index of this Uniform.
             */
            uint32_t getRegister() const;

        protected:

            void clearData();

            std::string m_Name;
            uint32_t m_Register;

            uint32_t m_Size;
            float* m_Data;

        private:
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif