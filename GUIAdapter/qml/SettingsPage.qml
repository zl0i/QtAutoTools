import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.1

import Components.Elements 1.0

Item {

    property var settings: _guiAdapter.settings

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: qsTr("Настройки")
    }

    Column {
        x: 20; y: 50
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Путь к Qt")
            mode: LabelFieldDialog.Mode.Folder
            text: _guiAdapter.settings.qtPath
            onTextChanged: {
                settings.qtPath = text
                _guiAdapter.settings = settings
            }
        }
        LabelFieldDialog {
            label: qsTr("Профиль")
            mode: LabelFieldDialog.Mode.Folder
            text:  _guiAdapter.settings.profilePath
            onTextChanged: {
                settings.profilePath = text
                _guiAdapter.settings = settings
            }
        }

        LabelFieldDialog {
            label: qsTr("Компилятор")
            mode: LabelFieldDialog.Mode.Folder
            text: _guiAdapter.settings.compilatorPath
            onTextChanged: {
                settings.compilator = text
                _guiAdapter.settings = settings
            }
        }

        Row {
            spacing: 10
            Label {
                width: 75; height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                text: qsTr("Язык")
            }
            ComboBox {
                model: ListModel {
                    id: _languageList
                    ListElement {
                        title: "Русский"
                        code: "ru"
                    }
                    ListElement {
                        title: "English"
                        code: "en"
                    }
                }
                textRole: "title"

                onActivated: _guiAdapter.setLanguage(_languageList.get(currentIndex).code)
                /*Component.onCompleted: {
                    for(var i = 0; i < _languageList.count; i++) {
                        if(_languageList.get(i).code === _worker.language) {
                            currentIndex = i
                            break
                        }
                    }
                }*/
            }
        }
        Button {
            text: qsTr("Удалить все настройки")
            onClicked: {
                _guiAdapter.clearAllSettings()
            }
        }
    }
}
