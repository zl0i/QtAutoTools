import QtQuick 2.12
import QtQuick.Controls 2.5


import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0


BasicPage {

    title: "QmlDir"
    buttonText: qsTr("Создать")

    task: {
        "tool": "qmldir",
        "path": "",
        "files": [],
        "qmltypes": false,
        "supportDesigner": false
    }

    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Файлы")
            mode: LabelFieldDialog.Mode.Files
            onAccess:  {

                task.files = []
                var array = text.split(" ")

                for(var i = 0; i < array.length; i++) {
                    var fileName = array[i].split("/")[array[i].split("/").length-1];


                    var name = fileName.split(".")[0]
                    var extension = fileName.split(".")[1]

                    task.files.push({
                                       "type": "",
                                       "version": "1.0",
                                       "name": name,
                                       "extension": extension,
                                       "path": array[i]
                                   })
                }

                taskChanged()

                var dirName = array[0].split("/")

                dirName.pop()
                this.text = dirName.join("/")
                task.path = dirName.join("/")

            }
        }
        ListView {
            id: _listFiles
            width: parent.width
            height: count * 40 + (count-1) * spacing
            spacing: 15
            model: task.files
            delegate: Row {
                id: _delegate
                width: parent.width; height: 40
                spacing: 15
                property var row: index
                ComboBox {
                    id: _typesBox
                    width: 120
                    model: ["", "internal", "singleton"]
                    onActivated: {
                        if(currentText == "internal" )
                            _versionLabel.text = ""
                        else
                            _versionLabel.text = _versionLabel.lastVersion

                        task.files[row].type = currentText
                    }
                }
                TextField {
                    id: _nameLabel
                    width: 120; height: 40
                    text: modelData.name
                    onTextChanged: task.files[row].name = text
                }
                TextField {
                    id: _versionLabel
                    width: 40; height: 40
                    text: modelData.version
                    validator: RegExpValidator { regExp: /[0-9]{1,2}[.]{1}[0-9]{1,2}/}
                    enabled: !(_typesBox.currentText == "internal" || modelData.extension === "dll" || modelData.extension === "so")
                    property string lastVersion: text !== "" ? text : lastVersion
                    onTextChanged:  {
                        task.files[row].version = text
                    }
                }
                TextField {
                    width: 150; height: 40
                    readOnly: true
                    enabled: _typesBox.currentText !== "internal"
                    text: modelData.name
                }
            }
        }
        LabelCheckBox {
            label: qsTr("Создать запись о типах qmldir")
            onCheckedChanged: {
                task.qmltypes = checked
            }
        }
        LabelCheckBox {
            label: qsTr("Поддержка Qt Quick Designer")
            onCheckedChanged: {
                task.supportDesigner = checked
            }
        }
    }

    onRun: console.log(JSON.stringify(task))


}
