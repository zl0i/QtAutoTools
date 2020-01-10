import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1
import QtGraphicalEffects 1.0

import AutoTools 1.0

import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0
import Components.Data 1.0

Item {
    id: _root


    Windeployqt {
        id: _windeployqt
        onStarted: {
            _busiDialog.reset()
            _busiDialog.open()
        }
        onFinished: {
            if(exitCode != 0)
                _busiDialog.errorProcess = true
            _busiDialog.isReady = true
        }
        onNewOutputData: {
            line = String(line).replace(/(\r\n){1}/g, '<br>')
            line = String(line).replace(/[ ]/g, '&nbsp;')
            _busiDialog.info += '<font color="#404040">'+line+'</font>'
        }
        onNewErrorData: {
            line = String(line).replace(/(\r\n){1}/g, '<br>')
            line = String(line).replace(/[ ]/g, '&nbsp;')
            _busiDialog.info += '<font color="#E31F1F" >'+line+'</font>'
        }
    }

    BusyDialog {
        id: _busiDialog
        onKill: _windeployqt.kill()
    }

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: "Windeployqt"
    }
    Flickable {
        x: 20; y: 60
        width: parent.width; height: parent.height-y
        contentHeight: _content.height+40
        interactive: contentHeight > height
        clip: true
        Column {
            id: _content
            x:0; y: 10
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
            CustomButton {
                text: qsTr("Развернуть")
                onClicked: {
                    _windeployqt.deploy()
                }
            }
        }
    }
}
