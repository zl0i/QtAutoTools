import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.1

import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0

BasicPage {
    id: _consolePage
    title: "Console"
    buttonText: qsTr("Выполнить")

    task: {
        "tool": "console",
        "comands": [""],
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
                text: qsTr("Список задач:")
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
            delegate:  LabelFieldDialog{
                widthLabel: 0
                widthField: _listView.width-80; height: 40
                text: task.comands[index]
                isPopupButton: false
                isClearButton: true
                onTextChanged: {
                    task.comands[index] = text
                }
                onClearClicked: {
                    task.comands.splice(index, 1)
                    taskChanged()
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
