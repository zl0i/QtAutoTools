import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Button {
    id: _button

    height: 40
    property int radius: 5

    contentItem: Label {
        width: parent.width; height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "#FFFFFF"
        text: parent.text
    }

    background: Rectangle {
        width: parent.width; height: parent.height; radius: parent.radius
        color: parent.down ? "#2C71B1" : "#52ABFF"
        /*layer.enabled: true
        layer.effect: DropShadow {
            radius: 8
            samples: 16
            color: "#80000000"
        }*/
    }

}
