/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "ObjectIO/ObjectIO.hpp"
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

        void ObjectIO::onLoad(BuilderNode const* node)
        {
            if(node)
            {
                for(auto variableMapping : m_ExposedVariables)
                {
                    ExposedVariable* variable = &variableMapping.second;

                    if(variable)
                    {
                        // Do we have a node associated with the variable?
                        const BuilderNode* child = node->getChild(variable->name);

                        if(child)
                        {
                            if(variable->isPointer)
                            {
                                // If the variable is a pointer, we only handle loading it
                                // if it can be cast to another ObjectIO.

                                ObjectIO** buildableVar = (ObjectIO**)(variable->data);

                                if(*buildableVar)
                                {
                                    // Pass off the current child node and let it load itself
                                    (*buildableVar)->onLoad(child);
                                }
                            }
                            else if(variable->isExposed)
                            {
                                ObjectIO* io = (ObjectIO*)(variable->data);

                                if(io)
                                {
                                    io->onLoad(child);
                                }
                            }
                            else
                            {
                                OcularString->fromString(variable->type, child->getValue(), variable->data);
                            }
                        }
                    }
                }
            }
        }

        void ObjectIO::onSave(BuilderNode* node) const
        {
            if(node)
            {
                for(auto variableMapping : m_ExposedVariables)
                {
                    ExposedVariable* variable = &variableMapping.second;

                    if(variable)
                    {
                        if(variable->isExposed)
                        {
                            if(variable->isPointer)
                            {
                                // If the variable is a pointer, we only add it to the node chain
                                // if it can be cast to another ObjectIO. If it can, then we add
                                // it as a new child and let it's onSave build itself.

                                ObjectIO* buildableChild = void_cast<ObjectIO*>(variable->data);

                                if(buildableChild)
                                {
                                    // Add a new node for this child, and envoke it's onSave so it can build itself
                                    buildableChild->onSave(node->addChild(variable->name, variable->type, ""));
                                }
                            }
                            else
                            {
                                ObjectIO* io = void_cast<ObjectIO*>(variable->data);

                                if(io)
                                {
                                    io->onSave(node->addChild(variable->name, variable->type, ""));
                                }
                            }
                        }
                        else
                        {
                            if(!variable->isPointer)
                            {
                                node->addChild(variable->name, variable->type, OcularString->toString(variable->type, variable->data, true));
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