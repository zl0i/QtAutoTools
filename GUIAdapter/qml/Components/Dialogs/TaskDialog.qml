import QtQuick 2.12
import QtQuick.Controls 2.5

import "../../"

Dialog {
    id: _taskDialog
    parent: Overlay.overlay
    x: parent.width/2-width/2; y: 20
    width: parent.width-200; height: parent.height - 40
    modal: true; dim: true
    closePolicy: Popup.NoAutoClose

    property var task
    property var page

    signal apply(var task)

    onTaskChanged:  {
        var component = createToolByName(task.tool)
        page = component.createObject(_toolView)
        _flickable.contentY = 0
        if(Object.keys(task).length > 3)
            page.task = task
        else
            page.task.label = task.label

        if(task.environment)
            _settingPage.settings = task.environment

        page.height = page.contentItem.height+70
        page.contentItem.heightChanged.connect(function () {
            page.height = page.contentItem.height+70
            _toolView.height = page.height
        })
        page.width = _taskDialog.width
        page.interactive = false
        _toolView.height = page.height
        _toolView.data = page
    }

    function createToolByName(tool) {
        switch (tool) {
        case "builder":
            return Qt.createComponent("../../BuildPage.qml")
        case "windeployqt":
            return Qt.createComponent("../../WinDeployQtPage.qml")
        case "finstaller":
            return Qt.createComponent("../../InstallerPage.qml")
        case "qmldir":
            return Qt.createComponent("../../QmldirPage.qml")
        case "lupdate":
            return Qt.createComponent("../../LUpdatePage.qml")
        }
    }


    background: Rectangle {
        width: parent.width; height: parent.height; radius: 10
        color: "#FFFFFF"
        MouseArea {
            x: parent.width-width-15; y: 15
            width: 17; height: 17
            onClicked: _taskDialog.close()
            Image {
                width: 13; height: 13
                source: "qrc:/icon/delete-black.svg"
            }
        }
    }

    contentItem: Item {
        width: parent.width; height: parent.height
        Flickable {
            id: _flickable
            anchors { fill: parent; topMargin: 20}
            contentHeight: _settingPage.contentItem.height+_toolView.height+80
            clip: true
            Column {
                width: parent.width
                Item {
                    id: _toolView
                    width: parent.width; height: 100
                }
                SettingsPage {
                    id: _settingPage
                    width: parent.width; height: contentItem.height+80
                    visibleRunButton: false
                    visibleLang: false
                    interactive: false
                    onSaveSettings: {
                        var saveTask = page.task
                        saveTask.environment = settings
                        apply(saveTask)
                    }
                }
            }
        }
    }
}