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

#include <iostream>
#include <queue>

#include "OcularEngine.hpp"
#include "Time\Timer.hpp"
#include "Utilities\Structures\CircularQueue.hpp"
#include "Events\AEvent.hpp"

//------------------------------------------------------------------------------------------

class SampleEvent : public Ocular::Core::AEvent
{
public:

    SampleEvent(Ocular::Core::EVENT_PRIORITY priority)
        : Ocular::Core::AEvent("Sample Event", priority)
    {

    }

    ~SampleEvent() { }

protected:

private:

};

long long testSTLPriorityQueue(unsigned numTests)
{
    Ocular::Core::Timer timer;
    std::priority_queue<Ocular::Core::AEvent, std::vector<Ocular::Core::AEvent>, Ocular::Core::CompareEventPriority> queue;

    for(unsigned i = 0; i < numTests; i++)
    {
        
    }

    return timer.getElapsedMS();
}

long long testPriorityMultiQueue(unsigned numTests)
{
    Ocular::Core::Timer timer;


    return timer.getElapsedMS();
}

void compareQueuePerformance(unsigned numTests)
{
    long long stlTime = testSTLPriorityQueue(numTests);
    long long ocuTime = testPriorityMultiQueue(numTests);

    OcularEngine.Logger()->info(numTests, " conducted in:\n\tSTL: ", stlTime, "\n\tOCU: ", ocuTime);
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();

    compareQueuePerformance(10000);

    OcularEngine.shutdown();
}