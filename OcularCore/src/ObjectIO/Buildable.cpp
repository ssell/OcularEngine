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

#include "ObjectIO/Buildable.hpp"
#include "ObjectIO/Exposable.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //--------------------------------------------------------------------------------------
        // CONSTRUCTORS
        //--------------------------------------------------------------------------------------

        //--------------------------------------------------------------------------------------
        // PUBLIC METHODS
        //--------------------------------------------------------------------------------------

        void Buildable::onLoad(BuilderNode const* node)
        {
            Exposable* exposable = (Exposable*)(this);

            if(exposable)
            {

            }
        }

        void Buildable::onSave(BuilderNode* node)
        {
            // If this also inherits from Exposable, then automatically
            // add any exposed variables/pointers to the node chain.

            if(node)
            {
                Exposable* exposable = (Exposable*)(this);

                if(exposable)
                {
                    for(auto variableMapping : exposable->m_ExposedVariables)
                    {
                        ExposedVariable* variable = &variableMapping.second;

                        if(variable)
                        {
                            if(variable->isPointer)
                            {
                                // If the variable is a pointer, we only add it to the node chain
                                // if it can be cast to another Buildable. If it can, then we add
                                // it as a new child and let it's onSave build itself.

                                Buildable* buildableChild = (Buildable*)(variable->data);

                                if(buildableChild)
                                {
                                    buildableChild->onSave(node->addChild(variable->name, "", variable->type));
                                }
                            }
                            else
                            {
                                node->addChild(variable->name, OcularString->toString(variable->type, variable->data), variable->type);
                            }
                        }
                    }
                }
            }
        }

        //--------------------------------------------------------------------------------------
        // PROTECTED METHODS
        //--------------------------------------------------------------------------------------

        //--------------------------------------------------------------------------------------
        // PRIVATE METHODS
        //--------------------------------------------------------------------------------------
    }
}