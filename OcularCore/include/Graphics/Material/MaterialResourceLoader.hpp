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
         *
         *     <OcularMaterial>
         *         <ShaderProgram>
         *             <var name="Vertex" type="Shader" value="OcularCore/Shaders/Default" />
         *             <var name="Fragment" type="Shader" value="OcularCore/Shaders/Default" />
         *         </ShaderProgram>
         *         <Textures>
         *             <Texture>
         *                 <var name="Name" type="string" value="Diffuse" />
         *                 <var name="Value" type="Texture" value="OcularCore/Textures/Default" />
         *                 <var name="Register" type="int" value="0" />
         *         </Textures>
         *         <Uniforms>
         *             <Uniform>
         *                 <var name="Name" type="string" value="Albedo" />
         *                 <var name="Value" type="Color" value="0 1 0 1" />
         *                 <var name="Register" type="int" value="0" />
         *             </Uniform>
         *             <Uniform>
         *                 <var name="Name" type="string" value="Specular" />
         *                 <var name="Value" type="Color" value="1 1 1 1" />
         *                 <var name="Register" type="int" value="1" />
         *             </Uniform>
         *             <Uniform>
         *                 <var name="Name" type="string" value="Roughness" />
         *                 <var name="Value" type="float" value="0.5" />
         *                 <var name="Register" type="int" value="2" />
         *             </Uniform>
         *         </Uniforms>
         *         <RenderState>
         *             <var name="PrimitiveStyle" type="int" value="0" />
         *         </RenderState>
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
         * The following are valid shader name values:
         *
         *     Vertex, Geometry, Fragment, PreTessellation, PostTessellation
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
         * three parts: Name, Value, and Register.
         *
         * Valid name types are:
         *
         *     Ocular::Utils::TypeName<float>::name
         *     Ocular::Utils::TypeName<Ocular::Core::Color>::name
         *     Ocular::Utils::TypeName<Ocular::Math::Vector4f>::name
         *     Ocular::Utils::TypeName<Ocular::Math::Matrix3x3>::name
         *     Ocular::Utils::TypeName<Ocular::Math::Matrix4x4>::name
         *
         * Their values are specified in the following way:
         *
         *     <var name="Value" type="float" value="#" />
         *     <var name="Value" type="Vector4f" value="# # # #" />
         *     <var name="Value" type="Matrix3x3" value="# # # # # # # # #" />
         *     <var name="Value" type="Matrix4x4" value="# # # # # # # # # # # # # # # #" />
         * 
         * All numbers are converted to 32-bit floats.
         *
         * ## Render State ##
         *
         * Select parts of the Render State may be changed via Materials.
         * Currently, the following fields may be specified:
         *
         *     PrimitiveStyle: unsigned integer corresponding to the PrimitiveStyle enum definitions
         *
         * 
         */
        class MaterialResourceLoader : public Core::AResourceLoader
        {
        public:

            MaterialResourceLoader();
            virtual ~MaterialResourceLoader();

            virtual bool loadResource(Core::Resource* &resource, Core::File const& file, std::string const& mappingName) override;

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