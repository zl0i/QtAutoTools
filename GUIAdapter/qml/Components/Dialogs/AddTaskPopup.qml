import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Popup {
    width: 100; height: 107
    padding: 0

    readonly property var taskModel: ["builder", "windeployqt", "finstaller", "qmldir", "lupdate"]

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
                    color: _mouseArea.pressed ? "#3E5FB8" : "#000000"
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
                    onClicked: addTask(modelData)
                }


            }
        }
    }

}
