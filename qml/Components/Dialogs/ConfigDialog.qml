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

    property var config: {
        "Name": "",
        "Version": "1.0",
        "Publisher": "",
        "ProductUrl": "",
        "Title": "",
        "MaintenanceToolName": "",
        "InstallerWindowIcon": "",
        "Logo": "",
        "StartMenuDir": "",
        "TargetDir": "",
        "Arguments": []
       /* "RemoteRepositories": {
            "Repository": [
                {
                    "Url": "",
                    "Enabled": false,
                    "Username": "",
                    "Password": "",
                    "DisplayName": ""
                }
            ]
        }*/
    }

    signal apply(var config)


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
            text: qsTr("Файл конфигурации")
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
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Название приложения")
                    text: config.Name
                    onTextChanged: config.Name = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Номер версии")
                    text: config.Version
                    onTextChanged: config.Version = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Автор")
                    text: config.Publisher
                    onTextChanged: config.Publisher = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("URL адрес приложения")
                    text: config.ProductUrl
                    onTextChanged: config.ProductUrl = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Заголовок установщика")
                    text: config.Title
                    onTextChanged: config.Title = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Иконка установщика")
                    text: config.InstallerWindowIcon
                    onTextChanged: config.InstallerWindowIcon = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Имя установщика")
                    text: config.MaintenanceToolName
                    onTextChanged: config.MaintenanceToolName = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Лого")
                    text: config.Logo
                    onTextChanged: config.Logo = text
                }
                /*LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Иконка приложения")
                }*/
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Папка установки")
                    text: config.TargetDir
                    onTextChanged: config.TargetDir = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Имя в меню пуск")
                    text: config.StartMenuDir
                    onTextChanged: config.StartMenuDir = text
                }
                /*LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("URL репозитория")
                    text: config.RemoteRepositories.Repository[0].Url
                    onTextChanged: config.RemoteRepositories.Repository[0].Url = text
                }*/
            }
        }


        CustomButton {
            x: parent.width-240; y: parent.height-35
            width: 100;  height: 35
            text: qsTr("Применить")
            onClicked: {
                _dialog.apply(config)
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
