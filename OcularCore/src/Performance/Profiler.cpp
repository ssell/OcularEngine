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

#include "Performance/Profiler.hpp"
#include "OcularEngine.hpp"
#include <iostream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Profiler::Profiler()
        {
            m_RootNode = new ProfilerNode(nullptr, "Ocular Engine", "");
            m_RootNode->totalCalls++;
            m_RootNode->blockStart = OcularEngine.Clock()->getEpochNS();
            
            m_CurrentNode = m_RootNode;
        }

        Profiler::~Profiler()
        {
            destroy();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Profiler::beginBlock(std::string const& name, std::string const& segment)
        {
            const uint64_t time = OcularEngine.Clock()->getEpochNS();        // Get time as soon as this method starts

            //------------------------------------------------------------
            // Check if block already exists

            ProfilerNode* blockNode = nullptr;

            for(auto child : m_CurrentNode->children)
            {
                if((name.compare(child->name) == 0) &&
                   (segment.compare(child->segment) == 0))
                {
                    blockNode = child;
                    break;
                }
            }

            if(!blockNode)
            {
                blockNode = new ProfilerNode(m_CurrentNode, name, segment);
                blockNode->blockDepth = m_CurrentNode->blockDepth + 1;

                m_CurrentNode->children.emplace_back(blockNode);
            }

            //------------------------------------------------------------
            // Calculate the local elapsed time and then set 
            // the current node pointer to the node for the new block.

            m_CurrentNode->localElapsed = (time - m_CurrentNode->blockStart);

            m_CurrentNode = blockNode;
            m_CurrentNode->totalCalls++;
            m_CurrentNode->blockStart = OcularEngine.Clock()->getEpochNS();  // Recalculate current time as this method
        }                                                                    // most likely took > 0 NS to complete

        void Profiler::endBlock()
        {
            const uint64_t time = OcularEngine.Clock()->getEpochNS();        // Get time as soon as this method starts

            m_CurrentNode->localElapsed += (time - m_CurrentNode->blockStart);
            m_CurrentNode->totalElapsed += m_CurrentNode->localElapsed;

            if(m_CurrentNode->parent)
            {
                m_CurrentNode->parent->localElapsed += m_CurrentNode->localElapsed;
                m_CurrentNode->parent->blockStart = time;
                m_CurrentNode->localElapsed  = 0;
                
                m_CurrentNode = m_CurrentNode->parent;

                if(m_CurrentNode->parent == nullptr)
                {
                    // Special Case: reentered root node ("Ocular Engine")
                    m_CurrentNode->totalElapsed += m_CurrentNode->localElapsed;
                    m_CurrentNode->localElapsed  = 0;
                }
            }
            else
            {
                m_CurrentNode->localElapsed  = 0;
            }
        }

        void Profiler::printToConsole(bool prettify) const
        {
            std::stringstream logStream;
            createLogBuffer(logStream, prettify);

            std::cout << logStream.str();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Profiler::destroy()
        {
            destroyNode(m_RootNode);
        }

        void Profiler::destroyNode(ProfilerNode* node) const
        {
            if(node)
            {
                for(auto child : node->children)
                {
                    destroyNode(child);
                }

                delete node;
                node = nullptr;
            }
        }

        void Profiler::createLogBuffer(std::stringstream& stream, bool prettify) const
        {
            stream << "\n*** Ocular Engine Execution Profiler ***\n";
            createLogForNode(m_RootNode, stream, prettify);
        }
         
        void Profiler::createLogForNode(ProfilerNode* node, std::stringstream& stream, bool prettify) const
        {
            if(node)
            {
                for(uint32_t i = 0; i < node->blockDepth; i++)
                {
                    stream << "  ";
                }

                std::string name = (prettify == true) ? prettifyName(node->name) : node->name;
                
                stream << "- " << name << " ";

                if(node->segment.size() > 0)
                {
                    stream << "\"" << node->segment << "\" ";
                }

                const float elapsedMS = static_cast<float>(node->totalElapsed) * 1e-6f;
                const float averageMS = elapsedMS / static_cast<float>(node->totalCalls);

                stream << "[" << node->totalCalls << "] ";
                stream << "[" << elapsedMS << "ms] ";
                stream << "[" << averageMS << "ms]\n";

                for(auto child : node->children)
                {
                    createLogForNode(child, stream, prettify);
                }
            }
        }

        std::string Profiler::prettifyName(std::string const& name) const
        {
            return name;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}