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

#include "ObjectIO/BuilderNode.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //--------------------------------------------------------------------------------------
        // CONSTRUCTORS
        //--------------------------------------------------------------------------------------

        BuilderNode::BuilderNode(BuilderNode* parent, std::string const& name, std::string const& value, std::string const& type)
            : m_Parent(parent),
            m_Name(name),
            m_Value(value),
            m_Type(type)
        {

        }

        BuilderNode::~BuilderNode()
        {
            for(auto nodePair : m_ChildMap)
            {
                delete nodePair.second;
                nodePair.second = nullptr;
            }
        }

        //--------------------------------------------------------------------------------------
        // PUBLIC METHODS
        //--------------------------------------------------------------------------------------

        std::string const& BuilderNode::getName() const
        {
            return m_Name;
        }

        std::string const& BuilderNode::getValue() const
        {
            return m_Value;
        }

        std::string const& BuilderNode::getType() const
        {
            return m_Type;
        }

        BuilderNode const* BuilderNode::getParent() const
        {
            return m_Parent;
        }

        BuilderNode* BuilderNode::addChild(std::string const& name, std::string const& value, std::string const& type)
        {
            BuilderNode* result = nullptr;
            auto findPair = m_ChildMap.find(name);

            if(findPair != m_ChildMap.end())
            {
                delete findPair->second;
            }

            result = new BuilderNode(this, name, value, type);
            m_ChildMap[name] = result;

            return result;
        }

        BuilderNode const* BuilderNode::getChild(std::string const& name) const
        {
            BuilderNode* result = nullptr;
            auto findPair = m_ChildMap.find(name);

            if(findPair != m_ChildMap.end())
            {
                result = findPair->second;
            }

            return result;
        }

        void BuilderNode::getAllChildren(std::vector<BuilderNode*>& children) const
        {
            children.reserve(children.size() + m_ChildMap.size());

            for(auto childPair : m_ChildMap)
            {
                children.push_back(childPair.second);
            }
        }

        uint32_t BuilderNode::getNumChildren() const
        {
            return static_cast<uint32_t>(m_ChildMap.size());
        }

        //--------------------------------------------------------------------------------------
        // PROTECTED METHODS
        //--------------------------------------------------------------------------------------

        //--------------------------------------------------------------------------------------
        // PRIVATE METHODS
        //--------------------------------------------------------------------------------------
    }
}