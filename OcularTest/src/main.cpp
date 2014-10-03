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
#include "Utilities\Random\XorShift.hpp"

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

    OcularEngine.shutdown();
}












/*
void prngAnalysis(Ocular::Utils::Random::ARandom* prng, unsigned iterations)
{
    int values[100];
    memset(values, 0, sizeof(int) * 100);

    //------------------------------------------------

    long long start = OcularEngine.Clock()->getElapsedMS();
    prng->seed(OcularEngine.Clock()->getEpochMS());

    for(unsigned i = 0; i < iterations; i++)
    {
        values[prng->next(0, 100)]++;
    }

    long long stop = OcularEngine.Clock()->getElapsedMS();

    //------------------------------------------------

    float minPercent = 100.0f;
    float maxPercent = 0.0f;

    unsigned minNum = 0;
    unsigned maxNum = 0;

    for(unsigned i = 0; i < 100; i++)
    {
        float percent = ((float)values[i] / (float)iterations) * 100.0f;
        OcularEngine.Logger()->info((i < 10 ? "0" : ""), i, ": ", values[i], " / ", iterations, "  (", percent, "%)");

        if(percent < minPercent)
        {
            minPercent = percent;
            minNum = i;
        }

        if(percent > maxPercent)
        {
            maxPercent = percent;
            maxNum = i;
        }
    }

    OcularEngine.Logger()->info("Min: ", minPercent, " (", minNum, ")");
    OcularEngine.Logger()->info("Max: ", maxPercent, " (", maxNum, ")");
    OcularEngine.Logger()->info("Completed in ", (stop - start), "ms");
}
*/