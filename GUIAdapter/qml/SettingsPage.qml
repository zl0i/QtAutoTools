import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.1

import Components.Elements 1.0
import Components.Controls 1.0

BasicPage {

    property var settings: _guiAdapter.settings

    title: qsTr("Настройки")
    buttonText: qsTr("Удалить все настройки")

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Путь к Qt")
            mode: LabelFieldDialog.Mode.Folder
            text: _guiAdapter.settings.qtPath
            onTextChanged: settings.qtPath = text
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
            }
        }

        LabelComboBox {
            label: qsTr("Версия Qt Installer Framework")
            model:  _toolDetector.detectTools.finstallerVersions
            currentIndex: {
                return _toolDetector.detectTools.finstallerVersions.indexOf(_guiAdapter.settings.finstallerVersion)
            }

            onCurrentTextChanged: {
                settings.finstallerVersion = currentText
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
                        code: "ru_Ru"
                    }
                    ListElement {
                        title: "English"
                        code: "en_US"
                    }
                }
                textRole: "title"

                onActivated: _guiAdapter.setLanguage(_languageList.get(currentIndex).code)
                Component.onCompleted: {
                    for(var i = 0; i < _languageList.count; i++) {
                        if(_languageList.get(i).code === _guiAdapter.settings.lang) {
                            currentIndex = i
                            break
                        }
                    }
                }
            }
        }
        CustomButton {
            text: qsTr("Применить")
            onClicked: {
                _guiAdapter.settings = settings
            }
        }
    }
    onRun: _guiAdapter.clearAllSettings()
}
