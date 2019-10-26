import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

import AutoTools 1.0

import Components 1.0

Item {
    id: _root


    Windeployqt {
        id: _windeployqt
        onFinished: {
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
        text: "Windeployqt"
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
                text: "Папка с испольняемым файлом"
                onSetPath: {
                    //_windeployqt.
                }
            }
            SelectFolderRow {
                text: "dir"
                onSetPath: {
                    _windeployqt.setDir(path)
                }
            }
            SelectFolderRow {
                text: "libdir"
                onSetPath: {
                    _windeployqt.setLibdir(path)
                }
            }
            SelectFolderRow {
                text: "plugindir"
                onSetPath: {
                    _windeployqt.setPlugindir(path)
                }
            }
            SelectFolderRow {
                text: "qmldir"
                onSetPath: {
                    _windeployqt.setQmldir(path)
                }
            }
            SelectFolderRow {
                text: "qmlimport"
                onSetPath: {
                    _windeployqt.setQmlimport(path)
                }
            }
            ArrayFieldRow {
                text: qsTr("Флаги")
                model: Data.modelFlagsWinDeployQt
                onSetFlags: {
                    _windeployqt.setFlags(flags)
                }
            }
            Label {
                width: 100;  height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                text: qsTr("Библиотеки")
            }
            Repeater {
                width: parent.width; height: 300
                model: _root.modelFlags

                delegate: Item {
                    width: _checBox.width; height: 20
                    CheckBox {
                        id: _checBox
                        text: modelData
                    }
                }
            }

            Button {
                text: qsTr("Развернуть")
                onClicked: {
                    _busiDialog.open()
                    _windeployqt.deploy(_path.path)
                }
            }

        }
    }
}
