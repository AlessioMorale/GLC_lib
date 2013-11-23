/*
 * glc_declarativeview.cpp
 *
 *  Created on: 22/04/2013
 *      Author: laumaya
 */

#include <GLC_Context>

#include <qgl.h>
#include "quickglcview.h"
#include "quickglcitem.h"

QuickGLCView::QuickGLCView(QWindow *pParent)
    : QQuickView(pParent)
{
    //register the glcView type
    qmlRegisterType<QuickGLCItem>("glcview", 1, 0, "GLCView");
    setSurfaceType(QWindow::OpenGLSurface);
    setResizeMode(QQuickView::SizeRootObjectToView);
    setColor(Qt::transparent);
}
