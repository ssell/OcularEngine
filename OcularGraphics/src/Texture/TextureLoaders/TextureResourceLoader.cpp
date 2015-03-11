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

#include "Texture/TextureLoaders/TextureResourceLoader.hpp"
#include "Texture/Texture2D.hpp"
#include "Utilities/StringUtils.hpp"
#include "OcularEngine.hpp"

#include <fstream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        TextureResourceLoader::TextureResourceLoader(std::string const& extension)
            : Core::AResourceLoader(extension)
        {
        
        }

        TextureResourceLoader::~TextureResourceLoader()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceLoader::loadResource(Core::Resource* resource, Core::File const& file)
        {
            bool result = false;

            if(isFileValid(file))
            {
                std::vector<Color> pixels;

                unsigned width = 0;
                unsigned height = 0;

                if(readFile(file, pixels, width, height))
                {
                    if((width > 0) && (height > 0))
                    {
                        unsigned totalSize = width * height;

                        if(pixels.size() == totalSize)
                        {
                            if(createResource(resource, file, pixels, width, height))
                            {
                                result = true;
                            }
                        }
                    }
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceLoader::isFileValid(Core::File const& file)
        {
            bool result = false;

            if(file.exists())
            {
                if(file.canRead())
                {
                    if(Utils::StringUtils::isEqual(file.getExtension(), m_SupportedExtension, true))
                    {
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Resource file '", file.getFullPath(), "' is an unsupported file type; Expected '", m_SupportedExtension, "'", OCULAR_INTERNAL_LOG("TextureResourceLoader", "isFileValid"));
                    }
                }
                else
                {
                    OcularLogger->error("Unable to read resource file '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("TextureResourceLoader", "isFileValid"));
                }
            }
            else
            {
                OcularLogger->error("Specified resource file '", file.getFullPath(), "' does not exist", OCULAR_INTERNAL_LOG("TextureResourceLoader", "isFileValid"));
            }

            return result;
        }

        bool TextureResourceLoader::createResource(Core::Resource* resource, Core::File const& file, std::vector<Color> const& pixels, unsigned const& width, unsigned const& height)
        {
            // We are either creating a brand new resource, or loading into memory a pre-existing one.

            bool result = false;

            Texture2D* texture = nullptr;

            if(resource == nullptr)
            {
                resource = new Texture2D(width, height);
                resource->setSourceFile(file);
            }

            texture = (Texture2D*)resource;

            if(texture != nullptr)
            {
                if((texture->getWidth() == width) && (texture->getHeight() == height))
                {
                    if(texture->isInMemory())
                    {
                        OcularLogger->warning("Loading in a texture resource that is already in memory", OCULAR_INTERNAL_LOG("TextureResourceLoader", "createResource"));
                        texture->unload();
                    }

                    if(!Utils::StringUtils::isEqual(file.getFullPath(), texture->getSourceFile().getFullPath()))
                    {
                        OcularLogger->warning("Source file mismatch for pre-existing resource", OCULAR_INTERNAL_LOG("TextureResourceLoader", "createResource"));
                        texture->setSourceFile(file);
                    }

                    if(texture->setPixels(pixels, 0, 0, width, height))
                    {
                        texture->apply();
                        result = true;
                    }
                    else
                    {
                        OcularLogger->error("Failed to set pixels for Resource", OCULAR_INTERNAL_LOG("TextureResourceLoader", "createResource"));
                    }
                }   
                else
                {
                    OcularLogger->error("Texture dimensions mismatch", OCULAR_INTERNAL_LOG("TextureResourceLoader", "createResource"));
                }
            }
            else
            {
                OcularLogger->error("Provided Resource is not a Texture2D", OCULAR_INTERNAL_LOG("TextureResourceLoader", "createResource"));
            }

            return result;
        }

        void TextureResourceLoader::loadFileIntoBuffer(Core::File const& file, std::vector<unsigned char>& buffer)
        {
            if(isFileValid(file))
            {
                if(!buffer.empty())
                {
                    OcularLogger->warning("Provided buffer is not empty; Emptying it", OCULAR_INTERNAL_LOG("TextureResourceLoader", "loadBuffer"));
                    buffer.clear();
                }

                std::ifstream inputStream(file.getFullPath(), std::ios_base::binary);

                if(inputStream.is_open())
                {
                    buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(inputStream), std::istreambuf_iterator<char>());
                    inputStream.close();
                }
                else
                {
                    OcularEngine.Logger()->error("Failed to open file for reading '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("TextureResourceLoader", "loadBuffer"));
                }
            }
            else 
            {
                OcularEngine.Logger()->error("Resource '", file.getFullPath(), "' is not a valid file", OCULAR_INTERNAL_LOG("TextureResourceLoader_BMP", "readFile"));
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}