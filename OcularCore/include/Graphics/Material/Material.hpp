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

#pragma
#ifndef __H__OCULAR_GRAPHICS_GRAPHICS_MATERIAL_H__
#define __H__OCULAR_GRAPHICS_GRAPHICS_MATERIAL_H__

#include "Resources/Resource.hpp"
#include "Math/Matrix4x4.hpp"

#include <string>
#include <unordered_map>

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
        class Texture;
        class VertexShader;
        class GeometryShader;
        class FragmentShader;
        class PreTessellationShader;
        class PostTessellationShader;

        /**
         * \class Material
         */
        class Material : public Core::Resource
        {
        public:

            Material();
            ~Material();

            virtual void bind();
            virtual void unbind();

            virtual void unload() override;

            //------------------------------------------------------------
            // Texture Methods
            //------------------------------------------------------------

            /**
             * Assigns a texture to a specific input register for use by the shaders
             * that are part of this material. All textures are automatically bound
             * to all relevant (non-NULL) shader stages.
             *
             * Depending on the underlying graphics API, and shader implementation language,
             * some may make use of the index or the name or both. 
             *
             * Note that some texture assignment indices and names are reserved by the engine.
             * See ------- for a list of all reserved locations.
             *
             * \param[in] index   The index to bind the texture to. This can be on the range of
             *                    0 to (GraphicsDriver::getMaxBoundTextures - 1). Note that indices
             *                    do not have to be sequential. For example, you may have use 0, 1, 3, 79.
             * \param[in] name    The name to bind the texture to.
             * \param[in] texture The texture to bind.
             *
             * \return TRUE if texture was successfully set. May fail due to invalid index value.
             */
            virtual bool setTexture(uint32_t index, std::string const& name, Texture* texture);

            /**
             * Retrieves the texture stored at the specified identifier.
             * \param[in] index Index of the texture to retrieve.
             */
            Texture* getTexture(uint32_t index) const;

            /**
             * Removes the texture at the specified index from this material.
             * \param[in] index
             */
            virtual void removeTexture(uint32_t index);

            //------------------------------------------------------------
            // Shader Methods
            //------------------------------------------------------------

            /**
             * Sets the vertex shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a vertex shader.
             */
            bool setVertexShader(std::string const& name);

            /**
             * Sets the vertex shader used by this Material.
             * \param[in] shader Pointer to the shared vertex shader to use.
             */
            void setVertexShader(VertexShader* shader);

            /**
             * Sets the geometry shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a geometry shader.
             */
            bool setGeometryShader(std::string const& name);

            /**
             * Sets the geometry shader used by this Material.
             * \param[in] shader Pointer to the shared geometry shader to use.
             */
            void setGeometryShader(GeometryShader* shader);

            /**
             * Sets the fragment shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a fragment shader.
             */
            bool setFragmentShader(std::string const& name);

            /**
             * Sets the fragment shader used by this Material.
             * \param[in] shader Pointer to the shared fragment shader to use.
             */
            void setFragmentShader(FragmentShader* shader);

            /**
             * Sets the pre-tessellation shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a pre-tessellation shader.
             */
            bool setPreTessellationShader(std::string const& name);

            /**
             * Sets the pre-tessellation shader used by this Material.
             * \param[in] shader Pointer to the shared pre-tessellation shader to use.
             */
            void setPreTessellationShader(PreTessellationShader* shader);

            /**
             * Sets the post-tessellation shader used by this Material.
             *
             * \param[in] name Name of the shader to use.
             * \return Returns TRUE if the shader was successfully set. May fail if no
             *         ShaderProgram with a matching name was discovered, or if that
             *         ShaderProgram did not contain a post-tessellation shader.
             */
            bool setPostTessellationShader(std::string const& name);

            /**
             * Sets the post-tessellation shader used by this Material.
             * \param[in] shader Pointer to the shared post-tessellation shader to use.
             */
            void setPostTessellationShader(PostTessellationShader* shader);

            /**
             * \return The vertex shader used by this material. May be NULL if no valid shader is set.
             */
            VertexShader* getVertexShader() const;

            /**
             * \return The geometry shader used by this material. May be NULL if no valid shader is set.
             */
            GeometryShader* getGeometryShader() const;

            /**
             * \return The fragment shader used by this material. May be NULL if no valid shader is set.
             */
            FragmentShader* getFragmentShader() const;

            /**
             * \return The pre-tessellation shader used by this material. May be NULL if no valid shader is set.
             */
            PreTessellationShader* getPreTessellationShader() const;

            /**
             * \return The post-tessellation shader used by this material. May be NULL if no valid shader is set.
             */
            PostTessellationShader* getPostTessellationShader() const;

            //------------------------------------------------------------
            // Uniform Methods
            //------------------------------------------------------------

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             * \param[in] name  Valid uniform name.
             * \param[in] value Single floating-point value for the uniform.
             */
            virtual void setUniform(std::string const& name, float value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, float& value);

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             * \param[in] name  Valid uniform name.
             * \param[in] value A 4-component Vector value for the uniform.
             */
            virtual void setUniform(std::string const& name, Math::Vector4f const& value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, Math::Vector4f& value);

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             * \param[in] name  Valid uniform name.
             * \param[in] value A 3x3 matrix value for the uniform.
             */
            virtual void setUniform(std::string const& name, Math::Matrix3x3f const& value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, Math::Matrix3x3f& value);

            /**
             * Sets the value of the specified uniform.
             *
             * \note This uniform value is set for all valid shaders associated with this material.
             * \param[in] name  Valid uniform name.
             * \param[in] value A 4x4 matrix value for the uniform.
             */
            virtual void setUniform(std::string const& name, Math::Matrix4x4f const& value);

            /**
             * Returns the value of the associated uniform.
             *
             * \param[in]  name  Valid uniform name.
             * \param[out] value Value of the specified uniform.
             *
             * \return Returns TRUE if the value was successfully retrieved. May return FALSE if
             *         either the uniform does not exist, or it is a different type of value.
             */
            virtual bool getUniform(std::string const& name, Math::Matrix4x4f& value);

        protected:

            void bindShaders();
            void unbindShaders();

            VertexShader*          m_VertexShader;
            GeometryShader*        m_GeometryShader;
            FragmentShader*        m_FragmentShader;
            PreTessellationShader*  m_PreTessellationShader;
            PostTessellationShader* m_PostTessellationShader;

            std::vector<std::pair<std::string, Texture*>> m_Textures;

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