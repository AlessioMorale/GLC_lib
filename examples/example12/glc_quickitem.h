/*
 * GLC_QuickItem.h
 *
 *  Created on: 22/04/2013
 *      Author: laumaya
 */

#ifndef GLC_QUICKITEM_H
#define GLC_QUICKITEM_H

#include <QQuickItem>
#include <QtOpenGL>
#include <QUrl>
#include <QQuickPaintedItem>
#include <GLC_Viewport>
#include <GLC_Light>
#include <GLC_World>
#include <GLC_MoverController>
#include <QGLFramebufferObject>

class GLC_QuickItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVariant world READ world WRITE setWorld)

public:
    explicit GLC_QuickItem(QQuickItem* pParent= NULL);
    virtual ~GLC_QuickItem();

    QVariant world() const;

public slots:
    void setWorld(QVariant worldVariant);
    void paint();
protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);    
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

protected:
    void initGl();
    void render();
    void renderForSelection();
    void renderWorld();
    void setupFbo(int width, int height);
    void setupSelectionFbo(int width, int height);
    void pushMatrix();
    void popMatrix();
    void select(qreal x, qreal y);
    void itemChange(ItemChange change, const ItemChangeData &value);

protected:
    GLC_Viewport m_Viewport;
    GLC_World m_World;
    GLC_Light m_Light;
    GLC_MoverController m_MoverController;
    bool m_FirstRender;
    QGLFramebufferObject* m_pSourceFbo;
    QGLFramebufferObject* m_pTargetFbo;
    QGLFramebufferObject* m_pSelectionFbo;
    GLC_Vector2d m_CurrentPos;
    bool m_IsinSelectionMode;

};

#endif // GLC_QUICKITEM_H
