import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

import AutoTools 1.0

import "qrc:/qml/components"

Item {
    id: _root
    readonly property var modelFlags: ["--debug", "--release", "--pdb", "--force", "--dry-run", "--no-patchqt",
        "--no-plugins", "--no-libraries", "--no-quick-import", "--no-translations", "--no-system-d3d-compiler",
        "--compiler-runtime", " --no-compiler-runtime", "--webkit2", "--no-webkit2", "--json", "--angle", "--no-angle", "--no-opengl-sw"]

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
        contentHeight: _conten.height+20
        clip: true
        Column {
            id: _conten
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
            Label {
                width: 100;  height: 40
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                text: qsTr("Флаги")
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
