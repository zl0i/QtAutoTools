import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Popup {
    width: 100; height: 130
    topPadding: 0; bottomPadding: 0
    leftPadding: 0; rightPadding: 0

    readonly property var taskModel: ["builder", "windeployqt", "finstaller", "qmldir", "lupdate"]

    signal addTask(var tool)

    background: Rectangle {
        width: parent.width; height: parent.height; radius: 10
        color: "#FFFFFF"
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 8
            samples: 16
        }
    }
    contentItem: Item {
        width: parent.width; height: parent.height
        ListView {
            width: parent.width; height: parent.height
            clip: true
            interactive: false
            model: taskModel
            delegate: ItemDelegate {
                width: parent.width; height: 20
                text: modelData
                Rectangle {
                    x: 0; y: parent.height
                    visible: index != taskModel.length-1
                    width: parent.width; height: 1
                    color: "#C4C4C4"
                }
                onClicked: addTask(modelData)
            }
        }
    }

}
