import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.1


Item {
    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: qsTr("Настройки")
    }

    Column {
        x: 20; y: 50
        spacing: 20
        Row {
            spacing: 10
            Label {
                width: 75; height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                text: "Путь к Qt"
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
    }

    FolderDialog {
        id: _dialog
        onAccepted: {
            _textField.text = String(currentFolder).slice(8)

        }


    }


}
