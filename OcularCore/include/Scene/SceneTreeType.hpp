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

#pragma once
#ifndef __H__OCULAR_SCENE_TREE_TYPE__H__
#define __H__OCULAR_SCENE_TREE_TYPE__H__

#include <cstdint>

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
        enum class SceneTreeType : uint32_t
        {
            BoundingVolumeHierarchyCPU = 0x00,    ///< CPU-based implementation of a BVH tree. See BVHSceneTree class.
            BoundingVolumeHierarchyGPU = 0x01,    ///< GPU-based implementation of a BVH tree. Not yet implemented.
            QuadTreeCPU                = 0x02,    ///< CPU-based implementation of a Quad tree. Not yet implemented.
            QuadTreeGPU                = 0x03,    ///< GPU-based implementation of a Quad tree. Not yet implemented.
            OctTreeCPU                 = 0x04,    ///< CPU-based implementation of a Oct tree. Not yet implemented.
            OctTreeGPU                 = 0x05,    ///< GPU-based implementation of a Oct tree. Not yet implemented.
            BinarySpacePartitioningCPU = 0x06,    ///< CPU-based implementation of a BSP tree. Not yet implemented.
            BinarySpacePartitioningGPU = 0x07,    ///< GPU-based implementation of a BSP tree. Not yet implemented.
            Unknown  
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