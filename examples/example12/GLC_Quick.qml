import QtQuick 2.0
import glcview 1.0
Rectangle{
    width: parent.width
    height: parent.height
    x:0
    y:0
    color: "#ff0000"
    Rectangle{
        width: parent.width - 40
        height: parent.height - 40
        x:20
        y:20
        color:"yellow"
        id: rect2
        antialiasing: true
        GLCView{
            anchors.left: rect2.left
            anchors.top: view1.top
            anchors.margins: 10
            width: rect2.width - 20
            height: rect2.height - 20
            world: worldVariant2
        }
    }
}
