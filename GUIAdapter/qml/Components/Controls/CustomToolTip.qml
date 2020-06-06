import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

ToolTip {
    id: _toolTip
    width: contentWidth+20
    contentItem: Text {
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font: _toolTip.font
        color: "#000000"
        text: _toolTip.text
    }

    background: Rectangle {
        width: parent.width; height: parent.height; radius: 5
        color: "#FFFFFF"
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 8
            samples: 16
            color: "#80000000"
        }
    }
}
