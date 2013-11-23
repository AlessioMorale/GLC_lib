#include <QApplication>

#include <QQmlContext>
#include <QFile>
#include <QVariant>

#include <GLC_World>
#include <GLC_Factory>

#include "quickglcview.h"
#include "quickglcitem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<QuickGLCItem>("glcview", 1, 0, "GLCView");

    QGLFormat f = QGLFormat::defaultFormat();
    f.setSampleBuffers(true);

    QuickGLCView view;
    QFile file2(":model/Democles.dae");
    GLC_World world2= GLC_Factory::instance()->createWorldFromFile(file2);
    QVariant variantWorld2;
    variantWorld2.setValue(world2);
    view.rootContext()->setContextProperty("worldVariant2", variantWorld2);

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/GLC_Quick.qml"));

    view.show();

    return app.exec();
}
