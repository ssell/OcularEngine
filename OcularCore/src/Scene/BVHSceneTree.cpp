/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Scene/BVHSceneTree.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BVHSceneTree::BVHSceneTree()
        {
			m_Root = nullptr;
        }

        BVHSceneTree::~BVHSceneTree()
        {
			destroy();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BVHSceneTree::restructure()
        {
			if(rebuildNeeded())
			{
				//--------------------------------------------------------------------
				// Destroy the tree structure but preserve the objects

				destroyNode(m_Root);
				m_Root = nullptr;

				//--------------------------------------------------------------------
				// Add any new objects

				uint32_t numNewObjects = m_NewObjects.size();
				uint32_t numTotalObjects = m_AllObjects.size() + numNewObjects;

				if(numNewObjects > 0)
				{
					m_AllObjects.reserve(numTotalObjects);
				}

				//--------------------------------------------------------------------
				// Build the new tree

				build();
			}
        }
        
        void BVHSceneTree::destroy()
        {
			if(m_Root)
			{
				destroyNode(m_Root);
				m_Root = nullptr;

				m_NewObjects.clear();
				m_AllObjects.clear();
			}
        }
        
        void BVHSceneTree::addObject(SceneObject* object)
        {
            if(object)
            {
                m_NewObjects.emplace_back(object);
            }
        }

        void BVHSceneTree::addObjects(std::vector<SceneObject*> const& objects)
        {
            for(auto object : objects)
            {
                if(object)
                {
                    m_NewObjects.emplace_back(object);
                }
            }
        }
        
        void BVHSceneTree::removeObject(SceneObject* object)
        {
        
        }
        
        void BVHSceneTree::getAllObjects(std::vector<SceneObject*>& objects) const
        {
        
        }
        
        void BVHSceneTree::getAllVisibleObjects(std::vector<SceneObject*>& objects) const
        {
        
        }

        void BVHSceneTree::getAllActiveObjects(std::vector<SceneObject*>& objects) const
        {
        
        }

        void BVHSceneTree::getIntersections(Math::Ray const& ray, std::vector<SceneObject*>& objects) const
        {
        
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool BVHSceneTree::rebuildNeeded() const
        {
            bool result = false;

            if(m_NewObjects.size() > 0)
            {
                result = true;
            }
            else
            {
                
            }

            return result;
        }

		void BVHSceneTree::destroyNode(BVHSceneNode* node) const
		{
			if(node)
			{
				destroyNode(node->left);
				destroyNode(node->right);

				delete node;
				node = nullptr;
			}
		}

		//----------------------------------------------------------------------
		// Build Methods
		//----------------------------------------------------------------------

		void BVHSceneTree::build()
		{
			m_Root = createRootNode();

			if(!m_AllObjects.empty())
			{
				const uint32_t numLeafs = m_AllObjects.size();
				const uint32_t numInternals = numLeafs - 1;

				// ...
			}
		}

		BVHSceneNode* BVHSceneTree::createRootNode() const
		{
			BVHSceneNode* result = new BVHSceneNode();

			result->parent = nullptr;
			result->left   = nullptr;
			result->right  = nullptr;
			result->type   = SceneNodeType::Root;

			return result;
		}

		BVHSceneNode* BVHSceneTree::createInternalNode(BVHSceneNode* parent) const
		{
			BVHSceneNode* result = new BVHSceneNode();

			result->parent = parent;
			result->left   = nullptr;
			result->right  = nullptr;
			result->type   = SceneNodeType::Internal;

			return result;
		}

		BVHSceneNode* BVHSceneTree::createLeafNode(BVHSceneNode* parent) const
		{
			BVHSceneNode* result = new BVHSceneNode();

			result->parent = parent;
			result->left   = nullptr;
			result->right  = nullptr;
			result->type   = SceneNodeType::Leaf;

			return result;
		}

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}