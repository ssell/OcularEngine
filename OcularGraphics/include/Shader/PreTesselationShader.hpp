/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

#pragma
#ifndef __H__OCULAR_GRAPHICS_PRETESSELATION_SHADER__H__
#define __H__OCULAR_GRAPHICS_PRETESSELATION_SHADER__H__

#include "Shader.hpp"

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
         * \class PreTesselationShader 
         */
        class PreTesselationShader : public Shader 
        {
        public:

            PreTesselationShader();
            ~PreTesselationShader();

            virtual void load(Core::File const source) = 0;
            virtual void bind() = 0;
            virtual void unbind() = 0;

        protected:

        private:
        };

        typedef PreTesselationShader HullShader;
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