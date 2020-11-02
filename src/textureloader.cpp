#include "textureloader.hpp"

#include "apputils.hpp"
#include "openglhelper.hpp"

#include <QImage>
#include <QString>

GLuint TextureLoader::CreateTextureFromPngFile(const QString &filename)
{
    if (loaded_textures.find(filename) != loaded_textures.cend())
    {
        return loaded_textures[filename];
    }
    GLuint textureId;
    AppUtils::FileContent_t data;
    if (!AppUtils::readFileContent(filename, data))
        return 0;
    const auto img2 = QImage(filename).convertToFormat(QImage::Format_RGBA8888);

    OpenGLHelper::get()->glGenTextures(1, &textureId);
    OpenGLHelper::get()->glBindTexture(GL_TEXTURE_2D, textureId);
    OpenGLHelper::get()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img2.width(), img2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img2.bits());
    OpenGLHelper::get()->glGenerateMipmap(GL_TEXTURE_2D);
    OpenGLHelper::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    OpenGLHelper::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLHelper::get()->glBindTexture(GL_TEXTURE_2D, 0);
    //    stbi_image_free(png);
    data.clear();
    loaded_textures[filename] = textureId;
    return textureId;
}
