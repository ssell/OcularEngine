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

#include "Tests/Performance/BVHSceneTreeTest.hpp"
#include "Scene/BVHSceneTree.hpp"
#include "Math/Random/MersenneTwister19937.hpp"
#include "OcularEngine.hpp"

using namespace Ocular::Core;
using namespace Ocular::Math;
using namespace Ocular::Math::Random;

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Tests
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BVHSceneTreeTest::BVHSceneTreeTest()
            : ATest("BVHSceneTreeTest")
        {
        
        }

        BVHSceneTreeTest::~BVHSceneTreeTest()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BVHSceneTreeTest::run()
        {
            //double elapsedConstruction10 = 0.0;
            //double elapsedConstruction100 = 0.0;
            double elapsedConstruction1000 = 0.0;
            //double elapsedConstruction10000 = 0.0;
            
            //buildTree(10, elapsedConstruction10);
           // OcularLogger->info("BVH[10]:    ", elapsedConstruction10, "ms");

            //buildTree(100, elapsedConstruction100);
            //OcularLogger->info("BVH[100]:   ", elapsedConstruction100, "ms");

            buildTree(1000, elapsedConstruction1000);
            OcularLogger->info("BVH[1000]:  ", elapsedConstruction1000, "ms");

            //buildTree(10000, elapsedConstruction10000);
            //OcularLogger->info("BVH[10000]: ", elapsedConstruction10000, "ms");

            ATest::run();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void BVHSceneTreeTest::buildTree(uint32_t numObjects, double& elapsed)
        {
            std::vector<SceneObject*> objects;
            buildObjects(numObjects, objects);

            BVHSceneTree* tree = new BVHSceneTree();

            //------------------------------------------------------------
            // Build the tree and time it

            tree->addObjects(objects);

            uint64_t start = OcularEngine.Clock()->getElapsedNS();
            tree->restructure();
            uint64_t end = OcularEngine.Clock()->getElapsedNS();

            elapsed = static_cast<double>((end - start)) * 1e-6;

            //------------------------------------------------------------
            // Clean up the tree and objects

            cleanTree(tree);
            cleanObjects(objects);
        }

        void BVHSceneTreeTest::buildObjects(uint32_t numObjects, std::vector<SceneObject*>& objects)
        {
            MersenneTwister19937 rng;

            objects.reserve(numObjects);

            for(uint32_t i = 0; i < numObjects; i++)
            {
                SceneObject* object = new SceneObject();
                object->boundsAABB.setCenter(Vector3f(rng.nextf(0.0f, 1000.0f), rng.nextf(0.0f, 1000.0f), rng.nextf(0.0f, 1000.0f)));
                object->boundsAABB.setExtents(Vector3f(rng.nextf(1.0f, 10.0f), rng.nextf(1.0f, 10.0f), rng.nextf(1.0f, 10.0f)));

                objects.push_back(object);
            }
        }

        void BVHSceneTreeTest::cleanTree(BVHSceneTree* tree)
        {
            tree->destroy();

            delete tree;
            tree = nullptr;
        }

        void BVHSceneTreeTest::cleanObjects(std::vector<SceneObject*>& objects)
        {
            for(auto object : objects)
            {
                delete object;
                object = nullptr;
            }

            objects.clear();
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}