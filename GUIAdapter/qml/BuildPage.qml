import QtQuick 2.12
import QtQuick.Controls 2.5


import Components.Controls 1.0
import Components.Elements 1.0

BasicPage {

    title: "Build"
    buttonText: qsTr("Собрать")

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Файл проекта")
            filterFile: qsTr("Файл проекта (*.pro)")
            mode: LabelFieldDialog.Mode.File
            onTextChanged: {
                //_builder.setProFile(text)
            }
        }
        LabelComboBox {
            label: qsTr("Система сборки")
            model: []//_builder.systemBuildList
            onActivated: {
                //_builder.setSystemBuild(currentText)
            }
        }
        LabelComboBox {
            label: qsTr("Спецификация")
            model: []//_builder.specList
            onActivated: {
                //_builder.setMkSpec(currentText)
            }
        }

        LabelFieldDialog {
            label: qsTr("Папка сборки")
            onTextChanged: {
                //_builder.setBuildDir(text)
            }
        }
        LabelFieldDialog {
            label: qsTr("CONFIG +=")
            isPopupButton: false
            onTextChanged: {
                //_builder.setConfigure(text)
            }
        }
    }

    //onRun: _builder.build()



}
