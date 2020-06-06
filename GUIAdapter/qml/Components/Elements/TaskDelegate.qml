import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Controls 1.0

Rectangle {
    id: _delegate
    width: parent.width; height: 40
    color: "#FFFFFF"

    property string name
    property string tool
    property bool hovered: false
    property alias mouseArea: _mouseArea    

    signal removeTask(var index)
    signal released()

    function isFirst() {
        return index == 0
    }
    MouseArea {
        id: _mouseArea
        width: parent.width; height: parent.height
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onEntered: _delegate.hovered = true
        onExited: _delegate.hovered = false
        onReleased: _delegate.released()
    }

    /*CustomToolTip {
        id: _toolTip
        x: _mouseArea.mouseX; y: _mouseArea.mouseY - height - 10
        visible: _delegate.hovered
        delay: 1500
        enabled: toolTipEnabled
        text: _delegate.tool
    }*/

    Rectangle {
        x: 5
        width: parent.width-10; height: 1
        color: "#C4C4C4"
        visible: !isFirst()
    }
    Label {
        x: 20
        width: contentWidth + 10; height: parent.height
        verticalAlignment: Text.AlignVCenter
        font { pixelSize: 14; bold: true }
        text: name
    }
    ImageButton {
        x: parent.width-30; y: parent.height/2 - height/2
        width: 20; height: 20
        image: "qrc:/icon/exit-black.svg"
        onClicked: {
            _delegate.removeTask(_delegate.index)
        }
    }
}
