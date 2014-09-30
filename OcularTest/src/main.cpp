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
#include "OcularEngine.hpp"
#include "Time\Timer.hpp"
#include "Utilities\Structures\CircularQueue.hpp"

//------------------------------------------------------------------------------------------

class Foo
{
public:

    Foo(std::string name) : m_Name(name)
    {
        m_Name = name;
    }

    ~Foo()
    {
        OcularEngine.Logger()->info("Destroying '", m_Name, "'");
    }

    std::string getName()
    {
        return m_Name;
    }

protected:

private:

    std::string m_Name;
};

//------------------------------------------------------------------------------------------

void testQueue()
{
    std::shared_ptr<Foo> a = std::make_shared<Foo>("object a");
    std::shared_ptr<Foo> b = std::make_shared<Foo>("object b");
    std::shared_ptr<Foo> c = std::make_shared<Foo>("object c");
    std::shared_ptr<Foo> d = std::make_shared<Foo>("object d");
    std::shared_ptr<Foo> e = std::make_shared<Foo>("object e");

    Ocular::Utils::CircularQueue<std::shared_ptr<Foo>, 3> queue;

    if(queue.enqueue(a)) { OcularEngine.Logger()->info("Queued '", a->getName(), "'");}
    if(queue.enqueue(b)) { OcularEngine.Logger()->info("Queued '", b->getName(), "'");}
    if(queue.enqueue(c)) { OcularEngine.Logger()->info("Queued '", c->getName(), "'");}
    if(queue.enqueue(d)) { OcularEngine.Logger()->info("Queued '", d->getName(), "'");}

   a.reset();
   b.reset();
   c.reset();
   d.reset();

    std::shared_ptr<Foo> bar;

    while(queue.dequeue(bar))
    {
        OcularEngine.Logger()->info("Dequeued '", bar->getName(), "'");
    }

    if(queue.enqueue(e)) { OcularEngine.Logger()->info("Queued '", e->getName(), "'");}
    if(queue.dequeue(bar)) { OcularEngine.Logger()->info("Dequeued '", bar->getName(), "'");}
}

int main(int argc, char** argv)
{
    OcularEngine.initialize();

    testQueue();

    OcularEngine.shutdown();
}