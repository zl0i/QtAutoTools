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
            LabelFieldRow {
                label: "Папка с деплоем"
                mode: LabelFieldRow.Mode.Folder
                onTextChanged:  {
                    _finstaller.setDeployPath(text)
                }
            }
            LabelFieldRow {
                label: "Папка установки"
                mode: LabelFieldRow.Mode.Folder
                onTextChanged: {
                    _finstaller.setInstallerPath(text)
                }
            }
            LabelFieldRow {
                label: qsTr("Вендор")
                isPopupButton: false
                text: "com.vendor.example"
                onTextChanged: {
                    _finstaller.setVendorName(text)
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
