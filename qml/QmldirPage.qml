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
            spacing: 20
            SelectFolderRow {
                id: _path
                text: qsTr("Целевая папка")
                onSetPath: {
                    _qmldir.setPath(path)
                }
            }
            Row {
                spacing: 10
                height: 40
                Label {
                    width: 150; height: parent.height
                    verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                    text: qsTr("Версия")
                }
                TextField {
                    id: _majorField
                    width: 40; height:  parent.height
                    selectByMouse : true
                    selectionColor: "#87CEFA"
                    validator: IntValidator {bottom: 1; top: 99}
                     horizontalAlignment: Text.AlignHCenter
                    text: "1"
                    onTextChanged: {
                        _qmldir.setMajorVersion(Number(text))
                    }
                }
                Label {
                    height: parent.height
                    verticalAlignment: Text.AlignBottom; horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    text: "."
                }
                TextField {
                    id: _minorField
                    width: 40; height:  parent.height
                    selectByMouse : true
                    selectionColor: "#87CEFA"
                    validator: IntValidator {bottom: 0; top: 99}
                    horizontalAlignment: Text.AlignHCenter
                    text: "0"
                    onTextChanged: {
                        _qmldir.setMinorVersion(Number(text))
                    }
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
