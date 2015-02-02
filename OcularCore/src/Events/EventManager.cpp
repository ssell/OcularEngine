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
            //m_Listeners.clear();
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
                if(!m_Events.dequeue(event))
                {
                    break;
                }

                triggerEvent(event);
            }
        }

        void EventManager::registerListener(AEventListener* listener, unsigned const priority)
        {
            if((listener != nullptr) && (findListener(listener) == -1))
            {
                m_Listeners.push(listener, priority);
            }
        }

        void EventManager::unregisterListener(AEventListener* listener)
        {
            if(listener != nullptr)
            {
                m_Listeners.removeElement(listener);
            }
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

        int EventManager::findListener(AEventListener* pListener)
        {
            int index = -1;

            if(pListener != nullptr)
            {
                for(unsigned i = 0; i < m_Listeners.size(); i++)
                {
                    AEventListener* listener = m_Listeners.get(i);

                    if((listener != nullptr) && (pListener == listener))
                    {
                        index = static_cast<int>(i);
                        break;
                    }
                }
            }

            return index;
        }

        void EventManager::triggerEvent(std::shared_ptr<AEvent> event)
        {
            for(unsigned i = 0; i < m_Listeners.size(); i++)
            {
                AEventListener* listener = m_Listeners.get(i);

                if(listener != nullptr)
                {
                    if(!listener->onEvent(event))
                    {
                        // Listener consumed this event
                        break;   
                    }
                }
            }
        }
    }
}