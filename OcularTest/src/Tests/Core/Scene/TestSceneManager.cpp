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

#include "OcularEngine.hpp"

#ifdef _DEBUG

#include "gtest/gtest.h"

using namespace Ocular::Core;

//------------------------------------------------------------------------------------------
// TEST FUNCTIONS
//------------------------------------------------------------------------------------------

TEST(SceneManager, GeneralObject)
{
    /**
     * Can't unit test much of the SceneManager/Scene, but can check the simple,
     * general object methods. The routine handling, SceneTree populating, etc.
     * will need to be tested via other methods.
     */

    //--------------------------------------------------------------------
    // Test Creation

    SceneObject* objectA = OcularScene->createObject("Object A");
    SceneObject* objectB = OcularScene->createObject("Object B");
    SceneObject* objectC = OcularScene->createObject("Object C");
    SceneObject* objectD = new SceneObject("Object D", objectA);
    
    if(objectA && objectB && objectC && objectD)
    {
        EXPECT_TRUE((objectA->getParent() == nullptr));
        EXPECT_TRUE((objectD->getParent() == objectA));

        EXPECT_TRUE((objectA->getName().compare("Object A") == 0));
        EXPECT_TRUE((objectB->getName().compare("Object B") == 0));

        //--------------------------------------------------------------------
        // Test Find

        OcularScene->createObject("Object B");

        SceneObject* objectAFind = OcularScene->findObject("Object A");
        SceneObject* objectBFind = OcularScene->findObject(objectB->getUUID());
        SceneObject* objectCFind = OcularScene->findObject("Object C");
        SceneObject* objectDFind = OcularScene->findObject("Object D");

        if(objectAFind && objectBFind && objectCFind && objectDFind)
        {
            std::vector<SceneObject*> allObjectB;
            OcularScene->findObjects("Object B", allObjectB);

            EXPECT_EQ(allObjectB.size(), 2);

            //--------------------------------------------------------------------
            // Test Removal

            // Remove A and it's child D

            OcularScene->destroyObject(objectA);

            EXPECT_TRUE(OcularScene->findObject("Object A") == nullptr);
            EXPECT_TRUE(OcularScene->findObject("Object D") == nullptr);

            // Remove multiple 'Object C' objects individually

            OcularScene->createObject("Object C");
            OcularScene->destroyObject(objectC->getUUID());

            EXPECT_TRUE(OcularScene->findObject("Object C") != nullptr);

            OcularScene->destroyObject("Object C");

            EXPECT_TRUE(OcularScene->findObject("Object C") == nullptr);

            // Remove multiple 'Object B' objects all at once

            OcularScene->destroyObject("Object B", true);

            EXPECT_TRUE(OcularScene->findObject("Object B") == nullptr);
        }
        else
        {
            FAIL();
        }
    }
    else
    {
        FAIL();
    }
}

TEST(SceneManager, DuplicateObject)
{
    EXPECT_TRUE(false);
}

#endif