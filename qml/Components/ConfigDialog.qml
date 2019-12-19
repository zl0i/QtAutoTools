import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Controls 1.0

Dialog {
    id: _dialog

    parent: Overlay.overlay
    x:parent.width/2-width/2; y:20
    width: 430; height: Math.min(_column.height + 120, parent.height-40)
    modal: true; dim: true
    closePolicy: Popup.NoAutoClose

    property var config: {
        "name": "",
        "version": "1.0",
        "author": "",
        "productUrl": "",
        "title": "",
        "maintenanceToolName": "",
        "installerWindowIcon": "",
        "logo": "",
        "startMenuDir": "",
        "targetDir": "",
        "repository": ""
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
                    text: config.name
                    onTextChanged: config.name = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Номер версии")
                    text: config.version
                    onTextChanged: config.version = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Автор")
                    text: config.author
                    onTextChanged: config.author = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("URL адрес приложения")
                    text: config.productUrl
                    onTextChanged: config.productUrl = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Заголовок установщика")
                    text: config.title
                    onTextChanged: config.title = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Иконка установщика")
                    text: config.installerWindowIcon
                    onTextChanged: config.installerWindowIcon = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Имя установщика")
                    text: config.maintenanceToolName
                    onTextChanged: config.maintenanceToolName = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Лого")
                    text: config.logo
                    onTextChanged: config.logo = text
                }
                /*LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Иконка приложения")                    
                }*/
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Папка установки")
                    text: config.targetDir
                    onTextChanged: config.targetDir = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Имя в меню пуск")
                    text: config.startMenuDir
                    onTextChanged: config.startMenuDir = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("URL репозитория")
                    text: config.repository
                    onTextChanged: config.repository = text
                }
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
