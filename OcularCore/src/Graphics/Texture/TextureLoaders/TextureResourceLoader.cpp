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
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader.hpp"
#include "Graphics/Texture/Texture2D.hpp"
#include "Utilities/StringUtils.hpp"
#include "Utilities/EndianOps.hpp"

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

        bool TextureResourceLoader::loadResource(Core::Resource* &resource, Core::File const& file)
        {
            bool result = false;

            if(isFileValid(file))
            {
                std::vector<Core::Color> pixels;

                unsigned width = 0;
                unsigned height = 0;

                if(readFile(file, pixels, width, height))
                {
                    if((width > 0) && (height > 0))
                    {
                        unsigned totalSize = width * height;

                        if(createResource(resource, file, pixels, width, height))
                        {
                            result = true;
                        }
                        else
                        {
                            OcularLogger->error("Failed to create Resource", OCULAR_INTERNAL_LOG("TextureResourceLoader", "loadResource"));
                        }
                    }
                    else
                    {
                        OcularLogger->error("Invalid image dimensions of (", width, ", ", height, ")", OCULAR_INTERNAL_LOG("TextureResourceLoader", "loadResource"));
                    }
                }
                else
                {
                    OcularLogger->error("Failed to parse the Resource file at '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("TextureResourceLoader", "loadResource"));
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool TextureResourceLoader::createResource(Core::Resource* &resource, Core::File const& file, std::vector<Core::Color> const& pixels, unsigned const& width, unsigned const& height)
        {
            // We are either creating a brand new resource, or loading into memory a pre-existing one.

            bool result = false;

            if(resource == nullptr)
            {
                TextureDescriptor descr;
                descr.width     = width;
                descr.height    = height;
                descr.cpuAccess = TextureAccess::ReadWrite;
                descr.gpuAccess = TextureAccess::ReadWrite;
                descr.filter    = TextureFilterMode::Point;
                descr.format    = TextureFormat::R32G32B32A32Float;
                descr.type      = TextureType::Texture2D;
                
                resource = OcularGraphics->createTexture(descr);

                if(resource != nullptr)
                {
                    resource->setSourceFile(file);
                }
            }

            Texture2D* texture = dynamic_cast<Texture2D*>(resource);

            if(texture)
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
                OcularLogger->error("Provided Resource is not a Texture2D or is NULL", OCULAR_INTERNAL_LOG("TextureResourceLoader", "createResource"));
            }

            return result;
        }

        void TextureResourceLoader::loadFileIntoBuffer(Core::File const& file, std::vector<unsigned char>& buffer, Endianness fileEndianness)
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

                    // Ensure all the retrieved data is in the proper endianness

                    for(unsigned i = 0; i < buffer.size(); i++)
                    {
                        Utils::EndianOps::convert(fileEndianness, Endianness::Native, buffer[i]);
                    }
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