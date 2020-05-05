#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <QOpenGLFunctions>
#include <QString>
class TextureLoader
{
  public:
    static GLuint CreateTextureFromPngFile(const QString &fileName);

  private:
    inline static std::map<QString, GLuint> loaded_textures;
};
#endif
