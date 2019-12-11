import QtQuick 2.12
import QtQuick.Controls 2.5

import Components 1.0
import Components.Controls 1.0
import AutoTools 1.0

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
    BusiDialog {
        id: _busyDialog
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
                delegate:  LabelFieldRow {
                    label: qsTr("Переводимый файл")
                    text: file
                    mode: LabelFieldRow.Mode.File
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
                        _lupdate.setFile(index, text)
                    }
                }
            }

            LabelFieldRow {
                label: qsTr("Языки")
                mode: LabelFieldRow.Mode.Flags
                flagsModel: Data.modelLanguages
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
