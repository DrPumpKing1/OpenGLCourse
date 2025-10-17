#pragma once

#include "../glad_loader.h"
#include <stb/stb_image.h>

#include "shader.h"

class Texture
{
public:
    GLuint ID;
    std::string type;
    std::string path;
    GLenum unit; // Texture unit
    Texture(const char *path, std::string type, GLenum slot)
    {
        this->path = std::string(path);
        this->type = type;
        this->unit = slot;

        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *bytes = stbi_load(path, &widthImg, &heightImg, &numColCh, 0);

        glGenTextures(1, &ID);

        glActiveTexture(slot);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
        // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

        GLint internalFormat;
        GLenum format;

        if(type == "normal")
        {
            internalFormat = GL_RGB;
            format = GL_RGBA;
        }
        else if(type == "displacement")
        {
            internalFormat = GL_RED;
            format = GL_RGBA;
        }
        else if(numColCh == 4)
        {
            internalFormat = GL_SRGB_ALPHA;
            format = GL_RGBA;
        }
        else if(numColCh == 3)
        {
            internalFormat = GL_SRGB;
            format = GL_RGB;
        }
        else if(numColCh == 1)
        {
            internalFormat = GL_SRGB;
            format = GL_RED;
        }
        else
            throw std::invalid_argument("Automatic Texture type recognition failed");

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, bytes);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(bytes);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Assigns a texture unit to a texture
    void texUnit(Shader &shader, const char *uniform, GLuint unit)
    {
        shader.Activate();
        shader.setInt(uniform, unit);
    }
    // Binds a texture
    void Bind()
    {
        glBindTexture(GL_TEXTURE_2D, ID);
    }
    // Unbinds a texture
    void Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // Deletes a texture
    void Delete()
    {
        glDeleteTextures(1, &ID);
    }
};