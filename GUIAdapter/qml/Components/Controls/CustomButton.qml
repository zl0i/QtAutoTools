import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

MouseArea {
    id: _button

    width: _label.contentWidth+40
    height: 40
    cursorShape: Qt.PointingHandCursor

    property string text: ""
    property int radius: 5
    property string style: "blue"

    property color disableColor
    property color disableTextColor

    property color pressedColor
    property color releasedColor

    property color pressedTextColor
    property color releaseTextColor


    state: style
    states: [
        State {
            name: "blue"
            PropertyChanges {
                target: _button
                disableColor: "#C4C4C4"
                disableTextColor: "#FFFFFF"

                pressedColor: "#2C71B1"
                releasedColor: "#52ABFF"

                pressedTextColor: "#FFFFFF"
                releaseTextColor: "#FFFFFF"
            }
        },
        State {
            name: "red"
            PropertyChanges {
                target: _button

                disableColor: "#C4C4C4"
                disableTextColor: "#FFFFFF"

                pressedColor: "#981F1F"
                releasedColor: "#E31F1F"

                pressedTextColor: "#FFFFFF"
                releaseTextColor: "#FFFFFF"
            }
        }
    ]

    Rectangle {
        width: _button.width; height: _button.height; radius: _button.radius
        color: _button.enabled ? (_button.down ? pressedColor : releasedColor) : disableColor
    }

    Label {
        id: _label
        width: _button.width; height: _button.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: _button.enabled ? (_button.down ? pressedTextColor : releaseTextColor) : disableTextColor
        text: _button.text
    }
}
