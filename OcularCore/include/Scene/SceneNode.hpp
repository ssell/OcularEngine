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
        class SceneObject;

        enum class SceneNodeType
        {
            Root = 0,
            Internal,
            Leaf
        };

        /**
         * \class SceneNode
         *
         * Base node of a SceneTree.
         */
        class SceneNode
        {
        public:

            SceneNode();
            ~SceneNode();
 
            /**
             * Attaches the specified parent object to this scene node.
             * \param[in] object
             */
            virtual void attachObject(SceneObject* object) = 0;

            //------------------------------------------------------------
           // Public Variables

            SceneNodeType type;                         ///< What type of node this scene node is.
            SceneNode*    parent;                       ///< Parent node (null if this is root).

        protected:

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