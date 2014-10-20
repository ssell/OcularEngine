/**
* Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Events/EventManager.hpp"
#include "Time/Timer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        EventManager::EventManager()
        {
        
        }

        EventManager::~EventManager()
        {
            m_Listeners.clear();
            m_Events.clear();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void EventManager::processEvents(long long const duration)
        {
            Timer timer;
            timer.start();

            std::shared_ptr<AEvent> event;

            while(timer.getElapsedMS() < duration)
            {
                m_Events.dequeue(event);
                triggerEvent(event);
            }
        }

        void EventManager::registerListener(AEventListener const * const listener, unsigned const priority)
        {
            std::shared_ptr<AEventListener> shared(listener);
            registerListener(shared, priority);
        }

        void EventManager::registerListener(std::shared_ptr<AEventListener> listener, unsigned const priority)
        {
            if(findListener(listener) == -1)
            {
                m_Listeners.push(listener, priority);
            }
        }

        void EventManager::unregisterListener(std::shared_ptr<AEventListener> listener)
        {
            m_Listeners.removeElement(listener);
        }

        void EventManager::queueEvent(std::shared_ptr<AEvent> event)
        {
            m_Events.enqueue(event, event.get()->getPriority());
        }

        void EventManager::fireEvent(std::shared_ptr<AEvent> event)
        {
            triggerEvent(event);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        int EventManager::findListener(std::shared_ptr<AEventListener> listener)
        {
            int index = -1;

            for(unsigned i = 0; i < m_Listeners.size(); i++)
            {
                if(m_Listeners.get(i).get() == listener.get())
                {
                    index = static_cast<int>(i);
                    break;
                }
            }

            return index;
        }

        void EventManager::triggerEvent(std::shared_ptr<AEvent> event)
        {
            for(unsigned i = 0; i < m_Listeners.size(); i++)
            {
                m_Listeners.get(i)->onEvent(event);
            }
        }
    }
}