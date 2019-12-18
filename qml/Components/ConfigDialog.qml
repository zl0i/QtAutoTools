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

    property var config: ({})

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
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Номер версии")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Автор")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("URL адрес приложения")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Заголовок установщика")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Иконка установщика")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Имя установщика")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Лого")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Иконка приложения")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Папка установки")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("Имя в меню пуск")
                }
                LabelFieldRow {
                    isPopupButton: false
                    label: qsTr("URL репозитория")
                }
            }
        }



        CustomButton {
            x: parent.width-240; y: parent.height-35
            width: 100;  height: 35
            text: qsTr("Применить")
            onClicked: {
                _dialog.apply()
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
