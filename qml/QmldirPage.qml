import QtQuick 2.12
import QtQuick.Controls 2.5

import Components 1.0
import AutoTools 1.0

Item {

    QmlDir {
        id: _qmldir
        onFinished: {
            _busiDialog.close()
        }
        onError: {
            console.log(str)
            _busiDialog.close()
        }
    }

    BusiDialog {
        id: _busiDialog
    }

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: "qmldir"
    }    

    Flickable {
        x: 20; y: 50
        width: parent.width; height: parent.height-y
        contentHeight: _content.height+20
        clip: true
        Column {
            id: _content
            SelectFolderRow {
                id: _path
                text: qsTr("Целевая папка")
                onSetPath: {
                    _qmldir.setPath(path)
                }
            }


            Button {
                text: qsTr("Создать")
                onClicked: {
                    _busiDialog.open()
                    _qmldir.createModule()
                }
            }
        }
    }
}
