#include "qmlrendertarget.h"

// ---------------------------------------------------------------------------
QMLRenderTarget::QMLRenderTarget(int width, int height)
{
    QOpenGLFramebufferObjectFormat fmt;
    fmt.setMipmap(true);
    fmt.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    fbo = new QOpenGLFramebufferObject(width, height, fmt);
}

// ---------------------------------------------------------------------------
QMLRenderTarget::~QMLRenderTarget()
{
  delete fbo;
}

void QMLRenderTarget::setSize(int width, int height){
    if(!fbo || fbo->size().width() != width || fbo->size().height()!=height){
        QOpenGLFramebufferObjectFormat fmt;
        fmt.setMipmap(true);
        fmt.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        if(fbo){
            delete fbo;
            fbo = NULL;
        }
        fbo = new QOpenGLFramebufferObject(width, height, fmt);
    }
}

// ---------------------------------------------------------------------------
void QMLRenderTarget::begin()
{
  fbo->bind();
}

// ---------------------------------------------------------------------------
void QMLRenderTarget::end()
{
  fbo->release();
}

// ---------------------------------------------------------------------------
void QMLRenderTarget::bind()
{
  glBindTexture(GL_TEXTURE_2D, fbo->texture());
}

// ---------------------------------------------------------------------------
bool QMLRenderTarget::hasAlphaChannel() const
{
  return true;
}

// ---------------------------------------------------------------------------
bool QMLRenderTarget::hasMipmaps() const
{
  return true;
}

// ---------------------------------------------------------------------------
int QMLRenderTarget::textureId() const
{
    return fbo->texture();
}

void QMLRenderTarget::setSize(QSize size)
{
    setSize(size.width(), size.height());
}

// ---------------------------------------------------------------------------
QSize QMLRenderTarget::textureSize() const
{
  return QSize(fbo->width(), fbo->height());
}
