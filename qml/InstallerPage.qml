import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.1

import Components 1.0
import Components.Controls 1.0
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
        width: parent.width-40; height: parent.height-y
        contentHeight: _content.height+20
        interactive: contentHeight > height
        clip: true
        Column {
            id: _content
            width: parent.width-20
            spacing: 20
            LabelFieldRow {
                label: qsTr("Папка установки")
                mode: LabelFieldRow.Mode.Folder
                onTextChanged: _finstaller.setPath(text)
            }
            CustomButton {
                text: qsTr("Настройка config файла")
                onClicked: _configDialog.open()
            }
            Row {
                spacing: 20
                Label {
                    height: 30
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("Список компонентов")
                }
                CustomButton {
                    width: 30; height: 30; radius: 15
                    text: qsTr("+")
                    onClicked: {
                        var component = {
                            "name": "component " + (_packagesModel.count + 1),
                            "description": "",
                            "version": "1.0",
                            "dateRelease": "",
                            "vendor": "org.myapp.component",
                            "virtual": false,
                            "license": "",
                            "script": "",
                            "pages": "",
                            "depends": "",
                            "sort": "",
                            "updateText": "",
                            "preDefault": "false",
                            "forsed": false,
                            "replaces": "",
                            "packageFolder": ""
                        }
                        _packagesModel.append(component)
                    }
                }
            }
            ListView {
                width: parent.width; height: contentHeight
                interactive: false
                spacing: -1
                model: _packagesModel
                delegate: Item {
                    id: _delegate
                    width: parent.width; height: 40
                    Row {
                        x: 20
                        width: parent.width-20; height: 40
                        spacing: 10
                        Label {
                            width: parent.width/4; height: 40
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideMiddle
                            text: name
                        }
                        Label {
                            width: parent.width/3; height: 40
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideMiddle
                            text: vendor
                        }
                        Label {
                            width: 40; height: 40
                            verticalAlignment: Text.AlignVCenter
                            text: version
                        }
                        MouseArea {
                            width: 20; height: 40
                            Image {
                                x: 0; y: 10
                                width: 20; height: 20
                                source: "qrc:/icon/folder.svg"
                                layer.enabled: parent.pressed
                                layer.effect: ColorOverlay {
                                    color: "#52ABFF"
                                }
                            }
                            onClicked: _fileDialog.open()
                        }
                        MouseArea {
                            width: 40; height: 40
                            Image {
                                x: 12; y: 8
                                width: 25; height: 25
                                source: "qrc:/icon/gear-black.svg"
                                layer.enabled: parent.pressed
                                layer.effect: ColorOverlay {
                                    color: "#52ABFF"
                                }
                            }
                            onClicked:  _packageDialog.open()
                        }
                    }
                    MouseArea {
                        x: parent.width - width - 10; y: 0
                        width: 21; height: 40
                        Image {
                            x: 0; y: 12
                            width: 21; height: 21
                            visible: _packagesModel.count > 1
                            source: "qrc:/icon/exit-black.svg"
                        }
                        onClicked: _packagesModel.remove(index)
                    }

                    Rectangle {
                        width: parent.width; height: 1
                        color: "#C4C4C4"
                    }
                    Rectangle {
                        x: 0; y: 39
                        width: parent.width; height: 1
                        color: "#C4C4C4"
                    }
                    PackageDialog {
                        id: _packageDialog
                        onApply: {
                            close()
                            _packagesModel.setJsonPackage(index, packag)
                        }
                    }
                    FolderDialog {
                        id: _fileDialog
                        onAccepted: {
                            packageFolder = String(currentFolder).slice(8)
                        }
                    }
                }
            }
            LabelCheckBox {
                label: qsTr("Создать офлайн установщик")
                onCheckedChanged: _finstaller.setCreateOfflineInstaller(checked)
            }
            LabelCheckBox {
                label: qsTr("Создать онлайн установщик")
                onCheckedChanged: _finstaller.setCreateOnlineInstaller(checked)
            }
            LabelCheckBox {
                label: qsTr("Создать репозиторий")
                onCheckedChanged: _finstaller.setCreateRepo(checked)
            }
            CustomButton {
                text: qsTr("Выполнить")
                onClicked: _finstaller.create(_configDialog.config, _packagesModel.getJsonPackages())
            }
        }
    }

    ConfigDialog {
        id: _configDialog
        onApply: close()
    }

    ListModel {
        id: _packagesModel

        function getJsonPackages() {
            var arr = []
            for(var i = 0; i < count; ++i) {
                arr.push(get((i)))
            }
            return arr;
        }

        function setJsonPackage(index, obj) {
            var item = get(index)
            Object.keys(obj).forEach(function (key) {
                item[key] = obj[key]
            })
        }

        ListElement {
            name: "MyApp"
            description: ""
            version: "1.0"
            dateRelease: ""
            vendor: "org.myapp.example"
            virtual: false
            license: ""
            script: ""
            pages: ""
            depends: ""
            sort: ""
            updateText: ""
            preDefault: "false"
            forsed: false
            replaces: ""
            packageFolder: ""
        }
    }
}
