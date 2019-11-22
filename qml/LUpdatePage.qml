import QtQuick 2.12
import QtQuick.Controls 2.5

import Components 1.0
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
        onFinished: {
            _busyDialog.close()
        }
    }
    BusiDialog {
        id: _busyDialog
    }
    Column {
        x: 20; y: 50
        spacing: 20
        SelectFolderRow {
            text: qsTr("Папка с профайлом")
            onSetPath: {
                _lupdate.setPath(path)
            }
        }
        LabelFieldRow {
            label: qsTr("Языки")
            //model: Data.modelLanguages
            onTextChanged: {
                _lupdate.setLanguage(list)
            }
        }
        Button {
            text: qsTr("Создать")
            onClicked: {
                _lupdate.createTs()
                _busyDialog.open()
            }
        }
        Button {
            text: qsTr("Запустить Qt Linguist")
            onClicked: {
                _lupdate.runLinguist()
            }
        }
    }
}
