import QtQuick 2.12
import QtGraphicalEffects 1.0

MouseArea {
    id: _button
    width: 14; height: 19
    hoverEnabled: true
    cursorShape: Qt.PointingHandCursor
    property bool hovered: false
    onEntered: hovered = true
    onExited: hovered = false
    Image {
        width: parent.width; height: parent.height
        source: "qrc:/icon/arrow-right.svg"
        layer.enabled: true
        layer.effect: ColorOverlay {
            color: hovered ? (_button.pressed ? "#2C71B1" : "#39A0FF") : "#C4C4C4"
        }
    }
}


