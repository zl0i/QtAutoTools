import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.1

import AutoTools 1.0
import Components 1.0

Item {

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: qsTr("Настройки")
    }

    Worker { id: _worker  }

    Column {
        x: 20; y: 50
        spacing: 20
        LabelFieldRow {
            label: qsTr("Путь к Qt")
            mode: LabelFieldRow.Mode.Folder
            Component.onCompleted: {
                text = _worker.qtPath
            }
            onTextChanged: {
                _worker.qtPath = text
            }
        }
        LabelFieldRow {
            label: qsTr("Путь к компилятору")
            mode: LabelFieldRow.Mode.Folder
            Component.onCompleted: {
                 text = _worker.compilerPath
            }
            onTextChanged: {
                _worker.compilerPath = text
            }
        }

        LabelFieldRow {
            label: qsTr("Путь к компилятору Tool")
            mode: LabelFieldRow.Mode.Folder
            Component.onCompleted: {
                 text = _worker.compilerToolPath
            }
            onTextChanged: {
                _worker.compilerToolPath = text
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
}
