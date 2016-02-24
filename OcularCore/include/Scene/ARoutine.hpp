/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_CORE_SCENE_AROUTINE__H__
#define __H__OCULAR_CORE_SCENE_AROUTINE__H__

#include "ObjectIO/Exposable.hpp"
#include "ObjectIO/Buildable.hpp"

#include "Events/AEventListener.hpp"
#include "Priority.hpp"

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
         * \class ARoutine
         *
         * |    Event    |                          Called By                          |
         * | ----------: | :---------------------------------------------------------- |
         * |  SceneStart | TBD                                                         |
         * |    SceneEnd | During Scene destruction (Scene::~Scene)                    |
         * |    Creation | When routine is created (SceneObject::addRoutine)           |
         * | Destruction | When routine is destroyed (SceneObject::~SceneObject)       |
         * |       Pause | TBD                                                         |
         * |     Unpause | TBD                                                         |
         * |      Update | During Scene update (Scene::update)                         |
         * | TimedUpdate | TBD                                                         |
         * |   PreRender | TBD                                                         |
         * |  PostRender | TBD                                                         |
         * |       Event | TBD                                                         |
         */
        class ARoutine : public AEventListener, public Exposable, public Buildable
        {
            friend class SceneObject;

        public:

            ARoutine();
            virtual ~ARoutine();
            
            bool operator<(ARoutine const& rhs);
            bool operator>(ARoutine const& rhs);

            /**
             * Called when the active Scene is started. Note that this will typically only
             * get called for Routines attached to peristent SceneObjects.
             */
            virtual void onSceneStart();

            /**
             * Called when the active Scene is ended. Note that this will typically only
             * get called for Routines attached to persistent SceneObjects.
             */
            virtual void onSceneEnd();

            /**
             * Called when the parent SceneObject is added to the active Scene.
             *
             * If this Routine is added after the SceneObject has already been created,
             * then this method is called on Routine creation.
             */
            virtual void onCreation();

            /**
             * Called when the parent SceneObject is removed from the active Scene.
             */
            virtual void onDestruction();

            /**
             * Called when the active Scene has been paused.
             */
            virtual void onPause();

            /**
             * Called when the active Scene has been unpaused.
             */
            virtual void onUnpause();

            /**
             * Called once per frame. Generally, Routines are updated in the order
             * they are traversed in a Scene. 
             *
             * If a special circumstance requires that a Routine's update is called before 
             * or after other Routines, then the priority level can be adjusted.
             *
             * \param[in] delta Current delta time (time in seconds that the last frame took to complete).
             */
            virtual void onUpdate(float const delta);

            /**
             * An update called after a specified amount of time.
             * 
             * The return value is the amount of time, in seconds, that must elapse
             * before this method is called again. This useful for logic that does
             * not need to be run every frame, and instead can be run once a second
             * or minute.
             *
             * Returning a low value (approaching or below zero) will simply have this
             * method behave identically to the standard onUpdate. 
             *
             * It should be noted that the returned time is only guaranteed to be a minimum
             * amount of elapsed time. Depending on the framerate, it may take longer than
             * the specified time to call the method again.
             *
             * \return Minimum time to elapse (in seconds) before this method is called again.
             */
            virtual float onTimedUpdate();

            /**
             * Called prior to the rendering of the scene.
             */
            virtual void onPreRender();

            /**
             * Called after the scene has been rendered.
             */
            virtual void onPostRender();

            /**
             * Called when an event occurs that the routine is registered as a listener for.
             *
             * \param[in] event Pointer to the event
             * \return TRUE to keep processing this event after this listener, FALSE to consume this event
             */
            virtual bool onEvent(std::shared_ptr<AEvent> event);

            /**
             * \routine The priority level of this Routine.
             */
            Priority getPriorityLevel() const;

            /**
             * \return The parent SceneObject that this Routine instance is attached to.
             */
            SceneObject* getParent() const;

            /**
             * Returns the non-unique name assigned to this Routine.
             */
            std::string const& getName() const;

            //------------------------------------------------------------
            // Inherited Methods
            //------------------------------------------------------------

            void onLoad(BuilderNode const* node) override;
            void onSave(BuilderNode* node) override;

        protected:

            void setParent(SceneObject* object);
            void setName(std::string const& name);

            Priority m_Priority;      ///< Priority level of this Routine in the Routine Queue.
            std::string m_Name;

            SceneObject* m_Parent;    ///< The SceneObject instance that this routine is attached to.

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