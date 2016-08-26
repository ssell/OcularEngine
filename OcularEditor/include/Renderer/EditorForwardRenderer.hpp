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
#ifndef __H__OCULAR_EDITOR_FORWARD_RENDERER__H__
#define __H__OCULAR_EDITOR_FORWARD_RENDERER__H__

#include "Renderer/Renderer.hpp"

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
        /** 
         * \class ForwardRenderer
         *
         * Standard forward renderer with minor adjustments specifically for Editor rendering.
         */
        class ForwardRenderer : public Core::Renderer
        {
        public:

            ForwardRenderer();
            virtual ~ForwardRenderer();

            /**
             * Invokes the debug version of the render methods.
             */
            virtual void render(std::vector<Core::SceneObject*>& objects) override;

            /**
             * Invokes the debug version of the render methods.
             */
            virtual void render(std::vector<Core::SceneObject*>& objects, Graphics::Material* material) override;

        protected:

            void buildSelectedMaterial();

        private:

            Graphics::Material* m_SelectedMaterial;     // Material used when rendering the selected object
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
