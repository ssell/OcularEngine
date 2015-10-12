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

        class Material
        {
        public:

            Material();
            ~Material();

            void bind();
            void unbind();

            //------------------------------------------------------------
            // Texture Methods

            /**
             * Expand upon this description once there is an implementation...
             *
             * \param[in] identifier 
             * \param[in] name
             */
            void setTexture(std::string const& identifier, std::string const& name);

            /**
             * Expand upon this description once there is an implementation...
             *
             * \param[in] identifier 
             * \param[in] texture
             */
            void setTexture(std::string const& identifier, Texture* texture);

            /**
             * Retrieves the texture stored at the specified identifier.
             * \param[in] identifier
             */
            Texture* getTexture(std::string const& identifier) const;

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

            VertexShader*          m_VertexShader;
            GeometryShader*        m_GeometryShader;
            FragmentShader*        m_FragmentShader;
            PreTesselationShader*  m_PreTesselationShader;
            PostTesselationShader* m_PostTesselationShader;

            std::unordered_map<std::string, Texture*> m_TextureMap;

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