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

    /*Windeployqt {
        id: _windeployqt
        onStarted: busiDialog.open()
        onFinished: busiDialog.finished(exitCode)
        onNewOutputData: busiDialog.addOutput(line)
        onNewErrorData: busiDialog.addError(line)
    }*/

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Исполняемый файл")
            filterFile: qsTr("Испольняемый файл (*.exe)")
            mode: LabelFieldDialog.Mode.File
            onTextChanged: {
                _windeployqt.setExeFile(text)
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка развертывания")
            onTextChanged: {
                _windeployqt.setDir(text)
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка подключаемых библиотек")
            onTextChanged: {
                _windeployqt.setLibdir(text)
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка подключаемых плагинов")
            onTextChanged: {
                _windeployqt.setPlugindir(text)
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка используемых qml файлов")
            onTextChanged: {
                _windeployqt.setQmldir(text)
            }
        }
        LabelFieldDialog {
            label: qsTr("Папка подключаемых qml модулей")
            onTextChanged: {
                _windeployqt.setQmlimport(text)
            }
        }
        LabelFieldDialog {
            label: qsTr("Флаги")
            mode: LabelFieldDialog.Mode.Flags
            flagsModel: Data.modelFlagsWinDeployQt
            onTextChanged: {
                _windeployqt.setFlags(flags)
            }
        }
        LabelFieldDialog {
            width: 100;  height: 40
            label: qsTr("Библиотеки")
            mode: LabelFieldDialog.Mode.Libraries
            librariesModel: Data.modelLibraryWindDeployQt
            onTextChanged: {
                _windeployqt.setLibraries(text)
            }
        }
        Repeater {
            width: parent.width; height: 300
            model: _root.modelFlags
            delegate: Item {
                width: _checBox.width; height: 20
                CheckBox {
                    id: _checBox
                    text: modelData
                }
            }
        }
    }

    onRun: _windeployqt.deploy()


}
