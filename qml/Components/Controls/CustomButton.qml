import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Button {
    id: _button

    contentItem: Label {
        width: parent.width; height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "#FFFFFF"
        text: parent.text
    }

    background: Rectangle {
        height: 35; radius: 5
        color: parent.down ? "#2C71B1" : "#52ABFF"
        /*layer.enabled: true
        layer.effect: DropShadow {
            radius: 8
            samples: 16
            color: "#80000000"
        }*/
    }

}
