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
#include "Utilities/Structures/PriorityList.hpp"

//------------------------------------------------------------------------------------------

class Foo
{
public:
    Foo(std::string str)
    {
        name = str;
    }

    ~Foo()
    {

    }

    std::string name;

protected:

private:

};

int main(int argc, char** argv)
{
    OcularEngine.initialize();

    Ocular::Utils::PriorityList<std::shared_ptr<Foo>, 16> list;

    std::shared_ptr<Foo> a = std::make_shared<Foo>("a");
    std::shared_ptr<Foo> b = std::make_shared<Foo>("b");
    std::shared_ptr<Foo> c = std::make_shared<Foo>("c");
    std::shared_ptr<Foo> d = std::make_shared<Foo>("d");
    std::shared_ptr<Foo> e = std::make_shared<Foo>("e");

    //------------------------------------------------
    // Add Element test

    list.add(a, 0);
    list.add(b, 1);
    list.add(c, 2);
    list.add(d, 3);

    OcularEngine.Logger()->info("Contents:");
    for (std::size_t i = 0; i < list.count(); i++)
    {
        OcularEngine.Logger()->info("\t@[", i, "]: ", list.get(i).get()->name);
    }
    OcularEngine.Logger()->info("");

    //------------------------------------------------
    // Contains Element test

    if (list.contains(c))
    {
        OcularEngine.Logger()->info("List contains 'c'");
        OcularEngine.Logger()->info("");
    }
    else
    {
        OcularEngine.Logger()->info("List does not contain 'c'");
        OcularEngine.Logger()->info("");
    }

    if (list.contains(e))
    {
        OcularEngine.Logger()->info("List contains 'e'");
        OcularEngine.Logger()->info("");
    }
    else
    {
        OcularEngine.Logger()->info("List does not contain 'e'");
        OcularEngine.Logger()->info("");
    }

    //------------------------------------------------
    // Remove Element test

    list.removeElement(c);

    OcularEngine.Logger()->info("Contents:");
    for (std::size_t i = 0; i < list.count(); i++)
    {
        OcularEngine.Logger()->info("\t@[", i, "]: ", list.get(i).get()->name);
    }
    OcularEngine.Logger()->info("");

    //------------------------------------------------
    // Remove Index test

    list.removeIndex(1);

    OcularEngine.Logger()->info("Contents:");
    for (std::size_t i = 0; i < list.count(); i++)
    {
        OcularEngine.Logger()->info("\t@[", i, "]: ", list.get(i).get()->name);
    }
    OcularEngine.Logger()->info("");


    OcularEngine.shutdown();
}