import QtQuick 2.12
import QtQuick.Controls 2.5

import "../../"

Dialog {
    id: _taskDialog
    parent: Overlay.overlay
    x:parent.width/2-width/2; y: 20
    width: 2*parent.width/3; height: parent.height - 40
    modal: true; dim: true

    property var task

    signal apply(var task)

    onTaskChanged:  {
        var component = createToolByName(task.tool)
        var item = component.createObject(_toolView)
        item.task = task
        _settingPage.settings = task.environment
        item.height = item.contentItem.height+70
        item.contentItem.heightChanged.connect(function () {
            item.height = item.contentItem.height+70
            _toolView.height = item.height
        })
        item.width = _taskDialog.width
        item.interactive = false
        _toolView.height = item.height
        _toolView.data = item
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
    }

    contentItem: Flickable {
        width: parent.width; height: parent.height
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
                onSaveSettings: apply(_taskDialog.task)
            }
        }

    }
}
