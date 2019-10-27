import QtQuick 2.12
import QtQuick.Controls 2.5

import Components 1.0
import AutoTools 1.0

Item {
    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: "Qmlplugindump"
    }
    BusiDialog {
        id: _busiDialog
    }
    QmlPluginDump {
        id: _qmlplugindump
        onFinished: {
            _busiDialog.close()
        }

    }

    Flickable {
        x: 20; y: 50
        width: parent.width; height: parent.height-y
        contentHeight: _content.height+20
        clip: true
        Column {
            id: _content
            spacing: 20
            SelectFolderRow {
                id: _path
                text: qsTr("Целевая папка")
                onSetPath: {
                    _qmlplugindump.setPath(path)
                }
            }
            CheckBoxRow {
                text: qsTr("Сделать запись о типах в qmldir")
                onCheckedChanged: {
                    _qmlplugindump.setWriteQmlDir(checked)
                }
            }

            Button {
                text: qsTr("Создать")
                onClicked: {
                    _busiDialog.open()
                    _qmlplugindump.dump()
                }
            }
        }
    }
}
