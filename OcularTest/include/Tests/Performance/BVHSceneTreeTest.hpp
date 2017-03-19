/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_TEST_BVH_SCENE_TREE__H__
#define __H__OCULAR_TEST_BVH_SCENE_TREE__H__

#include "Tests/ATest.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Core
    {
        class SceneObject;
        class BVHSceneTree;
    }

    /**
     * \addtogroup Tests
     * @{
     */
    namespace Tests
    {
        /**
         * \class BVHSceneTreeTest
         *
         * This test is used to evalualte the runtime efficiency of the BVH SceneTree.
         *
         * The following features are tested:
         *
         *     - Tree Construction
         *     - Intersection Testing
         *
         * With the following number of objects:
         *
         *     - 10
         *     - 100
         *     - 1000
         *     - 10000
         *
         * Since this is a performance test, it may take a non-trivial amount
         * of time to complete, and thus should not be run as part of the 
         * normal testing package.
         *
         */
        class BVHSceneTreeTest : public ATest 
        {
        public:

            BVHSceneTreeTest();
            ~BVHSceneTreeTest();

            virtual void run() override;

        protected:

            void buildTree(uint32_t numObjects, double& elapsed);
            void buildObjects(uint32_t numObjects, std::vector<Core::SceneObject*>& objects);

            void cleanTree(Core::BVHSceneTree* tree);
            void cleanObjects(std::vector<Core::SceneObject*>& objects);

        private:
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