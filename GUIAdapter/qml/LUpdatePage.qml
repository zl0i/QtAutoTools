import QtQuick 2.12
import QtQuick.Controls 2.5


import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0
import Components.Data 1.0


BasicPage {

    title: "lupdate"
    buttonText: qsTr("Создать")

    task: {
        "tool": "lupdate",
        "files": [""],
        "language": "",
        "translatorName": "",
        "updateFiles": "",
        "runQtLinguist": false
    }


    contentItem: Column {
        id: _content

        spacing: 20
        ListView {
            width: parent.width; height: count * 40 + (count-1) * spacing
            spacing: 20
            model: task.files
            interactive: false
            delegate:  LabelFieldDialog {
                label: qsTr("Переводимые файлы")
                text: modelData
                mode: LabelFieldDialog.Mode.Files
                filterFile: ["Qt Files (*.pro *.qml *.ui *.c *.c++ *.cc *.cpp *.cxx *.ch *.h *.h++ *.hh *.hpp *.hxx)", qsTr("Все файлы (*)")]
                onFieldFocusChanged: {
                    if(!fieldFocus && text == "" && index !== ListView.view.count-1) {
                        task.files.splice(0, index)
                        taskChanged()
                    }
                }

                onTextChanged:  {
                    if(text.length > 1 && index === ListView.view.count-1) {
                        task.files.push("")
                    }
                }
                onAccess: {
                    task.files[index] = text
                    taskChanged()
                }
            }
        }
        LabelFieldDialog {
            id: _tsFileName
            label: qsTr("Имя файла перевода")
            isPopupButton: false
            onTextChanged: {
               task.translatorName = text
            }
        }
        LabelFieldDialog {
            id: _updateFiles
            label: qsTr("Файлы обновления (не обязательно)")
            mode: LabelFieldDialog.Mode.Files
            enabled: _tsFileName.text.length == 0
            filterFile: qsTr("Файлы перевода (*.ts)")
            onTextChanged: {
                task.updateFiles = text
            }
        }

        LabelFieldDialog {
            label: qsTr("Языки")
            mode: LabelFieldDialog.Mode.Flags
            flagsModel: Data.modelLanguages
            enabled: _updateFiles.text.length == 0
            onTextChanged: {
                task.language = text
            }
        }
        LabelCheckBox {
            label: qsTr("Запустить Qt Linguist")
            onCheckedChanged: {
                task.runQtLinguist = checked
            }
        }

    }
    onRun: task.files.pop()

}



