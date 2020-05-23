import QtQuick 2.12
import QtQuick.Controls 2.5


import Components.Controls 1.0
import Components.Elements 1.0


BasicPage {
    id: _consolePage
    title: "Console"
    buttonText: qsTr("Выполнить")

    task: {
        "tool": "console",
        "comands": [],
        "sequentially": true
    }

    contentItem: Column {
        width: _consolePage.width-40;
        spacing: 20
        Row {
            spacing: 20
            Label {
                height: 30
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Список задач")
            }
            CustomButton {
                width: 30; height: 30; radius: 15
                text: "+"
                onClicked: {
                    task.comands.push("")
                    taskChanged()
                }
            }
        }
        ListView {
            id: _listView
            width: parent.width; height: contentHeight
            interactive: false
            spacing: 10
            model: task.comands
            delegate: Row {
                width: _listView.width-50; height: 40
                spacing: 20
                TextField {
                    width: parent.width-50; height: 40
                    text: task.comands[index]
                    onTextChanged: {
                        task.comands[index] = text
                    }
                }
                CustomButton {
                    y: 5
                    width: 30; height: 30; radius: 15
                    text: "x"
                    onClicked: {
                        task.comands.splice(index, 1)
                        taskChanged()
                    }
                }
            }
        }
        LabelCheckBox {
            width: parent.width-50
            label: qsTr("Параллельно")
            enabled: task.comands.length > 1
            onCheckedChanged: task.sequentially = !checked
        }
    }

}
