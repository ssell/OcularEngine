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
        class PreTesselationShader;
        class PostTesselationShader;

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

            void setVertexShader(std::string const& name);
            void setVertexShader(VertexShader* shader);

            void setGeometryShader(std::string const& name);
            void setGeometryShader(GeometryShader* shader);

            void setFragmentShader(std::string const& name);
            void setFragmentShader(FragmentShader* shader);

            void setPreTesselationShader(std::string const& name);
            void setPreTesselationShader(PreTesselationShader* shader);

            void setPostTesselationShader(std::string const& name);
            void setPostTesselationShader(PostTesselationShader* shader);

            VertexShader* getVertexShader() const;
            GeometryShader* getGeometryShader() const;
            FragmentShader* getFragmentShader() const;
            PreTesselationShader* getPreTesselationShader() const;
            PostTesselationShader* getPostTesselationShader() const;

        protected:

            void bindShaders();
            void unbindShaders();

            VertexShader*          m_VertexShader;
            GeometryShader*        m_GeometryShader;
            FragmentShader*        m_FragmentShader;
            PreTesselationShader*  m_PreTesselationShader;
            PostTesselationShader* m_PostTesselationShader;

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