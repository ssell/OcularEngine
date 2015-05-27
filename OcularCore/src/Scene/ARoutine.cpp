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

#include "Scene/ARoutine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ARoutine::ARoutine(std::string const& name)
        {
            m_Name = name;
            m_Priority = Priority::Medium;
        }

        ARoutine::~ARoutine()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

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

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}