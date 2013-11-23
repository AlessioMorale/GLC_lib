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
        GLCView{
            x:0
            y:0
            width:parent.width
            height:parent.height
            id : view1
            world: worldVariant2
        }

    }
}
