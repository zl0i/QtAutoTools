import QtQuick 2.12
import QtQuick.Controls 2.5

import AutoTools 1.0

import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0
import Components.Data 1.0


Item {
    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: "lupdate"
    }
    Lupdate {
        id: _lupdate
        onStarted: {
            _busyDialog.reset()
            _busyDialog.open()
        }
        onNewOutputData: {
            line = String(line).replace(/(\r\n){1}/g, '<br>')
            line = String(line).replace(/[ ]/g, '&nbsp;')
            _busyDialog.info += '<font color="#404040">'+line+'</font>'
        }
        onNewErrorData: {
            line = String(line).replace(/(\r\n){1}/g, '<br>')
            line = String(line).replace(/[ ]/g, '&nbsp;')
            _busyDialog.info += '<font color="#E31F1F" >'+line+'</font>'
        }
        onFinished: {
            if(exitCode != 0)
                _busyDialog.errorProcess = true
            _busyDialog.isReady = true

        }
    }
    BusyDialog {
        id: _busyDialog
        onKill: _lupdate.kill()
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
            ListView {
                width: parent.width; height: count * 40 + (count-1) * spacing
                spacing: 20
                model: _lupdate.files
                interactive: false
                delegate:  LabelFieldDialog {
                    label: qsTr("Переводимые файлы")
                    text: file
                    mode: LabelFieldDialog.Mode.Files
                    filterFile: ["Qt Files (*.pro *.qml *.ui *.c *.c++ *.cc *.cpp *.cxx *.ch *.h *.h++ *.hh *.hpp *.hxx)", qsTr("Все файлы (*)")]
                    onFieldFocusChanged: {
                        if(!fieldFocus && text == "" && index !== ListView.view.count-1) {
                            _lupdate.removeFile(index)
                        }
                    }

                    onTextChanged:  {
                        if(text.length > 1 && index === ListView.view.count-1) {
                            _lupdate.addFile()
                        }
                    }
                    onAccess: {
                        _lupdate.setFiles(index, text)
                    }
                }
            }
            LabelFieldDialog {
                id: _tsFileName
                label: qsTr("Имя файла перевода")
                isPopupButton: false
                onTextChanged: {
                   _lupdate.setTsFileName(text)
                }
            }
            LabelFieldDialog {
                id: _updateFiles
                label: qsTr("Файлы обновления (не обязательно)")
                mode: LabelFieldDialog.Mode.Files
                enabled: _tsFileName.text.length == 0
                filterFile: qsTr("Файлы перевода (*.ts)")
                onTextChanged: {
                    _lupdate.setUpdateFile(text)
                }
            }

            LabelFieldDialog {
                label: qsTr("Языки")
                mode: LabelFieldDialog.Mode.Flags
                flagsModel: Data.modelLanguages
                enabled: _updateFiles.text.length == 0
                onTextChanged: {
                    _lupdate.setLanguage(text)
                }
            }
            CustomButton {
                text: qsTr("Создать")
                onClicked: {
                    _lupdate.createTs()
                }
            }
            CustomButton {
                text: qsTr("Запустить Qt Linguist")
                onClicked: {
                    _lupdate.runLinguist()
                }
            }
        }
    }
}
