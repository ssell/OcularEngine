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

#include "OcularEngine.hpp"
#include "Scene/BVHSceneTree.hpp"

#ifdef _DEBUG

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
bool contains(std::vector<SceneObject*> const& vector, SceneObject const* obj);

//------------------------------------------------------------------------------------------
// Test Methods
//------------------------------------------------------------------------------------------

TEST(BVHSceneTree, AddRemoveObjects)
{
    populateObjects();

    std::vector<SceneObject*> allObjects;
    SceneObject* objectA = new SceneObject();
    
    g_SceneTree->addObject(objectA);
    g_SceneTree->restructure();
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
    frustum.setProjectionOrthographic(-3.0f, 3.0f, -3.0f, 3.0f, 1.0f, 10.0f);
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
    
    const Ray rayA(Vector3f(-10.0f, 0.0f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f));    // Should hit 3 (0,3,4)
    const Ray rayB(Vector3f(6.0f, 10.0f, 0.0f),  Vector3f(0.0f, -1.0f, 0.0f));   // Should hit 2 (5,4)
    const Ray rayC(Vector3f(2.0f, 0.0f, 5.0f),   Vector3f(0.0f, 0.0f, -1.0f));   // Should hit 1 (3)
    const Ray rayD(Vector3f(0.0f, 0.0f, 5.0f),   Vector3f(1.0f, 0.0f, 0.0f));    // Should hit 0

    std::vector<SceneObject*> hitsA;
    std::vector<SceneObject*> hitsB;
    std::vector<SceneObject*> hitsC;
    std::vector<SceneObject*> hitsD;

    g_SceneTree->getIntersections(rayA, hitsA);
    g_SceneTree->getIntersections(rayB, hitsB);
    g_SceneTree->getIntersections(rayC, hitsC);
    g_SceneTree->getIntersections(rayD, hitsD);

    EXPECT_EQ(hitsA.size(), 3);
    EXPECT_EQ(hitsB.size(), 2);
    EXPECT_EQ(hitsC.size(), 1);
    EXPECT_EQ(hitsD.size(), 0);
    
    EXPECT_EQ(hitsA[0], g_Objects[0]);    // Check individual indices since order matters with
    EXPECT_EQ(hitsA[1], g_Objects[3]);    // the ray intersection test.
    EXPECT_EQ(hitsA[2], g_Objects[4]);
    
    EXPECT_EQ(hitsB[0], g_Objects[5]);
    EXPECT_EQ(hitsB[1], g_Objects[4]);
    
    EXPECT_EQ(hitsC[0], g_Objects[3]);
}

TEST(BVHSceneTree, GetIntersectionsSphere)
{
    populateObjects();

    const BoundsSphere sphereA(Vector3f(0.0f, 0.0f, 0.0f), 3.0f);    // Should hit 3 (1,2,3)
    const BoundsSphere sphereB(Vector3f(-4.0f, -2.0f, 0.0f), 2.0f);  // Should hit 2 (0,2)
    const BoundsSphere sphereC(Vector3f(2.0f, 0.0f, 0.0f), 2.0f);    // Should hit 2 (3,4) (completely contain 3)
    const BoundsSphere sphereD(Vector3f(6.0f, 8.0f, 1.0f), 1.0f);    // Should hit 1 (5)
    const BoundsSphere sphereE(Vector3f(0.0f, 0.0f, 0.0f), 0.5f);    // Should hit 0

    std::vector<SceneObject*> hitsA;
    std::vector<SceneObject*> hitsB;
    std::vector<SceneObject*> hitsC;
    std::vector<SceneObject*> hitsD;
    std::vector<SceneObject*> hitsE;

    g_SceneTree->getIntersections(sphereA, hitsA);
    g_SceneTree->getIntersections(sphereB, hitsB);
    g_SceneTree->getIntersections(sphereC, hitsC);
    g_SceneTree->getIntersections(sphereD, hitsD);
    g_SceneTree->getIntersections(sphereE, hitsE);

    EXPECT_EQ(hitsA.size(), 3);
    EXPECT_EQ(hitsB.size(), 2);
    EXPECT_EQ(hitsC.size(), 2);
    EXPECT_EQ(hitsD.size(), 1);
    EXPECT_EQ(hitsE.size(), 0);
    
    EXPECT_TRUE(contains(hitsA, g_Objects[1]));
    EXPECT_TRUE(contains(hitsA, g_Objects[2]));
    EXPECT_TRUE(contains(hitsA, g_Objects[3]));
    
    EXPECT_TRUE(contains(hitsB, g_Objects[0]));
    EXPECT_TRUE(contains(hitsB, g_Objects[2]));
    
    EXPECT_TRUE(contains(hitsC, g_Objects[3]));
    EXPECT_TRUE(contains(hitsC, g_Objects[4]));
    
    EXPECT_TRUE(contains(hitsD, g_Objects[5]));
}

TEST(BVHSceneTree, GetIntersectionsAABB)
{
    populateObjects();
    
    const BoundsAABB boundsA(Vector3f(0.0f, 0.0f, 0.0f),  Vector3f(3.0f, 3.0f, 3.0f));    // Should hit 3 (1,2,3)
    const BoundsAABB boundsB(Vector3f(-6.0f, 1.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));    // Should hit 2 (0,1)
    const BoundsAABB boundsC(Vector3f(6.0f, 2.0f, 0.0f),  Vector3f(1.0f, 1.0f, 1.0f));    // Should hit 1 (4)
    const BoundsAABB boundsD(Vector3f(0.0f, 0.0f, 0.0f),  Vector3f(0.5f, 0.5f, 0.5f));    // Should hit 0

    std::vector<SceneObject*> hitsA;
    std::vector<SceneObject*> hitsB;
    std::vector<SceneObject*> hitsC;
    std::vector<SceneObject*> hitsD;

    g_SceneTree->getIntersections(boundsA, hitsA);
    g_SceneTree->getIntersections(boundsB, hitsB);
    g_SceneTree->getIntersections(boundsC, hitsC);
    g_SceneTree->getIntersections(boundsD, hitsD);

    EXPECT_EQ(hitsA.size(), 3);
    EXPECT_EQ(hitsB.size(), 2);
    EXPECT_EQ(hitsC.size(), 1);
    EXPECT_EQ(hitsD.size(), 0);
    
    EXPECT_TRUE(contains(hitsA, g_Objects[1]));
    EXPECT_TRUE(contains(hitsA, g_Objects[2]));
    EXPECT_TRUE(contains(hitsA, g_Objects[3]));
    
    EXPECT_TRUE(contains(hitsB, g_Objects[0]));
    EXPECT_TRUE(contains(hitsB, g_Objects[1]));
    
    EXPECT_TRUE(contains(hitsC, g_Objects[4]));
}

//------------------------------------------------------------------------------------------
// Other Methods
//------------------------------------------------------------------------------------------

void populateObjects()
{
    if(g_Objects.empty())
    {
        g_Objects.push_back(new SceneObject("Object 0"));
        g_Objects.push_back(new SceneObject("Object 1"));
        g_Objects.push_back(new SceneObject("Object 2"));
        g_Objects.push_back(new SceneObject("Object 3"));
        g_Objects.push_back(new SceneObject("Object 4"));
        g_Objects.push_back(new SceneObject("Object 5"));
    
        g_Objects[0]->boundsAABB = BoundsAABB(Vector3f(-6.0f, -1.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
        g_Objects[1]->boundsAABB = BoundsAABB(Vector3f(-3.0f,  3.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));
        g_Objects[2]->boundsAABB = BoundsAABB(Vector3f(-2.0f, -4.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));
        g_Objects[3]->boundsAABB = BoundsAABB(Vector3f( 2.0f,  0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
        g_Objects[4]->boundsAABB = BoundsAABB(Vector3f( 6.0f,  2.0f, 0.0f), Vector3f(2.0f, 2.0f, 2.0f));
        g_Objects[5]->boundsAABB = BoundsAABB(Vector3f( 6.0f,  6.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));

        g_SceneTree->addObjects(g_Objects);
        g_SceneTree->restructure();
    }
}

bool contains(std::vector<SceneObject*> const& vector, SceneObject const* obj)
{
    bool result = false;
    auto find = std::find(vector.begin(), vector.end(), obj);

    if(find != vector.end())
    {
        result = true;
    }

    return result;
}

#endif