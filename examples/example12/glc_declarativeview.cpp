/*
 * glc_declarativeview.cpp
 *
 *  Created on: 22/04/2013
 *      Author: laumaya
 */


#include <GLC_Context>

#include "glc_declarativeview.h"

GLC_DeclarativeView::GLC_DeclarativeView(QWindow *pParent)
    : QQuickView(pParent)
{
    setColor(Qt::transparent);
    setClearBeforeRendering(false);
    setPersistentSceneGraph(true);
    setPersistentOpenGLContext(true);
    setSurfaceType(QWindow::OpenGLSurface);
    //QQuickView::setViewport(new QGLWidget(new GLC_Context(QGLFormat(QGL::SampleBuffers)), this));
    //QQuickView::setRenderHint(QPainter::SmoothPixmapTransform);
    //QQuickView::setRenderHint(QPainter::Antialiasing);
    QQuickView::setResizeMode(QQuickView::SizeRootObjectToView);
}
