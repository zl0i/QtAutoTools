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
        "proFile": "",
        "systemBuild": "qmake",
        "mkspec": "",
        "buildDir": "",
        "configure": ""
    }

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Файл проекта")
            filterFile: qsTr("Файл проекта (*.pro)")
            mode: LabelFieldDialog.Mode.File
            text: task.proFile
            onTextChanged: {
                task.proFile = text
            }
        }
        LabelComboBox {
            label: qsTr("Система сборки")
            model: _toolDetector.buildSystems
            currentIndex:  _toolDetector.buildSystems.indexOf(task.systemBuild)
            onActivated: {
                task.systemBuild = currentText
            }
        }
        LabelComboBox {
            label: qsTr("Спецификация")
            model: _toolDetector.getDetectTools().mkspecs[
                   _guiAdapter.settings.qtVersion + "_" + _guiAdapter.settings.profile
                   ]
            currentIndex: _toolDetector.getDetectTools().mkspecs[
                              _guiAdapter.settings.qtVersion + "_" + _guiAdapter.settings.profile
                              ].indexOf(task.mkspec)
            onActivated: {
                task.mkspec = currentText
            }
        }

        LabelFieldDialog {
            label: qsTr("Папка сборки")
            text: task.buildDir
            onTextChanged: {
                task.buildDir = text
            }
        }
        LabelFieldDialog {
            label: qsTr("CONFIG +=")
            isPopupButton: false
            text: task.configure
            onTextChanged: {
                task.configure = text
            }
        }
    }





}
