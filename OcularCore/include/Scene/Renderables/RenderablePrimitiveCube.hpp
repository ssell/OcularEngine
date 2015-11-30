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
#ifndef __H__OCULAR_CORE_SCENE_RENDERABLE_PRIMITIVE_CUBE__H__
#define __H__OCULAR_CORE_SCENE_RENDERABLE_PRIMITIVE_CUBE__H__

#include "Scene/ARenderable.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        class SceneObject;

        /**
         * \class RenderablePrimitiveCube
         */
        class RenderablePrimitiveCube : public ARenderable
        {
        public:

            RenderablePrimitiveCube(std::string const& name, SceneObject* parent);
            virtual ~RenderablePrimitiveCube();

            virtual bool initialize() override;

        protected:

            bool createMesh();

        private:
        };
    }
}

//------------------------------------------------------------------------------------------

#endif