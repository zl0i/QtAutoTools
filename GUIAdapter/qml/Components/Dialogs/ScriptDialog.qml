import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtGraphicalEffects 1.0

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
            text: script ? script.name : ""
            onTextChanged: script.name = text
        }
        Label {
            x: 10; y: 20
            font.pixelSize: 12
            text: script ? qsTr("Версия: %1").arg(script.version) : ""
        }

        Label {
            x: 10; y: 55
            font { pixelSize: 14; bold: true }
            text: qsTr("Задачи:")
        }

        ListView {
            y: 75
            width: parent.width; height: count*40+41
            model: script ? script.tasks : 0
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
                    TextInput {
                        width: contentWidth + 10; height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        font { pixelSize: 14; bold: true }
                        text: modelData.label
                        onTextChanged: script.tasks[index].label = text
                    }
                    Label {
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 12
                        text: "(" + modelData.tool + ")"
                    }
                }
                MouseArea {
                    x: parent.width-width-60; y: 15
                    width: 17; height: 17
                    onClicked: {
                        script.tasks.splice(index, 1)
                        scriptChanged()
                    }
                    Image {
                        width: 13; height: 13
                        source: "qrc:/icon/delete-black.svg"
                        layer.enabled: parent.pressed
                        layer.effect: ColorOverlay {
                            color: "#39A0FF"
                        }

                    }
                }

                MenuButton {
                    x: parent.width - width - 20; y: 13
                }
            }
            footer: MouseArea {
                width: parent.width; height: 40
                onClicked: _addTaskPopup.open()
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
                AddTaskPopup {
                    x: parent.width/2; y: parent.height/2
                    id: _addTaskPopup
                    onAddTask: {
                        var task = {
                            "tool": tool,
                            "label": tool,
                            "environment": _guiAdapter.settings
                        }
                        script.tasks.push(task)
                        scriptChanged()
                        _taskDialog.task =  task
                        _taskDialog.open()
                        close()
                    }

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
