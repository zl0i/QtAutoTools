import QtQuick 2.12
import QtQuick.Controls 2.5

import "../../"
import Components.Controls 1.0
import Components.Elements 1.0

Dialog {
    id: _taskDialog
    parent: Overlay.overlay
    x: parent.width/2-width/2; y: 20
    width: parent.width-200; height: parent.height - 40
    padding: 0
    modal: true; dim: true
    closePolicy: Popup.NoAutoClose

    property var task
    property var page
    property var labelTasks: []

    signal apply(var task)

    onTaskChanged:  {
        var component = createToolByName(task.tool)
        page = component.createObject(_toolView)
        _flickable.contentY = 0
        if(Object.keys(task).length > 3)
            page.task = task
        else
            page.task.label = task.label        

        page.visibleRunButton = false
        page.visibleScriptButton = false
        page.height = page.contentItem.height+70
        page.contentItem.heightChanged.connect(function () {
            page.height = page.contentItem.height+70
            _toolView.height = page.height
        })
        page.width = _taskDialog.width
        page.interactive = false

        if(task.environment)
            _settingPage.settings = task.environment

        page.y = -30
        _toolView.height = page.height
        _toolView.data = page        
    }

    function createToolByName(tool) {
        switch (tool) {
        case "builder":
            return Qt.createComponent("../../BuildPage.qml")
        case "windeployqt":
            return Qt.createComponent("../../WinDeployQtPage.qml")
        case "qt installer framework":
            return Qt.createComponent("../../InstallerPage.qml")
        case "qmldir":
            return Qt.createComponent("../../QmldirPage.qml")
        case "lupdate":
            return Qt.createComponent("../../LUpdatePage.qml")
        case "console":
            return Qt.createComponent("../../ConsolePage.qml")
        }
    }

    onOpened: {
        labelTasks.unshift("")        
        labelTasksChanged()

        if(task)
            _dependenceBox.currentIndex = labelTasks.indexOf(task.dependence)
    }


    background: Rectangle {
        width: parent.width; height: parent.height; radius: 10
        color: "#FFFFFF"
    }
    ImageButton {
        x: parent.width-30; y: 5
        width: 25; height: 25
        image: "qrc:/icon/exit-black.svg"
        onClicked: {
            _taskDialog.close()
        }
    }

    contentItem: Item {
        width: parent.width; height: parent.height
        Flickable {
            id: _flickable
            anchors { fill: parent; margins: 10}
            contentHeight: _settingPage.contentItem.height+_toolView.height+220
            clip: true
            Column {
                width: parent.width
                spacing: 10
                Row {
                    x: 20
                    spacing: 10
                    Label {
                        height: 40
                        verticalAlignment: Text.AlignVCenter
                        //font.pixelSize: 14
                        text: qsTr("Название задачи:")
                    }
                    TextField {
                        width: contentWidth+20 < 200 ? contentWidth+20 : 200; height: 40
                        font { pixelSize: 18; bold: true }
                        text: task ? task.label : ""
                        selectByMouse: true
                        selectionColor: "#39A0FF"
                        selectedTextColor: "#FFFFFF"
                        padding: 0
                        onTextChanged: _taskDialog.task.label = text
                        background: Item {
                            width: parent.width; height: parent.height
                            Rectangle {
                                y: parent.height-2
                                width: parent.width; height: 1
                                color: "#1A1A1A"
                            }
                        }
                    }
                }


                Item {
                    id: _toolView
                    width: parent.width; height: 100
                }
                Label {
                    x: 20
                    font { pixelSize: 18; weight: Font.Bold }
                    text: qsTr("Зависимости")
                }

                LabelComboBox {
                    id: _dependenceBox
                    x: 20; width: parent.width-80
                    label: qsTr("Зависит от")
                    model: labelTasks
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
                        saveTask.dependence = _dependenceBox.currentText
                        apply(saveTask)
                    }
                }
            }
        }
    }
}
