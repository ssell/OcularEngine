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
// Statics
//------------------------------------------------------------------------------------------

static std::vector<SceneObject*> g_Objects;
static std::shared_ptr<BVHSceneTree> g_SceneTree = std::make_shared<BVHSceneTree>();

//------------------------------------------------------------------------------------------
// Forward Declarations
//------------------------------------------------------------------------------------------

void populateObjects();

//------------------------------------------------------------------------------------------
// Test Methods
//------------------------------------------------------------------------------------------

TEST(BVHSceneTree, AddRemoveObjects)
{
    populateObjects();

    std::vector<SceneObject*> allObjects;
    SceneObject* objectA = new SceneObject();
    
    g_SceneTree->addObject(objectA);
    g_SceneTree->getAllObjects(allObjects);

    EXPECT_EQ(allObjects.size(), (g_Objects.size() + 1));

    g_SceneTree->removeObject(objectA);
    g_SceneTree->getAllObjects(allObjects);

    EXPECT_EQ(allObjects.size(), g_Objects.size());
}

TEST(BVHSceneTree, GetAllObjects)
{
    populateObjects();
    
    std::vector<SceneObject*> allObjects;
    g_SceneTree->getAllObjects(allObjects);

    EXPECT_EQ(allObjects.size(), g_Objects.size());
}

TEST(BVHSceneTree, GetAllVisibleObjects)
{
    populateObjects();

    std::vector<SceneObject*> visibleObjects;

    Frustum frustum;
    frustum.setView(Vector3f(0.0f, 0.0f, 2.0f), Vector3f::Forward(), Vector3f::Up());
    frustum.setProjection(-3.0f, 3.0f, -3.0f, 3.0f, 1.0f, 10.0f);
    frustum.rebuild();

    g_SceneTree->getAllVisibleObjects(frustum, visibleObjects);

    EXPECT_EQ(visibleObjects.size(), 4);

    // Note: The frustum does not currently correctly handle orthographic projections.
    // If the frustum was a proper ortho projection (box), then visibleObjects' size
    // would be 3. But since it is currently doing a perspective projection, then
    // the right-plane is clipping one of objects that would otherwise be culled.
}

TEST(BVHSceneTree, GetIntersectionsRay)
{
    populateObjects();
    EXPECT_FALSE(true);
}

TEST(BVHSceneTree, GetIntersectionsSphere)
{
    populateObjects();
    EXPECT_FALSE(true);

}

TEST(BVHSceneTree, GetIntersectionsAABB)
{
    populateObjects();
    EXPECT_FALSE(true);
}

//------------------------------------------------------------------------------------------
// Other Methods
//------------------------------------------------------------------------------------------

void populateObjects()
{
    if(g_Objects.empty())
    {
        g_Objects.push_back(new SceneObject());
        g_Objects.push_back(new SceneObject());
        g_Objects.push_back(new SceneObject());
        g_Objects.push_back(new SceneObject());
        g_Objects.push_back(new SceneObject());
        g_Objects.push_back(new SceneObject());
    
        g_Objects[0]->boundsAABB = BoundsAABB(Vector3f(-6.0f, -1.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
        g_Objects[1]->boundsAABB = BoundsAABB(Vector3f(-3.0f,  3.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));
        g_Objects[2]->boundsAABB = BoundsAABB(Vector3f(-2.0f, -4.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));
        g_Objects[3]->boundsAABB = BoundsAABB(Vector3f( 2.0f,  0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
        g_Objects[4]->boundsAABB = BoundsAABB(Vector3f( 6.0f,  6.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
        g_Objects[5]->boundsAABB = BoundsAABB(Vector3f( 6.0f,  2.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));

        g_SceneTree->addObjects(g_Objects);
        g_SceneTree->restructure();
    }
}
