/*
 * QuickGLCItem.cpp
 *
 *  Created on: 22/04/2013
 *      Author: laumaya
 */

#include <QGLFramebufferObject>

#include <GLC_Context>
#include <GLC_Exception>
#include <GLC_Factory>
#include <QSGSimpleTextureNode>
#include "quickglcitem.h"
#include <QSGNode>
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

QuickGLCItem::QuickGLCItem(QQuickItem *pParent)
    : QQuickItem(pParent)
    , m_Viewport()
    , m_World()
    , m_Light()
    , m_MoverController()
    , m_FirstRender(true)
    , m_pSourceFbo(NULL)
    , m_pSelectionFbo(NULL)
    , m_CurrentPos()
    , m_IsinSelectionMode(false)
{
    //setAcceptedMouseButtons(Qt::AllButtons);
    setAntialiasing(true);
    stackCounter = 0;
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton | Qt::MidButton);
    setFlag(QQuickItem::ItemIsFocusScope, true);
    setFlag(QQuickItem::ItemHasContents, true);
    m_rendertarget = NULL;
    // Set some GLC_lib state in order to render heavy scene
    GLC_State::setDefaultOctreeDepth(4);
    GLC_State::setPixelCullingUsage(true);
    GLC_State::setSpacePartionningUsage(true);
    m_Viewport.setMinimumPixelCullingSize(6);
    m_Viewport.setBackgroundColor(Qt::transparent);
    m_Light.setTwoSided(true);
    m_Light.setPosition(10.0, -10.0, 10.0);

    m_Viewport.cameraHandle()->setEyeCam(GLC_Point3d(1.0, 1.0, 1.0));

    QColor repColor;
    repColor.setRgbF(1.0, 0.11372, 0.11372, 1.0);
    m_MoverController= GLC_Factory::instance()->createDefaultMoverController(repColor, &m_Viewport);
    m_delta = 0;
    m_dirty = true;
}

QuickGLCItem::~QuickGLCItem()
{
    delete m_pSourceFbo;
    delete m_pSelectionFbo;
}

QVariant QuickGLCItem::world() const
{
    QVariant subject;
    subject.setValue(m_World);

    return subject;
}

void QuickGLCItem::setWorld(QVariant worldVariant)
{
    GLC_World world= worldVariant.value<GLC_World>();
    if (!world.isEmpty())
    {
        m_World= world;
        m_Viewport.reframe(world.boundingBox());
    }
    updateGLC();
}

void QuickGLCItem::updateGLC()
{
    markDirty();
    update();
}

void QuickGLCItem::markDirty(){
    m_dirty = true;
}

void QuickGLCItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    delete m_pSourceFbo;
    m_pSourceFbo= NULL;
    delete m_pSelectionFbo;
    m_pSelectionFbo= NULL;
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    markDirty();
}

void QuickGLCItem::paint()
{
    QOpenGLContext *qocontext = QOpenGLContext::currentContext();
    if(!GLC_Context::current() || !GLC_Context::current()->isValid()){
        QGLContext *baseGLContext = QGLContext::fromOpenGLContext(qocontext);
        baseGLContext->makeCurrent();
        GLC_Context *context = new GLC_Context(QGLFormat(QGL::SampleBuffers));
        context->create(baseGLContext);
        context->makeCurrent();
        Q_ASSERT(baseGLContext->isValid());
    }

    QOpenGLContext::currentContext()->functions()->glUseProgram(0);
    // Handle wheel zoom in/out
    if(m_delta != 0 ){
        // this has to be done into the thread owning the context they have been moved here
        m_Viewport.cameraHandle()->setDistEyeTarget(m_delta);
        m_Viewport.setDistMinAndMax(m_World.boundingBox());
        m_delta = 0;
    }
    glPopAttrib();
    if (!m_World.isEmpty() && widthValid() && heightValid() && isComponentComplete())
    {
        if (m_IsinSelectionMode)
        {
            renderForSelection();
        }
        else
        {
            render();
        }
    }
    glPushAttrib(GL_ALL_ATTRIB_BITS);
}

void QuickGLCItem::mousePressEvent(QMouseEvent *e)
{
    if (!m_MoverController.hasActiveMover())
    {
        const QSize oldSize= m_Viewport.size();

        switch (e->button())
        {
        case (Qt::RightButton):
            m_Viewport.setWinGLSize(width(), height(), false);
            m_MoverController.setActiveMover(GLC_MoverController::TrackBall, GLC_UserInput(e->pos().x(), e->pos().y()));
            m_Viewport.setWinGLSize(oldSize, false);
            updateGLC();
            break;
        case (Qt::LeftButton):
            select(e->pos().x(), e->pos().y());
            break;
        case (Qt::MidButton):
            m_Viewport.setWinGLSize(width(), height(), false);
            m_MoverController.setActiveMover(GLC_MoverController::Zoom, GLC_UserInput(e->pos().x(), e->pos().y()));
            m_Viewport.setWinGLSize(oldSize, false);
            updateGLC();
            break;

        default:
            break;
        }
    }
}

void QuickGLCItem::mouseMoveEvent(QMouseEvent  *e)
{
    if (m_MoverController.hasActiveMover())
    {
        QSize oldSize= m_Viewport.size();
        m_Viewport.setWinGLSize(width(), height(), false);
        m_MoverController.move(GLC_UserInput(e->pos().x(), e->pos().y()));
        m_Viewport.setWinGLSize(oldSize, false);
        updateGLC();
    }
}

void QuickGLCItem::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    this->setFocus(true, Qt::MouseFocusReason);
    if (m_MoverController.hasActiveMover())
    {
        m_MoverController.setNoMover();
        updateGLC();
    }
}
void QuickGLCItem::keyPressEvent(QKeyEvent *e) // switch between camera
{
    switch(e->key()){
    case Qt::Key_1:
        m_Viewport.cameraHandle()->setIsoView();
        break;
    case Qt::Key_2:
        m_Viewport.cameraHandle()->setFrontView();
        break;
    case Qt::Key_3:
        m_Viewport.cameraHandle()->setIsoView();
        m_Viewport.cameraHandle()->rotateAroundTarget(glc::Z_AXIS, glc::toRadian(90));
        break;
    case Qt::Key_4:
        m_Viewport.cameraHandle()->setLeftView();
        break;
    case Qt::Key_5:
        m_Viewport.cameraHandle()->setTopView();
        m_Viewport.cameraHandle()->rotateAroundTarget(glc::Z_AXIS, glc::toRadian(180));
        break;
    case Qt::Key_6:
        m_Viewport.cameraHandle()->setRightView();;
        break;
    case Qt::Key_7:
        m_Viewport.cameraHandle()->setIsoView();
        m_Viewport.cameraHandle()->rotateAroundTarget(glc::Z_AXIS, glc::toRadian(-90));
        break;
    case Qt::Key_8:
        m_Viewport.cameraHandle()->setRearView();;
        break;
    case Qt::Key_9:
        m_Viewport.cameraHandle()->setIsoView();
        m_Viewport.cameraHandle()->rotateAroundTarget(glc::Z_AXIS, glc::toRadian(180));
        break;
    case Qt::Key_0:
        m_Viewport.cameraHandle()->setBottomView();
        m_Viewport.cameraHandle()->rotateAroundTarget(glc::Z_AXIS, glc::toRadian(180));
        break;
     default:
        return;
    }
    updateGLC();

}

void QuickGLCItem::wheelEvent(QWheelEvent *event)
{
    m_delta = m_Viewport.cameraHandle()->distEyeTarget() - (event->delta() / 4);
    updateGLC();
}

void QuickGLCItem::initGl()
{
    m_Viewport.initGl();
    glEnable(GL_NORMALIZE);
    // Enable antialiasing
    glEnable(GL_MULTISAMPLE);
    m_FirstRender= false;
}

QSGNode * QuickGLCItem::updatePaintNode(QSGNode * oldNode, UpdatePaintNodeData *)
{
    if (width() <= 0 || height() <= 0) {
        delete oldNode;
        return NULL;
    }

    QSGSimpleTextureNode* node = 0;
    if(oldNode)
    {
        node = static_cast<QSGSimpleTextureNode*>(oldNode);
    }

    if (!node){
        node = new QSGSimpleTextureNode();
    }


    if(!m_rendertarget){
        m_rendertarget= new QMLRenderTarget(this->boundingRect().size().width(),this->boundingRect().size().height());
    }

    m_rendertarget->setSize(this->boundingRect().size().toSize());
    if(m_dirty){
        paint();
        node->setTexture(this->m_rendertarget);
        node->setRect(boundingRect());
        node->markDirty(QSGNode::DirtyMatrix );
        m_dirty = false;
    }
    return node;
}

void QuickGLCItem::render()
{
    if(!m_rendertarget){
        m_rendertarget= new QMLRenderTarget(this->boundingRect().size().width(),this->boundingRect().size().height());
    }
    setupFbo(this->width(), this->height());
    if (m_pSourceFbo && m_pSourceFbo->isValid())
    {
        initGl();
        pushMatrix();
        try{
            m_rendertarget->begin();
            m_Viewport.setWinGLSize(width(), height());
            // Calculate camera depth of view
            m_Viewport.setDistMinAndMax(m_World.boundingBox());
            renderWorld();
            m_rendertarget->end();
        }
        catch (GLC_Exception &e)
        {
            qDebug() << e.what();
            popMatrix();
            return;
        }
        popMatrix();

    }
    else
    {
        delete m_pSourceFbo;
        m_pSourceFbo= NULL;
    }
}

void QuickGLCItem::renderForSelection()
{
    setupFbo(this->width(), this->height());
    setupSelectionFbo(this->width(), this->height());
    GLC_uint selectionId;
    initGl();
    pushMatrix();
    try{
        m_pSelectionFbo->bind();

        m_Viewport.setWinGLSize(width(), height());
        // Calculate camera depth of view
        m_Viewport.setDistMinAndMax(m_World.boundingBox());

        GLC_State::setSelectionMode(true);
        renderWorld();
        selectionId= m_Viewport.selectOnPreviousRender(m_CurrentPos.x(), m_CurrentPos.y(), GL_COLOR_ATTACHMENT0);
        GLC_State::setSelectionMode(false);
        m_IsinSelectionMode= false;

        m_pSelectionFbo->release();
        m_Viewport.setWinGLSize(width(), height());
    }
    catch (GLC_Exception &e)
    {
        qDebug() << e.what();
        popMatrix();
        return;
    }
    popMatrix();
    glDisable(GL_DEPTH_TEST);
    m_World.unselectAll();
    if (m_World.containsOccurence(selectionId))
    {
        m_World.select(m_World.occurence(selectionId));
    }

    render();
}

void QuickGLCItem::renderWorld()
{
    try
    {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Load identity matrix
        GLC_Context::current()->glcLoadIdentity();
        GLC_Context::current()->glcMatrixMode(GL_PROJECTION);
        GLC_Context::current()->glcScaled(1, -1,1);
        m_World.collection()->updateInstanceViewableState();
        m_Light.glExecute();
        m_Viewport.glExecuteCam();

        m_World.render(0, glc::ShadingFlag);
        m_World.render(0, glc::TransparentRenderFlag);

        m_World.render(1, glc::ShadingFlag);
        m_MoverController.drawActiveMoverRep();
    }
    catch (GLC_Exception &e)
    {
        qDebug() << e.what();
    }
}

void QuickGLCItem::setupFbo(int width, int height)
{
    if (NULL == m_pSourceFbo)
    {
        QOpenGLFramebufferObjectFormat sourceFormat;
        sourceFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        sourceFormat.setSamples(8);
        m_pSourceFbo= new QOpenGLFramebufferObject(width, height, sourceFormat);
    }
}

void QuickGLCItem::setupSelectionFbo(int width, int height)
{
    if (NULL == m_pSelectionFbo)
    {
        m_pSelectionFbo= new QOpenGLFramebufferObject(width, height, QOpenGLFramebufferObject::CombinedDepthStencil);
    }
}

void QuickGLCItem::pushMatrix()
{
    GLC_Context* pCurrentContext= GLC_Context::current();
    pCurrentContext->glcMatrixMode(GL_PROJECTION);
    pCurrentContext->glcPushMatrix();
    pCurrentContext->glcMatrixMode(GL_MODELVIEW);
    pCurrentContext->glcPushMatrix();
}

void QuickGLCItem::popMatrix()
{
    GLC_Context* pCurrentContext= GLC_Context::current();
    pCurrentContext->glcMatrixMode(GL_PROJECTION);
    pCurrentContext->glcPopMatrix();
    pCurrentContext->glcMatrixMode(GL_MODELVIEW);
    pCurrentContext->glcPopMatrix();
}

void QuickGLCItem::select(qreal x, qreal y)
{
    m_IsinSelectionMode= true;
    m_CurrentPos.setVect(x, y);
    updateGLC();
}
