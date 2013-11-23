#ifndef QMLRENDERTARGET_H
#define QMLRENDERTARGET_H
#include <QSGTexture>
#include <QOpenGLFramebufferObject>
// ---------------------------------------------------------------------------
class QMLRenderTarget : public QSGTexture
{
  Q_OBJECT
  public :
    QMLRenderTarget(int width, int height);
    virtual ~QMLRenderTarget();
    void begin();
    void end();
    virtual void bind();
    virtual bool hasAlphaChannel() const;
    virtual bool hasMipmaps() const;
    virtual int textureId() const;
    void setSize(QSize);
    void setSize(int width, int height);
    virtual QSize textureSize() const;
  public:
    QOpenGLFramebufferObject *fbo;
};
#endif // QMLRENDERTARGET_H
