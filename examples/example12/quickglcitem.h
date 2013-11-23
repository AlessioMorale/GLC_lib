/*
 * glc_declarativeitem.h
 *
 *  Created on: 22/04/2013
 *      Author: laumaya
 */

#ifndef GLC_DECLARATIVEITEM_H
#define GLC_DECLARATIVEITEM_H

#define GLC_EXTENSIONSHARED_EXPORT

#include <QQuickPaintedItem>
#include <QtOpenGL>
#include <QUrl>

#include <GLC_Viewport>
#include <GLC_Light>
#include <GLC_World>
#include <GLC_MoverController>
#include "qmlrendertarget.h"

class QGLFramebufferObject;

class GLC_EXTENSIONSHARED_EXPORT QuickGLCItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant world READ world WRITE setWorld)

public:
    explicit QuickGLCItem(QQuickItem* pParent= NULL);
    virtual ~QuickGLCItem();
    QVariant world() const;

    void DebugGLStack();
public slots:
    void setWorld(QVariant worldVariant);
    void updateGLC();
protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void paint();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    void renderWorld();
    virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
protected:
    void initGl();
    void render();
    void renderForSelection();
    void setupFbo(int width, int height);
    void setupSelectionFbo(int width, int height);
    void pushMatrix();
    void popMatrix();
    void select(qreal x, qreal y);

protected:
    GLC_Viewport m_Viewport;
    GLC_World m_World;
    GLC_Light m_Light;
    GLC_MoverController m_MoverController;
    bool m_FirstRender;
    QOpenGLFramebufferObject* m_pSourceFbo;
    QOpenGLFramebufferObject* m_pSelectionFbo;
    GLC_Vector2d m_CurrentPos;
    bool m_IsinSelectionMode;
    QMLRenderTarget *m_rendertarget;
    qint16 stackCounter;
    double m_delta;
    bool m_dirty;
    void markDirty();
};

#endif // GLC_DECLARATIVEITEM_H

