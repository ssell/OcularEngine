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

#pragma once
#ifndef __H__OCULAR_CORE_BUILDER_NODE__H__
#define __H__OCULAR_CORE_BUILDER_NODE__H__

#include "Utilities/Types.hpp"
#include "Utilities/StringUtils.hpp"

#include <string>
#include <vector>
#include <unordered_map>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class BuilderNode
         * \brief Generic node system used for loading and saving SceneObjects and their components.
         *
         * A BuilderNode chain is employed when reading from and writing to various Ocular file types
         * including: Scene (.oscene), SceneObject (.opref), and Material (.omat). These nodes allow
         * for a generic pattern in which both primitive and custom types may be used to specify the
         * contents of an object.
         */
        class BuilderNode
        {
        public:

            BuilderNode(BuilderNode* parent, std::string const& name, std::string const& type, std::string const& value);
            ~BuilderNode();

            //--------------------------------------------------------------------

            /**
             * \return The name of the variable stored in this node.
             */
            std::string const& getName() const;

            /**
             * \return The string representation of the value of the variable stored in this node.
             */
            std::string const& getValue() const;

            /**
             * \return The string representation of the type of variable stored in this node.
             */
            std::string const& getType() const;

            //--------------------------------------------------------------------

            /**
             * \return The parent of this node. If no parent, returns nullptr.
             */
            BuilderNode const* getParent() const;

            /**
             * Adds a new child to this node.
             *
             * If a child already exists with the specified name, that child will be
             * overwritten by the new child.
             *
             * \param[in] name
             * \param[in] type
             * \param[in] value
             */
            BuilderNode* addChild(std::string const& name, std::string const& type, std::string const& value);

            /**
             * Attempts to retrieve the child with the specified name.
             *
             * \param[in] name
             * \return Child with the specified name. If no such child exists, returns nullptr.
             */
            BuilderNode const* getChild(std::string const& name) const;

            /**
             * Finds all children with the specified string in their name.
             * \note Names are unique, so this searches for any children whose name contains the string.
             *
             * \param[out] children
             * \param[in]  name
             */
            void findChildrenByName(std::vector<BuilderNode*>& children, std::string const& name) const;

            /**
             * Finds all children whose type matches the specified string.
             *
             * \param[out] children
             * \param[in]  type
             */
            void findChildrenByType(std::vector<BuilderNode*>& children, std::string const& type) const;

            /**
             * Adds references to all children into the provided vector container.
             * \param[out] children
             */
            void getAllChildren(std::vector<BuilderNode*>& children) const;

            /**
             * Returns number of child nodes.
             */
            uint32_t getNumChildren() const;

        protected:

        private:

            BuilderNode* m_Parent;

            std::string m_Name;
            std::string m_Value;
            std::string m_Type;

            std::unordered_map<std::string, BuilderNode*> m_ChildMap;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif