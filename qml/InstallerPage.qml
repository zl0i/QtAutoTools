import QtQuick 2.12
import QtQuick.Controls 2.5

import Components 1.0
import AutoTools 1.0

Item {
    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: "Qt Installer Framework"
    }
    FInstaller {
        id: _finstaller
        onFinished: {
            _busyDialog.close()
        }
    }
    BusiDialog {
        id: _busyDialog
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
                text: "Папка с деплоем"
                onSetPath: {
                    _finstaller.setDeployPath(path)
                }
            }
            SelectFolderRow {
                text: "Папка установки"
                onSetPath: {
                    _finstaller.setInstallerPath(path)
                }
            }
            SelectFolderRow {
                text: qsTr("Вендор")
                isFolderButton: false
                path: "com.vendor.example"
                onSetPath: {
                    _finstaller.setVendorName(path)
                }
            }
            Row {
                spacing: 20
                Button {
                    text: qsTr("Создать config")
                    onClicked: {
                        _finstaller.createConfig()
                    }
                }
                Button {
                    text: qsTr("Создать packages")
                    onClicked: {
                        _finstaller.createPackages()
                    }
                }
            }
            Button {
                text: qsTr("Создать офлайн инсталятор")
                onClicked:  {
                     _busyDialog.open()
                    _finstaller.createOffInstaller()
                }
            }
        }
    }
}
