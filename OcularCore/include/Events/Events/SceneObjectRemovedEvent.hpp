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
#ifndef __H__OCULAR_EVENTS_SCENE_OBJECT_REMOVED_EVENT__H__
#define __H__OCULAR_EVENTS_SCENE_OBJECT_REMOVED_EVENT__H__

#include "Events/AEvent.hpp"
#include "UUID.hpp"

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
        /**
         * \class SceneObjectRemovedEvent
         *
         * Event notifying that a SceneObject has been removed from the active Scene.
         *
         * Note that by the time the event is received, the SceneObject may have
         * potentially already been deleted, which is why the UUID is provided 
         * instead of the SceneObject itself.
         *
         * String Descriptor: "SceneObjectRemovedEvent" <br/>
         * Event Priority: Medium 
         */
        class SceneObjectRemovedEvent : public AEvent 
        {
        public:

            SceneObjectRemovedEvent(UUID const& uuid);
            SceneObjectRemovedEvent();

            virtual ~SceneObjectRemovedEvent();

            UUID uuid;

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