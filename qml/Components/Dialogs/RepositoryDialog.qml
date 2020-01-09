import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Controls 1.0
import Components.Elements 1.0

Dialog {
    id: _dialog

    parent: Overlay.overlay
    x:parent.width/2-width/2; y:20
    width: 430; height: Math.min(_column.height + 120, parent.height-40)
    modal: true; dim: true
    closePolicy: Popup.NoAutoClose

    property var repository

    signal apply(var repository)


    Overlay.modal: Rectangle {
        color: "#DF000000"
    }

    background: Rectangle {
        width: parent.width; height: parent.height
        radius: 10
        color: "#FFFFFF"
    }

    contentItem: Item {
        width: parent.width; height: parent.height
        Label {
            font.pixelSize: 18
            text: qsTr("Репозиторий")
        }
        Flickable {
            id: _flickable
            x: 20; y: 35
            width: parent.width-40; height: parent.height-80
            contentHeight: _column.height
            interactive: contentHeight > height
            clip: true
            Column {
                id: _column
                spacing: 10
                LabelCheckBox {
                    width: _flickable.width
                    label: qsTr("Включить")
                    checked: repository.Enabled
                    onCheckedChanged: repository.Enabled = checked
                }
                LabelFieldRow {
                    label: qsTr("Название")
                    text: repository.DisplayName
                    onTextChanged: repository.DisplayName = text
                }
                LabelFieldRow {
                    label: qsTr("Url")
                    text: repository.Url
                    onTextChanged: repository.Url = text
                }
                LabelFieldRow {
                    label: qsTr("Логин")
                    text: repository.Username
                    onTextChanged: repository.Username = text
                }
                LabelFieldRow {
                    label: qsTr("Пароль")
                    text: repository.Password
                    onTextChanged: repository.Password = text
                }
            }
        }




        CustomButton {
            x: parent.width-240; y: parent.height-35
            width: 100;  height: 35
            text: qsTr("Применить")
            onClicked: {
                _dialog.apply(repository)
            }
        }
        CustomButton {
            x: parent.width-width-20; y: parent.height-35
            width: 100; height: 35
            text: qsTr("Отмена")
            onClicked: {
                _dialog.close()
            }
        }
    }

}
