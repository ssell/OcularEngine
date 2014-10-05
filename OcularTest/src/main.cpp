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
#include "Utilities\Structures\PriorityMultiQueue.hpp"
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

long long testSTLPriorityQueue(unsigned numTests, Ocular::Utils::Random::ARandom* action,
    Ocular::Utils::Random::ARandom* priority)
{
    Ocular::Core::Timer timer;
    timer.reset();
    timer.start();

    std::priority_queue<int> queue;

    for(unsigned i = 0; i < numTests; i++)
    {
        unsigned random = action->next(0, 5);

        if(random < 3)
        {
            // Add
            queue.push((Ocular::Core::EVENT_PRIORITY)priority->next(1,5));
        }
        else if(random == 3)
        {
            // Remove one
            if(queue.size() > 0)
            {
                queue.pop();
            }
        }
        else
        {
            // Remove all
            while(queue.size() > 0)
            {
                queue.pop();
            }
        }
    }

    return timer.getElapsedMS();
}

long long testPriorityMultiQueue(unsigned numTests, Ocular::Utils::Random::ARandom* action,
    Ocular::Utils::Random::ARandom* priority)
{
    Ocular::Core::Timer timer;
    timer.reset();
    timer.start();

    Ocular::Utils::PriorityMultiQueue<int, 5096> queue;

    int value = 0;

    for(unsigned i = 0; i < numTests; i++)
    {
        unsigned random = action->next(0, 5);

        if(random < 3)
        {
            // Add
            queue.enqueue(5, (Ocular::Core::EVENT_PRIORITY)priority->next(1,5));
        }
        else if(random == 3)
        {
            // Remove one
            queue.dequeue(value);
        }
        else
        {
            // Remove all
            while(queue.dequeue(value));
        }
    }

    return timer.getElapsedMS();
}

void compareQueuePerformance(unsigned numTests, long long& stlTime, long long& ocuTime)
{
    Ocular::Utils::Random::XorShift96 action;
    Ocular::Utils::Random::XorShift96 priority;

    action.seed(100);
    priority.seed(50);

    stlTime = testSTLPriorityQueue(numTests, &action, &priority);

    action.seed(100);
    priority.seed(50);

    ocuTime = testPriorityMultiQueue(numTests, &action, &priority);
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();

    long long stlTime = 0;
    long long ocuTime = 0;

    for(unsigned i = 10; i <= 10000000; i *= 10)
    {
        long long stlTotal = 0;
        long long ocuTotal = 0;

        for(unsigned j = 0; j < 10; j++)
        {
            compareQueuePerformance(i, stlTime, ocuTime);
            stlTotal += stlTime;
            ocuTotal += ocuTime;
        }

        double stlAverage = (double)stlTotal / 10.0;
        double ocuAverage = (double)ocuTotal / 10.0;

        OcularEngine.Logger()->info(i, " iterations:\n\tSTL: ", stlAverage, "ms\n\tOCU: ", ocuAverage, "ms\n");
    }

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