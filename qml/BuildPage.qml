import QtQuick 2.12
import QtQuick.Controls 2.5

import AutoTools 1.0

import Components.Controls 1.0
import Components.Elements 1.0

BasicPage {

    title: "Build"
    buttonText: qsTr("Собрать")

    Builder {
        id: _builder
        onStarted: busiDialog.open()
        onFinished: busiDialog.finished(exitCode)
        onNewOutputData: busiDialog.addOutput(line)
        onNewErrorData: busiDialog.addError(line)
    }

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Файл проекта")
            filterFile: qsTr("Файл проекта (*.pro)")
            mode: LabelFieldDialog.Mode.File
            onTextChanged: {
                _builder.setProFile(text)
            }
        }
        LabelComboBox {
            label: qsTr("Система сборки")
            model: _builder.systemBuildList
            onActivated: {
                _builder.setSystemBuild(currentText)
            }
        }
        LabelComboBox {
            label: qsTr("Спецификация")
            model: _builder.specList
            onActivated: {
                _builder.setMkSpec(currentText)
            }
        }

        LabelFieldDialog {
            label: qsTr("Папка сборки")
            onTextChanged: {
                _builder.setBuildDir(text)
            }
        }
        LabelFieldDialog {
            label: qsTr("CONFIG +=")
            isPopupButton: false
            onTextChanged: {
                _builder.setConfigure(text)
            }
        }
    }

    onRun: _builder.build()

    onKill: _builder.kill()

}
