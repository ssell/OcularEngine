/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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

#include "stdafx.h"
#include "CoreDynamicRegistration.hpp"

//------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    if(OcularEditor.initialize(argc, argv))
    {
        OcularResources->setSourceDirectory("C:\\Projects\\OcularEngine\\Resources");
        OcularResources->forceSourceRefresh();

        while(OcularEditor.run());

        OcularEditor.shutdown();
    }
}