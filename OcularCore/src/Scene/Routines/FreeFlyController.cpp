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

#include "Scene/Routines/FreeFlyController.hpp"
#include "Scene/SceneObject.hpp"
#include "Math/Vector4.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        FreeFlyController::FreeFlyController()
            : ARoutine()
        {

        }

        FreeFlyController::~FreeFlyController()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void FreeFlyController::onCreation()
        {
            if(m_Parent)
            {
                m_Parent->getTransform().setPosition(0.0f, 0.0f, -5.0f);
            }
        }

        void FreeFlyController::onUpdate(float const delta)
        {
            ARoutine::onUpdate(delta);

            if(m_Parent)
            {
                static const Math::Vector3f MovementVector = Math::Vector3f::Forward();

                Math::Vector3f currPosition = m_Parent->getTransform().getPosition();
                m_Parent->getTransform().setPosition(currPosition + (MovementVector * delta));
            }
        }

        bool FreeFlyController::onEvent(std::shared_ptr<AEvent> event)
        {
            return ARoutine::onEvent(event);
        }
    }
}