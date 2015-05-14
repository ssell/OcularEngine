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

#include "Events/EventSnooper.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        EventSnooper::EventSnooper()
        {
            m_IgnoreDuplicates = false;
            m_IgnorePriorityMonitor = false;
            m_IgnorePriorityCritical = false;
            m_IgnorePriorityHigh = false;
            m_IgnorePriorityMedium = false;
            m_IgnorePriorityLow = false;

            m_LastEventType = "";
        }

        EventSnooper::~EventSnooper()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void EventSnooper::setIgnoreDuplicates(bool const ignore)
        {
            m_IgnoreDuplicates = ignore;
        }

        void EventSnooper::setIgnorePriorityLevel(EventPriority const priority, bool const ignore)
        {
            switch(priority)
            {
            case Monitor:
                m_IgnorePriorityMonitor = ignore;
                break;

            case Critical:
                m_IgnorePriorityCritical = ignore;
                break;

            case High:
                m_IgnorePriorityHigh = ignore;
                break;

            case Medium:
                m_IgnorePriorityMedium = ignore;
                break;

            case Low:
                m_IgnorePriorityLow = ignore;
                break;

            default:
                break;
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool EventSnooper::onEvent(std::shared_ptr<Core::AEvent> event)
        {
            //----------------------------------------
            // Ignore this event due to priority level?
            
            switch(event->getPriority())
            {
            case Monitor:
            {
                if(m_IgnorePriorityMonitor)
                {
                    return true;
                }

                break;
            }

            case Critical:
            {
                if(m_IgnorePriorityCritical)
                {
                    return true;
                }

                break;
            }

            case High:
            {
                if(m_IgnorePriorityHigh)
                {
                    return true;
                }

                break;
            }

            case Medium:
            {
                if(m_IgnorePriorityMedium)
                {
                    return true;
                }

                break;
            }

            case Low:
            {
                if(m_IgnorePriorityLow)
                {
                    return true;
                }

                break;
            }

            default:
                break;
            }

            //----------------------------------------
            // Ignore this event due to duplicate?

            if(m_IgnoreDuplicates)
            {
                if(m_LastEventType.compare(event->getName()) == 0)
                {
                    return true;
                }
            }

            m_LastEventType = event->getName();

            //----------------------------------------
            // Log this event

            OcularEngine.Logger()->info("Event [", event->getUUID().toString(), "] Fired: "
                                        "\n\tPriority: ", event->getPriority(),
                                        "\n\t    Type: ", event->getName(),
                                        "\n\t      On: ", event->getCreationTime());


            return true;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}