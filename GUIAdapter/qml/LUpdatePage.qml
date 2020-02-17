import QtQuick 2.12
import QtQuick.Controls 2.5


import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0
import Components.Data 1.0


BasicPage {


    title: "lupdate"
    buttonText: qsTr("Запустить Qt Linguist")

    task: {
        "tool": "lupdate",
        "files": [
                "G:\Projects\Qt\QtAutoTools\TestQmlDir\BuilderPage.qml"
                ],
        "language": "ru eu ua",
        "translatorName": "main",
        "updateFiles": "G:/Projects/Qt/QtAutoTools/QtAutoTools/GUIAdapter/translation/ts_files/QtAutoTools_en.ts"
    }


    contentItem: Column {
        id: _content

        spacing: 20
        ListView {
            width: parent.width; height: count * 40 + (count-1) * spacing
            spacing: 20
            //model: _lupdate.files
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
                //_lupdate.createTs()
            }
        }
    }
    //onRun: _lupdate.runLinguist()

}



