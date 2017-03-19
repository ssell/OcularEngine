/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "Scene/ARoutine.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ARoutine::ARoutine(std::string const& name, std::string const& type)
            : Object(name, type),
              m_Priority(Priority::Medium),
              m_Parent(nullptr)
        {
            OcularScene->objectAddedRoutine(this);

            //uint32_t* priority = (uint32_t*)(&m_Priority);
            //OCULAR_EXPOSE(priority);
        }

        ARoutine::~ARoutine()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool ARoutine::operator<(ARoutine const& rhs)
        {
            return (m_Priority < rhs.getPriorityLevel());
        }

        bool ARoutine::operator>(ARoutine const& rhs)
        {
            return (m_Priority > rhs.getPriorityLevel());
        }

        void ARoutine::onSceneStart()
        {
        
        }

        void ARoutine::onSceneEnd()
        {
        
        }

        void ARoutine::onCreation()
        {
        
        }

        void ARoutine::onDestruction()
        {
        
        }

        void ARoutine::onPause()
        {
        
        }

        void ARoutine::onUnpause()
        {
        
        }

        void ARoutine::onUpdate(float const delta)
        {
        
        }

        float ARoutine::onTimedUpdate()
        {
            return FLT_MAX;
        }

        void ARoutine::onPreRender()
        {
        
        }

        void ARoutine::onPostRender()
        {
        
        }

        bool ARoutine::onEvent(std::shared_ptr<AEvent> event)
        {
            return true;
        }

        Priority ARoutine::getPriorityLevel() const
        {
            return m_Priority;
        }

        SceneObject* ARoutine::getParent() const
        {
            return m_Parent;
        }

        std::string const& ARoutine::getName() const
        {
            return m_Name;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void ARoutine::setParent(SceneObject* object)
        {
            if(m_Parent)
            {
                m_Parent->removeRoutine(this, true);
            }

            m_Parent = object;
        }

        void ARoutine::setName(std::string const& name)
        {
            m_Name = name;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}