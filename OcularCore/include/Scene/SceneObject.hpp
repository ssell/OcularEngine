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

#ifndef __H__OCULAR_CORE_SCENE_OBJECT__H__
#define __H__OCULAR_CORE_SCENE_OBJECT__H__

#include "Object.hpp"
#include "Math/Transform.hpp"

#include <string>

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
        class SceneManager;

        /**
         * \class SceneObject
         */
        class SceneObject : Object
        {
            friend class SceneManager;

        public:
            
            ~SceneObject();

            //------------------------------------------------------------------------------

            void  update(float const delta);
            float updateTimed();

            void preRender();
            void render();
            void postRender();

            //------------------------------------------------------------------------------

            Math::Transform transform;

        protected:

            SceneObject();

        private:

            std::string m_Name;
            
            bool m_IsStatic;
            bool m_IsActive;
            bool m_IsVisible;
            bool m_ForcedActive;
            bool m_ForcedVisible;
            bool m_InheritsPosition;
            bool m_InheritsRotation;
            bool m_InheritsScale;
            bool m_Persists;

            uint32_t m_Layer;
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