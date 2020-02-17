import QtQuick 2.12
import QtQuick.Controls 2.5


import Components.Controls 1.0
import Components.Elements 1.0

BasicPage {
    id: _builderPage
    title: "Build"
    buttonText: qsTr("Собрать")

    task: {
        "tool": "builder",
        "proFile": "G:\Projects\QtAutoTools\testBuild",
        "systemBuild": "qmake",
        "mkspec": "win32",
        "buildDir": "G:\Projects\QtAutoTools\testBuild",
        "configure": ""
    }

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Файл проекта")
            filterFile: qsTr("Файл проекта (*.pro)")
            mode: LabelFieldDialog.Mode.File
            onTextChanged: {
                task.proFile = text
            }
        }
        LabelComboBox {
            label: qsTr("Система сборки")
            model: []//_builder.systemBuildList
            onActivated: {
                task.systemBuild = currentText
            }
        }
        LabelComboBox {
            label: qsTr("Профиль")
            model: []//_builder.specList
            onActivated: {
                task.mkspec = currentText
            }
        }

        LabelFieldDialog {
            label: qsTr("Папка сборки")
            onTextChanged: {
                task.buildDir = text
            }
        }
        LabelFieldDialog {
            label: qsTr("CONFIG +=")
            isPopupButton: false
            onTextChanged: {
                task.configure = text
            }
        }
    }





}
