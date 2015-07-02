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

#include "OcularEngine.hpp"
#include "Scene/BVHSceneTree.hpp"
#include "gtest/gtest.h"

using namespace Ocular::Core;
using namespace Ocular::Math;

//------------------------------------------------------------------------------------------
// Forward Declarations
//------------------------------------------------------------------------------------------

void populateObjects(std::vector<SceneObject*>& objects);

//------------------------------------------------------------------------------------------
// Test Methods
//------------------------------------------------------------------------------------------

TEST(BVHSceneTree, Construction)
{
    std::shared_ptr<BVHSceneTree> sceneTree = std::make_shared<BVHSceneTree>();
    std::vector<SceneObject*> sceneObjects;

    populateObjects(sceneObjects);

    sceneTree->addObjects(sceneObjects);
    sceneTree->restructure();
}

//------------------------------------------------------------------------------------------
// Other Methods
//------------------------------------------------------------------------------------------

void populateObjects(std::vector<SceneObject*>& objects)
{
    objects.push_back(new SceneObject());
    objects.push_back(new SceneObject());
    objects.push_back(new SceneObject());
    objects.push_back(new SceneObject());
    objects.push_back(new SceneObject());
    
    objects.push_back(new SceneObject());
    objects.push_back(new SceneObject());
    objects.push_back(new SceneObject());
    
    objects[0]->boundsAABB = BoundsAABB(Vector3f(-6.0f, -1.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    objects[1]->boundsAABB = BoundsAABB(Vector3f(-3.0f,  3.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));
    objects[2]->boundsAABB = BoundsAABB(Vector3f(-2.0f, -4.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));
    objects[3]->boundsAABB = BoundsAABB(Vector3f( 2.0f,  0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    objects[4]->boundsAABB = BoundsAABB(Vector3f( 6.0f,  6.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    
    objects[4]->boundsAABB = BoundsAABB(Vector3f( 7.0f,  6.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    objects[4]->boundsAABB = BoundsAABB(Vector3f( 6.0f,  7.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
    objects[4]->boundsAABB = BoundsAABB(Vector3f( 7.0f,  7.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
}
