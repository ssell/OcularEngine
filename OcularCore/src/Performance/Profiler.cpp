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

#include "Performance/Profiler.hpp"
#include "OcularEngine.hpp"

#include <iostream>
#include <regex>
#include <fstream>

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
            //------------------------------------------------------------
            // Check if block already exists

            if((m_CurrentNode->name.compare(name) == 0) &&
               (m_CurrentNode->segment.compare(segment) == 0))
            {
                // Requested to start a block that matches our current node.
                // We are in a recursive function.

                m_CurrentNode->recursiveDepth++;
                m_CurrentNode->totalCalls++;
            }
            else
            {
                const uint64_t time = OcularEngine.Clock()->getEpochNS();
                ProfilerNode* blockNode = nullptr;

                // Check if there is already a matching child

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
                    // No matching child, create a new one
                    blockNode = new ProfilerNode(m_CurrentNode, name, segment);
                    blockNode->blockDepth = m_CurrentNode->blockDepth + 1;

                    m_CurrentNode->children.emplace_back(blockNode);
                }

                //------------------------------------------------------------
                // Calculate the local elapsed time and then set 
                // the current node pointer to the node for the new block.

                m_CurrentNode->localElapsed += (time - m_CurrentNode->blockStart);

                m_CurrentNode = blockNode;
                m_CurrentNode->totalCalls++;
                m_CurrentNode->blockStart = OcularEngine.Clock()->getEpochNS();  // Recalculate current time as this method
            }                                                                   // most likely took > 0 NS to complete
        }

        void Profiler::endBlock()
        {
            if(m_CurrentNode->recursiveDepth == 0)
            {
                const uint64_t time = OcularEngine.Clock()->getEpochNS();

                m_CurrentNode->localElapsed += (time - m_CurrentNode->blockStart);
                m_CurrentNode->totalElapsed += m_CurrentNode->localElapsed;

                if(m_CurrentNode->parent)
                {
                    m_CurrentNode->parent->localElapsed += m_CurrentNode->localElapsed;
                    m_CurrentNode->parent->blockStart = time;
                    m_CurrentNode->localElapsed = 0;

                    m_CurrentNode = m_CurrentNode->parent;

                    if(!m_CurrentNode->parent)
                    {
                        // Special Case: reentered root node ("Ocular Engine")
                        m_CurrentNode->totalElapsed += m_CurrentNode->localElapsed;
                        m_CurrentNode->localElapsed = 0;
                    }
                }
                else
                {
                    // In root...
                    m_CurrentNode->localElapsed = 0;
                }
            }
            else
            {
                // We are inside a recursive function.
                m_CurrentNode->recursiveDepth--;
            }
        }

        void Profiler::printToConsole(bool prettify) const
        {
            std::stringstream logStream;
            createLogBuffer(logStream, prettify);

            std::cout << logStream.str();
        }

        void Profiler::printToTXT(std::string const& path) const
        {
            std::ofstream fstream(path, std::ios_base::out);

            if(fstream.is_open())
            {
                std::stringstream logStream;
                createLogBuffer(logStream, true);

                fstream << logStream.str();

                fstream.close();
            }           
        }

        void Profiler::printToHTML(std::string const& path) const
        {
            /// \todo Profiler output to HTML
            // Perhaps use https://github.com/ludo/jquery-treetable
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
            /**
             * Regex to search for match inbetween (but not including) ' ' and '('
             * Breaking the regex down as I will most likely forget what is happening:
             * 
             *           \b : Selection starts on a word boundary
             *     ([^\s])+ : Selection contains 1 or more non-space characters
             *      ?(?=\() : Selection ends with a '(' but does not include it (using lookahead)
             */

            static const std::regex regex("\\b([^\\s])+?(?=\\()");

            std::string result = name;
            std::smatch regexMatch;

            if(std::regex_search(name.begin(), name.end(), regexMatch, regex))
            {
                result = regexMatch[0];
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}