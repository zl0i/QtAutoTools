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

    property var packag: {
        "name": "",
        "description": "",
        "version": "1.0",
        "dateRelease": "",
        "vendor": "",
        "virtual": false,
        "license": "",
        "script": "",
        "pages": "",
        "depends": "",
        "sort": "",
        "updateText": "",
        "preDefault": "false",
        "forsed": false,
        "replaces": "",
        "packageFolder": ""
    }

    signal apply(var packag)


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
            text: qsTr("Файл компонента")
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
                    label: qsTr("Название пакета")
                    text: packag.name
                    onTextChanged: packag.name = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Описание")
                    text: packag.description
                    onTextChanged: packag.description = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Номер версии")
                    text: packag.version
                    onTextChanged: packag.version = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Дата релиза")
                    text: packag.dateRelease
                    onTextChanged: packag.dateRelease = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Название вендора")
                    text: packag.vendor
                    onTextChanged: packag.vendor = text
                }
                LabelCheckBox {
                    label: qsTr("Скрыть пакет")
                    checked: packag.virtual
                    onCheckedChanged: packag.virtual = checked
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Файл лицензии")
                    text: packag.license
                    onTextChanged: packag.license = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Скрипт")
                    text: packag.script
                    onTextChanged: packag.script = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Дополнительные страницы")
                    text: packag.pages
                    onTextChanged: packag.pages = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Зависимости")
                    text: packag.depends
                    onTextChanged: packag.depends = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Приоритет сортировки")
                    text: packag.sort
                    onTextChanged: packag.sort = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Описание обновления пакета")
                    text: packag.updateText
                    onTextChanged: packag.updateText = text
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Выбор компонента по умолчанию")
                    text: packag.preDefault
                    onTextChanged: packag.preDefault = text
                }
                LabelCheckBox {
                    label: qsTr("Устанавливать всегда")
                    checked: packag.forsed
                    onCheckedChanged: packag.forsed = checked
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Список заменяемых компонентов")
                    text: packag.replaces
                    onTextChanged: packag.replaces = text
                }
            }
        }



        CustomButton {
            x: parent.width-240; y: parent.height-35
            width: 100;  height: 35
            text: qsTr("Применить")
            onClicked: {                
                _dialog.apply(packag)
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
