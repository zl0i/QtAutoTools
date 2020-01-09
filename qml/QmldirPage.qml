import QtQuick 2.12
import QtQuick.Controls 2.5

import AutoTools 1.0

import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0


Item {

    QmlDir {
        id: _qmldir
        onStarted: {
            _busiDialog.reset()
            _busiDialog.open()
        }
        onFinished: {

            if(exitCode !== 0)
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
        onKill:  _qmldir.kill()
    }

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: "QmlDir"
    }

    Flickable {
        x: 20; y: 50
        width: parent.width-40; height: parent.height-y
        contentHeight: _content.height+20
        interactive: contentHeight > height
        clip: true
        Column {
            id: _content
            width: parent.width
            spacing: 20
            LabelFieldRow {
                label: qsTr("Папка с компонентами")
                onAccess:  {
                    _qmldir.setPath(text)
                }
            }
            ListView {
                id: _listFiles
                width: parent.width
                height: count * 40 + (count-1) * spacing
                spacing: 15
                model: _qmldir.files
                delegate: Row {
                    id: _delegate
                    width: parent.width; height: 40
                    spacing: 15
                    property var row: index
                    ComboBox {
                        id: _typesBox
                        width: 120
                        model: types
                        onActivated: {
                            if(currentText == "internal" )
                                _versionLabel.text = ""
                            else
                                _versionLabel.text = _versionLabel.lastVersion

                            _qmldir.setTypeByIndex(parent.row, currentText)
                        }
                    }
                    TextField {
                        id: _nameLabel
                        width: 120; height: 40
                        text: name
                        onTextChanged: _qmldir.setNameByIndex(parent.row, text)
                    }
                    TextField {
                        id: _versionLabel
                        width: 40; height: 40
                        text: version
                        validator: RegExpValidator { regExp: /[0-9]{1,2}[.]{1}[0-9]{1,2}/}
                        enabled: !(_typesBox.currentText == "internal" || extension == "dll" || extension == "so")
                        property string lastVersion: text !== "" ? text : lastVersion
                        onTextChanged:  {
                            _qmldir.setVersionByIndex(parent.row, text)
                        }
                    }
                    TextField {
                        width: 150; height: 40
                        readOnly: true
                        text: file
                    }
                }
            }
            LabelCheckBox {
                label: qsTr("Создать запись о типах qmldir")
                onCheckedChanged: {
                    _qmldir.setCreateTypes(checked)
                }
            }
            LabelCheckBox {
                label: qsTr("Поддержка Qt Quick Designer")
                onCheckedChanged: {
                    _qmldir.setSupportDesigner(checked)
                }
            }

            CustomButton {
                text: qsTr("Создать")
                enabled: _listFiles.count !== 0
                onClicked: {
                    _qmldir.createModule()
                }
            }
        }
    }
}
