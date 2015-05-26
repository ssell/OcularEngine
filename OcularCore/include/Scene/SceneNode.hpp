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

#ifndef __H__OCULAR_CORE_SCENE_NODE__H__
#define __H__OCULAR_CORE_SCENE_NODE__H__

#include <list>

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
        class SceneTree;
        class SceneObject;

        /**
         * \class SceneNode
         *
         * Base node of a SceneTree. The behaviour of nodes varies based on the type of
         * SceneTree it is part of (oct, bounding-volume, bsp, etc.) but they are generally
         * either static or contain only static SceneObjects.
         */
        class SceneNode
        {
            friend class SceneTree;

        public:

            SceneNode();
            ~SceneNode();

        protected:

            SceneNode* previous;
            SceneNode* next;
            SceneNode* parent;

            std::list<SceneObject*> sceneObjects;

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