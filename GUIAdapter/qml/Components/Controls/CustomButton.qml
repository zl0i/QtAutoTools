import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

MouseArea {
    id: _button

    width: _label.contentWidth+40
    height: 40

    property string text: ""
    property int radius: 5

    property color disableColor: "#C4C4C4"
    property color disableTextColor: "#FFFFFF"

    property color pressedColor: "#2C71B1"
    property color releasedColor: "#52ABFF"

    property color pressedTextColor: "#FFFFFF"
    property color releaseTextColor: "#FFFFFF"


    Rectangle {
        width: _button.width; height: _button.height; radius: _button.radius
        color: _button.enabled ? (_button.pressed ? pressedColor : releasedColor) : disableColor
    }

    Label {
        id: _label
        width: _button.width; height: _button.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: _button.enabled ? (_button.pressed ? pressedTextColor : releaseTextColor) : disableTextColor
        text: _button.text
    }
}
