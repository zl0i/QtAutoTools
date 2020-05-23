import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.1

import Components.Elements 1.0
import Components.Controls 1.0
import Components.Dialogs 1.0

BasicPage {

    title: "Qt Installer Framework"
    buttonText: qsTr("Выполнить")
    task: {
        "tool": "finstaller",
        "path": "",
        "config": {
            "Name": "",
            "Version": "1.0",
            "Publisher": "",
            "ProductUrl": "",
            "Title": "",
            "MaintenanceToolName": "",
            "InstallerWindowIcon": "",
            "Logo": "",
            "StartMenuDir": "",
            "TargetDir": "",
            "Arguments": [],
            "RemoteRepositories": {
                "Repository": [
                    {
                        "Enabled": true,
                        "DisplayName": "Example repository",
                        "Url": "http://www.example.com/packages",
                        "Username": "",
                        "Password": ""
                    }
                ]
            }
        },
        "packages": packagesModel,
        "isCreateMixedInstaller": false,
        "isCreateOfflineInstaller": true,
        "isCreateOnlineInstaller": false,
        "isCreateRepository": false
    }

    property bool visibleOnlineInstaller: task.isCreateOnlineInstaller || task.isCreateMixedInstaller || task.isCreateRepository

    property var remoteRepository: [
        {
            "Enabled": true,
            "DisplayName": "Example repository",
            "Url": "http://www.example.com/packages",
            "Username": "",
            "Password": ""
        }
    ]

    property var packagesModel: [
        {
            "DisplayName": "mainComponent",
            "Description": "",
            "Version": "1.0",
            "ReleaseDate": new Date().toLocaleDateString(Qt.locale(), "yyyy-MM-dd"),
            "Name": "org.myapp.component",
            "Virtual": "",
            "Licenses": [],
            "Script": "",
            "UserInterfaces": [],
            "Dependencies": "",
            "SortingPriority": "",
            "UpdateText": "",
            "Default": "false",
            "ForcedInstallation": false,
            "Replaces": "",
            "packageFolder": ""
        }
    ]

    function getJsonPackages() {
        var arr = []
        for(var i = 0; i < count; ++i) {
            arr.push(get((i)))
        }
        return arr;
    }

    function setJsonPackage(index, obj) {
        var item = packagesModel[index]
        Object.keys(obj).forEach(function (key) {
            item[key] = obj[key]
        })
    }


    contentItem: Column {
        spacing: 20
        LabelFieldDialog {
            label: qsTr("Папка установки")
            mode: LabelFieldDialog.Mode.Folder
            text: task.path
            onTextChanged: task.path = text

        }
        CustomButton {
            text: qsTr("Настройка config файла")
            onClicked: _configDialog.open()
        }
        LabelCheckBox {
            label: qsTr("Онлайн установщик")
            checked: task.isCreateOnlineInstaller
            onCheckedChanged: {
                visibleOnlineInstaller = checked
                task.isCreateOnlineInstaller = checked
            }
        }
        Row {
            visible: visibleOnlineInstaller
            spacing: 20
            Label {
                height: 30
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Список репозиториев")
            }
            CustomButton {
                width: 30; height: 30; radius: 15
                text: "+"
                onClicked: {
                    var obj = {
                        "Enabled": true,
                        "DisplayName": "Example repository",
                        "Url": "http://www.example.com/packages",
                        "Username": "",
                        "Password": ""
                    }
                    task.config.RemoteRepositories.Repository.push(obj)
                    taskChanged()
                }
            }
        }
        ListView {
            width: parent.width; height: contentHeight
            interactive: false
            spacing: -1
            visible: visibleOnlineInstaller
            model: task.config.RemoteRepositories.Repository
            delegate: Item {
                width: parent.width; height: 40
                Row {
                    x: 20
                    width: parent.width-20; height: 40
                    spacing: 10
                    CheckBox {
                        width: 40; height: 40
                        checked: modelData.Enabled
                    }

                    Label {
                        width: parent.width/4; height: 40
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideMiddle
                        text: modelData.DisplayName
                    }
                    Label {
                        width: parent.width/3; height: 40
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideMiddle
                        text: modelData.Url
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
                        onClicked:  _repositoryDialog.open()
                    }
                }
                RepositoryDialog {
                    id: _repositoryDialog
                    repository: task.config.RemoteRepositories.Repository[index]
                    onApply: {
                        close()
                        task.config.RemoteRepositories.Repository[index] = repository
                        taskChanged()
                    }
                }
                MouseArea {
                    x: parent.width - width - 10; y: 0
                    width: 21; height: 40
                    visible: remoteRepository.length > 1
                    Image {
                        x: 0; y: 12
                        width: 21; height: 21
                        source: "qrc:/icon/exit-black.svg"
                    }
                    onClicked: {
                        task.config.RemoteRepositories.Repository.splice(index, 1)
                        taskChanged()
                    }
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
            }
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
                text: "+"
                onClicked: {
                    var component = {
                        "DisplayName": "component ",
                        "Description": "",
                        "Version": "1.0",
                        "ReleaseDate": new Date().toLocaleDateString(Qt.locale(), "yyyy-MM-dd"),
                        "Name": "org.myapp.component",
                        "Virtual": "",
                        "Licenses": [],
                        "Script": "",
                        "UserInterfaces": [],
                        "Dependencies": "",
                        "SortingPriority": "",
                        "UpdateText": "",
                        "Default": "false",
                        "ForcedInstallation": false,
                        "Replaces": "",
                        "packageFolder": ""
                    }
                    task.packages.push(component)
                    taskChanged()
                }
            }
        }
        ListView {
            width: parent.width; height: contentHeight
            interactive: false
            spacing: -1
            model: task.packages
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
                        text: modelData.DisplayName
                    }
                    Label {
                        width: parent.width/3; height: 40
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideMiddle
                        text: modelData.Name
                    }
                    Label {
                        width: 40; height: 40
                        verticalAlignment: Text.AlignVCenter
                        text: modelData.Version
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
                    visible: task.packages.length > 1
                    Image {
                        x: 0; y: 12
                        width: 21; height: 21
                        source: "qrc:/icon/exit-black.svg"
                    }
                    onClicked: {
                        task.packages.splice(index, 1)
                        taskChanged()
                    }
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
                    packag: task.packages[index]
                    onApply: {
                        close()
                        task.packages[index] = packag
                        taskChanged()
                    }
                }
                FolderDialog {
                    id: _fileDialog
                    onAccepted: {
                        packagesModel[index].packageFolder = String(currentFolder).slice(8)
                    }
                }
            }
        }
        LabelCheckBox {
            label: qsTr("Создать смешанный установщик")
            checked: task.isCreateMixedInstaller
            visible: visibleOnlineInstaller
            onCheckedChanged: task.isCreateMixedInstaller = checked
        }
        LabelCheckBox {
            label: qsTr("Создать оффлайн установщик")
            checked: task.isCreateOfflineInstaller
            enabledCheckBox: visibleOnlineInstaller
            onCheckedChanged: task.isCreateOfflineInstaller = checked
        }
        LabelCheckBox {
            visible: visibleOnlineInstaller
            label: qsTr("Создать онлайн установщик")
            checked: task.isCreateOnlineInstaller
            onCheckedChanged: task.isCreateOnlineInstaller = checked
        }
        LabelCheckBox {
            visible: visibleOnlineInstaller
            label: qsTr("Создать репозиторий")
            checked: task.isCreateRepository
            onCheckedChanged: task.isCreateRepository = checked
        }
    }

    ConfigDialog {
        id: _configDialog
        config: task.config
        onApply: {
            task.config = config
            close()
        }
    }

    onRun: {
        //task.packages = packagesModel
    }

}
