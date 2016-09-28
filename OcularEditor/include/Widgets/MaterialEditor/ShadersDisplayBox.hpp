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

#pragma once
#ifndef __H__OCULAR_EDITOR_MATERIAL_SHADERS_DISPLAY_BOX__H__
#define __H__OCULAR_EDITOR_MATERIAL_SHADERS_DISPLAY_BOX__H__

#include "MaterialPropertiesDisplayBox.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        class ResourceProperty;

        /**
         * \class ShaderDisplayBox
         */
        class ShadersDisplayBox : public MaterialPropertiesDisplayBox
        {
        public:

            ShadersDisplayBox(QWidget* parent = nullptr);
            ~ShadersDisplayBox();

            //------------------------------------------------------------

            virtual void setMaterial(Graphics::Material* material) override;
            virtual void updateProperties() override;

        protected:

            void buildWidgets();

        private:

            ResourceProperty* m_PropertyVertexShader;
            ResourceProperty* m_PropertyGeometryShader;
            ResourceProperty* m_PropertyFragmentShader;
            ResourceProperty* m_PropertyPreTessShader;
            ResourceProperty* m_PropertyPostTessShader;
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