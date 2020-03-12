import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

import Components.Controls 1.0

Dialog {
    id: _scriptDialog
    parent: Overlay.overlay
    x:parent.width/2-width/2; y: 20
    width: parent.width/2; height: parent.height - 40
    modal: true; dim: true

    property var script

    property int currentTask: -1
    signal saveScript(var script)

    background: Rectangle {
        width: parent.width; height: parent.height; radius: 10
        color: "#FFFFFF"
    }


    contentItem: Item {
        TextInput {
            x: 10
            width: contentWidth+10; height: contentHeight+10
            font { pixelSize: 18; bold: true }
            text: script.name
            onTextChanged: script.name = text
        }
        Label {
            x: 10; y: 20
            font.pixelSize: 12
            text: qsTr("Версия: %1").arg(script.version)
        }

        Label {
            x: 10; y: 55
            font { pixelSize: 14; bold: true }
            text: qsTr("Задачи:")
        }

        ListView {
            y: 75
            width: parent.width; height: count*40+41
            model: script.tasks
            interactive: count*40 > _scriptPage.height-100
            clip: true
            delegate: MouseArea {
                width: parent.width; height: 40
                onClicked: {
                    currentTask = index
                    _taskDialog.task =  modelData
                    _taskDialog.open()
                }
                Rectangle {
                    width: parent.width; height: 1
                    color: "#C4C4C4"
                }
                Rectangle {
                    y: 40
                    width: parent.width; height: 1
                    color: "#C4C4C4"
                }
                Row {
                    x: 20;
                    height: parent.height
                    Label {
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        font { pixelSize: 14; bold: true }
                        text: modelData.label
                    }
                    Label {
                        y: 5
                        height: parent.height-5
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 12
                        text: "(" + modelData.tool + ")"
                    }
                }
                MenuButton {
                    x: parent.width - width - 20; y: 13
                }
            }
            footer: MouseArea {
                width: parent.width; height: 40
                Rectangle {
                    width: parent.width; height: 1
                    color: "#C4C4C4"
                }
                Rectangle {
                    y: 40
                    width: parent.width; height: 1
                    color: "#C4C4C4"
                }
                Label {
                    width: parent.width; height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 24
                    text: "+"
                }
            }
        }
        CustomButton {
            x: parent.width/2 - width/2; y: parent.height - height
            text: qsTr("Сохранить")
            onClicked: {
                _scriptDialog.saveScript(script)
                _scriptDialog.close()
            }
        }
    }
    TaskDialog {
        id: _taskDialog
        onApply: {
            script.tasks[currentTask] = task
            currentTask = -1
            _taskDialog.close()
        }
    }
}
