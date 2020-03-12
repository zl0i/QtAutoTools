import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1
import QtGraphicalEffects 1.0


import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0
import Components.Data 1.0

BasicPage {
    id: _root

    title: "Windeployqt"
    buttonText: qsTr("Развернуть")

    task: {
        "tool": "windeployqt",
        "exeFile": "",
        "deployDir": "",
        "libraryDir": "",
        "pluginDir": "",
        "qmlFilesDir": "",
        "qmlPluginsDir": "",
        "flags": "",
        "libraries": ""
    }

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Исполняемый файл")
            filterFile: qsTr("Испольняемый файл (*.exe)")
            mode: LabelFieldDialog.Mode.File
            text: task.exeFile
            onTextChanged: {
                task.exeFile = text
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка развертывания")
            text: task.deployDir
            onTextChanged: {
                task.deployDir = text
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка подключаемых библиотек")
            text: task.libraryDir
            onTextChanged: {
                task.libraryDir = text
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка подключаемых плагинов")
            text: task.pluginDir
            onTextChanged: {
               task.pluginDir = text
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка используемых qml файлов")
            text: task.qmlFilesDir
            onTextChanged: {
                task.qmlFilesDir = text
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка подключаемых qml модулей")
            text:  task.qmlPluginsDir
            onTextChanged: {
                task.qmlPluginsDir = text
            }
        }
        LabelFieldDialog {
            label: qsTr("Флаги")
            mode: LabelFieldDialog.Mode.Flags
            flagsModel: Data.modelFlagsWinDeployQt
            text: task.flags
            onTextChanged: {
                task.flags = text
            }
        }
        LabelFieldDialog {
            width: 100;  height: 40
            label: qsTr("Библиотеки")
            mode: LabelFieldDialog.Mode.Libraries
            librariesModel: Data.modelLibraryWindDeployQt
            text: task.libraries
            onTextChanged: {
                task.libraries = text
            }
        }
    }
}
