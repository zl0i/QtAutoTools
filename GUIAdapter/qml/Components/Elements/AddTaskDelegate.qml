import QtQuick 2.12
import QtQuick.Controls 2.12

import Components.Controls 1.0
import Components.Dialogs 1.0

MouseArea {
    id: _delegate
    width: parent.width; height: 40
    cursorShape: Qt.PointingHandCursor
    hoverEnabled: true
    property bool hovered: false

    signal addTask(var tool)

    onEntered: hovered = true
    onExited:  hovered = false

    onClicked: {
        var point = mapToItem(Overlay.overlay, mouseX, mouseY)
        if(point.y + _addTaskPopup.height + 20 > Overlay.overlay.height) {
            _addTaskPopup.y = -_addTaskPopup.height+20
        } else {
            _addTaskPopup.y = 20
        }
        _addTaskPopup.x = mouseX
        _addTaskPopup.open()
    }
    CustomToolTip {
        id: _toolTip
        x: parent.mouseX; y: parent.mouseY - height - 10
        visible: parent.hovered
        delay: 1000
        text: qsTr("Добавить задачу")
    }
    Rectangle {
        width: parent.width; height: 1
        color: "#C4C4C4"
    }
    Rectangle {
        y: 39
        width: parent.width; height: 1
        color: "#C4C4C4"
    }
    Label {
        width: parent.width; height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: parent.hovered || _addTaskPopup.opened ? 42 : 24
        text: "+"
        Behavior on font.pixelSize {
            NumberAnimation { duration: 100 }
        }
    }
    AddTaskPopup {
        x: parent.width/2; y: parent.height/2
        id: _addTaskPopup
        onAddTask:  {
            _delegate.addTask(tool)
            close()
        }
    }
}

