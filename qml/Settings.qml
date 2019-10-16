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

    Worker {
        id: _worker

    }

    Column {
        x: 20; y: 50
        spacing: 20
        SelectFolderRow {
            text: qsTr("Путь к Qt")
            path: _worker.qtPath
        }
        SelectFolderRow {
            text: qsTr("Путь к компилятору")
            path: _worker.compl1Path
        }

        SelectFolderRow {
            text: qsTr("Путь к компилятору Tool")
            path: _worker.compl2Path
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
