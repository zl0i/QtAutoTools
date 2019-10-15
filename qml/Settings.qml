import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.1

import AutoTools 1.0

Item {
    property var currentField: _textField

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: qsTr("Настройки")
    }

    Worker {
        id: _worker

    }

    Column {
        x: 20; y: 50
        spacing: 20
        Row {
            spacing: 10
            Label {
                width: 150; height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                text: "Путь к Qt"
            }
            TextField {
                id: _textField
                width: 200; height: 40
                text: _worker.qtPath
            }
            Button {
                width: 40; height: 40
                text: "..."
                onClicked:  {
                    currentField = _textField
                    _dialog.open()
                }
            }
        }
        Row {
            spacing: 10
            Label {
                width: 150; height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                text: "Путь к компилятору"
            }
            TextField {
                id: _compl1Field
                width: 200; height: 40
                text: _worker.compl1Path
            }
            Button {
                width: 40; height: 40
                text: "..."
                onClicked:  {
                    currentField = _compl1Field
                    _dialog.open()
                }
            }
        }
        Row {
            spacing: 10
            Label {
                width: 175; height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                text: "Путь к компилятору Tool"
            }
            TextField {
                id: _compl2Field
                width: 200; height: 40
                text: _worker.compl2Path
            }
            Button {
                width: 40; height: 40
                text: "..."
                onClicked:  {
                    currentField = _compl2Field
                    _dialog.open()
                }
            }
        }
        Row {
            spacing: 10
            Label {
                width: 75; height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                text: qsTr("Язык")
            }
            ComboBox {
                model: ["Русский", "English"]
            }
        }
        Button {
            text: qsTr("Удалить все настройки")
            onClicked: {
                _worker.clearAllSettings()
            }
        }
    }

    FolderDialog {
        id: _dialog
        onAccepted: {
            switch (currentField) {
            case _textField:
                _worker.qtPath = String(currentFolder).slice(8)
                break;
            case _compl1Field :
                _worker.compl1Path = String(currentFolder).slice(8)
                break;

            case _compl2Field:
                _worker.compl2Path = String(currentFolder).slice(8)
                break;
            }
        }
    }
}
