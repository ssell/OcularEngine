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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_MATERIAL_RESOURCE_LOADER__H__
#define __H__OCULAR_GRAPHICS_MATERIAL_RESOURCE_LOADER__H__

#include "Resources/ResourceLoader.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        class ShaderProgram;

        /**
         * \class MaterialResourceLoader
         * \brief Creates Material objects from Ocular Material files (.omat)
         *
         * ## Overview ##
         *
         * This loader is responsible for creating Material objects from the XML-based Ocular Material files (.omat).
         * For a full description of the Ocular Material file format, see the Materials section of the manual.
         *
         * But as the manual does not yet exist, here is an example of the XML:
         *
         *     <OcularMaterial>
         *         <ShaderProgram>
         *             <Vertex>
         *                 <Path>Shaders/OcularFlat</Path>
         *             </Vertex>
         *             <Fragment>
         *                 <Path>Shaders/OcularFlat</Path>
         *             </Fragment>
         *         </ShaderProgram>
         *         <Textures>
         *             <Texture>
         *                 <Path>Textures/Grass</Path>
         *                 <Name>Grass</Name>
         *                 <Register>0</Register>
         *             </Texture>
         *             <Texture>
         *                 <Path>Textures/GrassBump</Path>
         *                 <Name>Grass Bump Map</Name>
         *                 <Register>1</Register>
         *             </Texture>
         *             <Texture>
         *                 <Path>Texture/GrassSpecular</Path>
         *                 <Name>Grass Specular Map</Name>
         *                 <Register>2</Register>
         *             </Texture>
         *         </Textures>
         *         <Uniforms>
         *             <Uniform>
         *                 <Type>Vector4</Type>
         *                 <Name>Offset</Name>
         *                 <Register>0</Register>
         *                 <Value>1.0 0.5 3.0 0.0</Value>
         *             </Uniform>
         *             <Uniform>
         *                 <Type>Float</Type>
         *                 <Name>Fade</Name>
         *                 <Register>1</Register>
         *                 <Value>0.5</Value>
         *             </Uniform>
         *             <Uniform>
         *                 <Type>Matrix3x3</Type>
         *                 <Name>Identity3x3</Name>
         *                 <Register>2</Register>
         *                 <Value>1.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 1.0</Value>
         *             </Uniform>
         *             <Uniform>
         *                 <Type>Matrix3x3</Type>
         *                 <Name>Rot3x3</Name>
         *                 <Register>3</Register>
         *                 <Value>
         *                     0.38 1.0 0.0
         *                     1.97 3.0 0.5
         *                     0.01 0.9 1.0
         *                 </Value>
         *             </Uniform>
         *         </Uniforms>
         *     </OcularMaterial>
         *
         * The above XML can be broken into three major sections: ShaderProgram, Textures, and Uniforms.
         *
         * ## ShaderProgram ##
         *
         * The ShaderProgram is split into individual 'Shader' sections that simply specify which Shader
         * resource file defines them. Note that these resource files may be uncompiled files (.hlsl, .glsl, etc.),
         * pre-compiled binaries, or a mix of the two.
         *
         * Internally, a request is done for the ShaderProgram that matches the specified file and then
         * the specific shader is retrieved. For example, for the above Vertex shader we would:
         *
         *     ShaderProgram* program = OcularResources->getResource<ShaderProgram>("Shaders/OcularFlat");
         *
         *     if(program)
         *     {
         *         material->setVertexShader(program->getVertexShader());
         *     }
         *
         * The following are valid shader stage tags:
         *
         *     <Vertex>
         *     <Geometry>
         *     <Fragment> or <Pixel>
         *     <PreTessellation> or <Hull>
         *     <PostTessellation> or <Domain>
         *
         * ## Textures ##
         * 
         * This defines all textures to be bound to in the Material. 
         *
         * The three required bits of information (path, name, and register) directly map to what the
         * Material::setTexture method requires as input parameters.
         *
         * Note that 'Name' is independent of the actual Resource's name. This is used for certain
         * graphics APIs that bind based on name instead of register. So, we could have the following:
         *
         *    Resource Source: Texture/Grass
         *    Resource Name: "Grass"
         *    Material Binding Name: "GrassDiffuse"
         *
         * In the Material file we are specifying the 'Material Binding Name' and not the 'Resource Name.'
         * Of course, it is perfectly acceptable that these names match, but it is not required.
         *
         * ## Uniforms ##
         *
         * Here the individual Uniforms for the material are specified. Each Uniform is composed of 
         * three parts: Type, Name, and Value.
         *
         * Valid types are:
         *
         *     Float
         *     Vector4
         *     Matrix3x3
         *     Matrix4x4
         *
         * Their values are specified in the following way:
         *
         *         Float: <Value>#</Value>
         *
         *       Vector4: <Value># # # #</Value>
         *
         *     Matrix3x3: <Value># # #  # # #  # # #</Value>
         *
         *                or
         *
         *                <Value>
         *                    # # #
         *                    # # #
         *                    # # #
         *                </Value>
         *                       
         *     Matrix4x4: <Value># # # #  # # # #  # # # #  # # # #</Value>
         *
         *                or
         *
         *                <Value>
         *                    # # # #
         *                    # # # #
         *                    # # # #
         *                    # # # #
         *                </Value>
         * 
         * All numbers are converted to 32-bit floats.
         */
        class MaterialResourceLoader : public Core::AResourceLoader
        {
        public:

            MaterialResourceLoader();
            virtual ~MaterialResourceLoader();

            virtual bool loadResource(Core::Resource* &resource, Core::File const& file) override;

        protected:

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