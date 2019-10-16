import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

ToolTip {
    id: _toolTip

    contentItem: Text {
        text: _toolTip.text
        font: _toolTip.font
        color: "#000000"
    }

    background: Rectangle {
        radius: 5
        color: "#FFFFFF"
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 8
            samples: 16
            color: "#80000000"
        }
    }

}
