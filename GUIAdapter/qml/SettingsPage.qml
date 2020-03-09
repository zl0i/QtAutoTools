import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.1

import Components.Elements 1.0
import Components.Controls 1.0

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
                //_guiAdapter.settings = settings
            }
        }

        LabelComboBox {
            label: qsTr("Версия Qt")
            model: _toolDetector.detectTools.qtVersions
            currentIndex: {
                return _toolDetector.detectTools.qtVersions.indexOf(_guiAdapter.settings.qtVersion)
            }

            onCurrentTextChanged: {
                settings.qtVersion = currentText
                settingsChanged()
                //_guiAdapter.settings = settings
            }
        }

        LabelComboBox {
            label: qsTr("Профиль")
            model: _toolDetector.detectTools.profiles[settings.qtVersion]
            currentIndex: {
                return _toolDetector.detectTools.profiles[settings.qtVersion].indexOf(_guiAdapter.settings.profile)
            }

            onCurrentTextChanged: {
                settings.profile = currentText
                //_guiAdapter.settings = settings
            }
        }

        LabelComboBox {
            label: qsTr("Компилятор")
            model: _toolDetector.detectTools.compilers
            currentIndex: {
                return _toolDetector.detectTools.compilers.indexOf(_guiAdapter.settings.compilator)
            }

            onCurrentTextChanged: {
                settings.compilator = currentText
                //_guiAdapter.settings = settings
            }
        }

        LabelComboBox {
            label: qsTr("Версия Qt Framework Installer")
            model:  _toolDetector.detectTools.finstallerVersions
            currentIndex: {
                return _toolDetector.detectTools.finstallerVersions.indexOf(_guiAdapter.settings.finstallerVersion)
            }

            onCurrentTextChanged: {
                settings.finstallerVersion = currentText
                //_guiAdapter.settings = settings
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
        CustomButton {
            text: qsTr("Применить")
            onClicked: {
                _guiAdapter.settings = settings
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
