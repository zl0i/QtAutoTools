import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Popup {
    width: 150; height: 125
    padding: 0
    modal: true

    readonly property var taskModel: ["Builder", "Windeployqt", "Qt Installer Framework", "qmldir", "LUpdate", "Console"]

    signal addTask(var tool)

    background: Rectangle {
        width: parent.width; height: parent.height; radius: 10
        color: "#FFFFFF"
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 16
            samples: 24
        }
    }
    contentItem: Item {
        width: parent.width; height: parent.height
        ListView {
            x: 0; y: 3
            width: parent.width; height: parent.height
            clip: true
            interactive: false
            model: taskModel
            delegate: Item {
                width: parent.width; height: 20;
                Label {
                    width: parent.width; height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: _mouseArea.hovered ? (_mouseArea.pressed ? "#3E5FB8" : "#39A0FF") : "#000000"
                    text: modelData
                }
                Rectangle {
                    x: 0; y: parent.height
                    visible: index != taskModel.length-1
                    width: parent.width; height: 1
                    color: "#C4C4C4"
                }
                MouseArea {
                    id: _mouseArea
                    width: parent.width; height: parent.height
                    hoverEnabled: true
                    property bool hovered: false
                    onEntered: hovered = true
                    onExited: hovered = false
                    onClicked: addTask(String(modelData).toLowerCase())
                }
            }
        }
    }

}
