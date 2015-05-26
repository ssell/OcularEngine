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
#include <map>
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
        class SceneManager;
        class Routine;

        /**
         * \class SceneObject
         *
         * A SceneObject represents the instance of an arbitrary object in a Scene.
         * This can range from a static scenery object, such as a rock, to a particle effect,
         * to a physics volume, to a multifaceted actor.
         *
         * A single SceneObject can have multiple child objects attached to it. This can be 
         * thought of as similar to a car. A parent chassis object could have child axle objects
         * which in turn have child wheel objects. Each level down inherits the parent's transform
         * and active/visible status (unless otherwise overridden).
         *
         * Additionally, there are Routine and Renderable instances that may be attached to
         * a SceneObject. A Routine represents the logic behind an object while the Renderable
         * is any part of the object that is to be rendered onto the screen.
         *
         *
         */
        class SceneObject : public Object
        {
            friend class SceneManager;

        public:
            
            ~SceneObject();

            //------------------------------------------------------------
            // Child Object Methods

            SceneObject* createChild(std::string const& name);
            
            SceneObject* findChild(std::string const& name);
            SceneObject* findChild(UUID const& uuid);
            SceneObject* findChild(uint32_t const index);

            void removeChild(std::string const& name);
            void removeChild(UUID const& uuid);
            void removeChild(uint32_t const index);

            uint32_t getNumChildren() const;

            //------------------------------------------------------------
            // Routine Methods

            void addRoutine(std::string const& name);

            Routine* getRoutine(std::string const& name);
            void getAllRoutines(std::string const& name, std::list<Routine*>& routines);

            //------------------------------------------------------------
            // Public Members

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