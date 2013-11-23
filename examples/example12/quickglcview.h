
/*
 * quickglcview.h
 *
 *  Created on: 22/04/2013
 *      Author: laumaya
 */
#ifndef QUICKGLCVIEW_H
#define QUICKGLCVIEW_H

#define GLC_EXTENSIONSHARED_EXPORT
#include <QQuickView>
#include <QOpenGLContext>
class GLC_EXTENSIONSHARED_EXPORT QuickGLCView : public QQuickView
{
    Q_OBJECT
public:
    QuickGLCView(QWindow *pParent= NULL);
};

#endif // QUICKGLCVIEW_H
