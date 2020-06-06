import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtGraphicalEffects 1.0

import Components.Controls 1.0
import Components.Elements 1.0

Dialog {
    id: _scriptDialog
    parent: Overlay.overlay
    x:parent.width/2-width/2; y: 20
    width: parent.width/2; height: parent.height - 40
    modal: true; dim: true
    closePolicy: Popup.NoAutoClose

    property var script
    property string oldName

    property int currentTask: -1
    signal saveScript(var script, var renamed)

    function getPossibleDependence(currentLabel) {
        var labels = []
        for(var i = 0; i < script.tasks.length; i++) {
            if(script.tasks[i].label !== currentLabel)
                labels.push(script.tasks[i].label)
        }
        return labels;
    }

    background: Rectangle {
        width: parent.width; height: parent.height; radius: 10
        color: "#FFFFFF"
        ImageButton {
            x: parent.width-30; y: 5
            width: 25; height: 25
            image: "qrc:/icon/exit-black.svg"
            onClicked: {
                _scriptDialog.close()
            }
        }
    }

    contentItem: Item {
        TextField {
            id: _nameScriptField
            x: 10
            width: contentWidth+20 < 200 ? contentWidth+20 : 200; height: contentHeight+10
            font { pixelSize: 18; bold: true }
            text: script ? script.name : ""
            selectByMouse: true
            selectionColor: "#39A0FF"
            selectedTextColor: "#FFFFFF"
            padding: 0
            background: Item {
                width: _nameScriptField.width
                height: _nameScriptField.height
                Rectangle {
                    y: parent.height-2
                    width: parent.width; height: 1
                    color: "#1A1A1A"
                }
            }
        }
        Label {
            x: 10; y: 35
            font.pixelSize: 12
            text: script ? qsTr("Версия: %1").arg(script.version) : ""
        }

        Label {
            x: 10; y: 60
            font { pixelSize: 14; bold: true }
            text: qsTr("Задачи:")
        }
        Flickable {
            y: 80
            width: _scriptDialog.width-25; height: _scriptDialog.height-150
            contentHeight: _tasksView.height
            clip: true
            ListView {
                id: _tasksView
                width: parent.width ; height: (count+2) * 40
                model: script ? script.tasks : 0
                interactive: false
                header: Item { width: parent.width; height: 5 }
                delegate: TaskDelegate {
                    x: 5
                    width: _tasksView.width-10
                    name: modelData.label
                    tool: modelData.tool
                    onHoveredChanged: {
                        if(hovered) {
                            _taskDelegate.index = index
                            _taskDelegate.y = index*40 - _tasksView.contentY
                            _taskDelegate.visible = true
                        }
                    }
                }
                TaskDelegate {
                    id: _taskDelegate
                    x: 5; width: _tasksView.width-10
                    property int index: 0
                    name: script && index < script.tasks.length ? script.tasks[index].label : ""
                    tool: script && index < script.tasks.length ? script.tasks[index].tool : ""
                    visible: false
                    layer.enabled: true
                    layer.effect: DropShadow {
                        radius: 8
                        samples: _taskDelegate.mouseArea.pressed ? 30 : 16
                    }
                    onReleased: {
                        currentTask = index
                        _taskDialog.task = script.tasks[index]
                        _taskDialog.labelTasks = getPossibleDependence(script.tasks[index].label)
                        _taskDialog.open()
                    }
                    onRemoveTask: {
                        visible = false
                        script.tasks.splice(index, 1)
                        scriptChanged()
                    }
                    onHoveredChanged: {
                        if(!hovered) {
                            visible = false
                        }
                    }
                    CustomToolTip {
                        id: _toolTip
                        x: parent.mouseArea.mouseX; y: parent.mouseArea.mouseY - height - 10
                        visible: _taskDelegate.hovered
                        delay: 1500
                        text: _taskDelegate.tool
                    }
                }

                footer: AddTaskDelegate {
                    onAddTask: {
                        var task = {
                            "tool": tool,
                            "label": tool,
                            "environment": _guiAdapter.settings
                        }
                        script.tasks.push(task)
                        scriptChanged()
                        _taskDialog.task =  task
                        _taskDialog.labelTasks = getPossibleDependence(task.label)
                        _taskDialog.open()
                    }
                }
            }
        }

        CustomButton {
            x: parent.width/2 - width/2; y: parent.height - height
            text: qsTr("Сохранить")
            onClicked: {
                var renamed = script.name !== _nameScriptField.text
                oldName = script.name
                script.name = _nameScriptField.text
                _scriptDialog.saveScript(script, renamed)
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
