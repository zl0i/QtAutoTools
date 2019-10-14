import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

Item {
    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: "Windeployqt"
    }
    Column {
        x: 20; y: 50
        spacing: 20
        Row {
            spacing: 10
            Label {
                width: 150; height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
                text: "Папка с испольняемым файлом"
            }
            TextField {
                id: _textField
                width: 200; height: 40
            }
            Button {
                width: 40; height: 40
                text: "..."
                onClicked:  {
                    _dialog.open()
                }
            }
        }
        Label {
            width: 100;  height: 40
            verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
            text: qsTr("Флаги")
        }

    }
    FileDialog {
        id: _dialog
        fileMode: FileDialog.OpenFile
        onAccepted: {
            _textField.text = currentFile
        }

    }
}
