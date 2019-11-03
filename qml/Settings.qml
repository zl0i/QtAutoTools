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
            Component.onCompleted: {
                path = _worker.qtPath
            }
            onPathChanged: {
                _worker.qtPath = path
            }
        }
        SelectFolderRow {
            text: qsTr("Путь к компилятору")
            Component.onCompleted: {
                 path = _worker.compilerPath
            }
            onPathChanged: {
                _worker.compilerPath = path

            }
        }

        SelectFolderRow {
            text: qsTr("Путь к компилятору Tool")
            Component.onCompleted: {
                 path = _worker.compilerToolPath
            }
            onPathChanged: {
                _worker.compilerToolPath = path
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
