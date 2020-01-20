import QtQuick 2.12
import QtQuick.Controls 2.5

import AutoTools 1.0

import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0


BasicPage {

    title: "QmlDir"
    buttonText: qsTr("Создать")

    QmlDir {
        id: _qmldir
        onStarted: busiDialog.open()
        onFinished: busiDialog.finished(exitCode)
        onNewOutputData: busiDialog.addOutput(line)
        onNewErrorData: busiDialog.addError(line)
    }

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
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
    }

    onRun: _qmldir.createModule()
    onKill: _qmldir.kill()

}
