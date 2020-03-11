import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Controls 1.0
import Components.Dialogs 1.0

Item {
    id: _page

    property string title
    property Item contentItem
    property bool visibleRunButton: true
    property string buttonText: qsTr("Запустить")
    property bool visibleScriptButton: true
    property alias interactive: _flickable.interactive


    property var task: ({})
    signal run(var task)
    signal saveScript(var add, var script)

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: _page.title
    }

    Flickable {
        id: _flickable
        x: 20; y: 60
        width: parent.width; height: parent.height-y
        contentHeight: _content.height + 100
        interactive: contentHeight > height
        clip: true
        Column {
            id: _content
            x:0; y: 10
            children: _page.contentItem
        }
        Row {
            anchors { top: _content.bottom; topMargin: 20}
            spacing: 10
            CustomButton {
                visible: visibleRunButton
                text: _page.buttonText
                onClicked: {
                    _page.run(task)
                }
            }
            CustomButton {
                width: 40; height: 40
                visible: visibleScriptButton
                onClicked:  _popup.open() //_page.saveScript()
                Popup {
                    id: _popup
                    x: 20; y: 20
                    width: 120; height: 50
                    padding: 0
                    background: Rectangle {
                        width: 120; height: 50; radius: 10
                        layer.enabled: true
                        layer.effect: DropShadow {
                            radius: 8
                            samples: 16
                        }
                    }
                    contentItem: Column {
                        width: 120; height: 50
                        MouseArea {
                            width: 120; height: 24
                            hoverEnabled: true
                            property bool hovered: false
                            onEntered: hovered = true
                            onExited: hovered = false
                            onClicked: {
                                _page.saveScript(true, task)
                                _popup.close()
                            }
                            Label {
                                width: 120; height: 19
                                leftPadding: 10
                                verticalAlignment: Text.AlignVCenter
                                color: parent.hovered ? (parent.pressed ? "#3E5FB8" : "#39A0FF") : "#000000"
                                text: qsTr("Добавить к ...")
                            }
                        }
                        Rectangle {
                            width: 120; height: 1
                            color: "#C4C4C4"
                        }
                        MouseArea {
                            width: 120; height: 24
                            hoverEnabled: true
                            property bool hovered: false
                            onEntered: hovered = true
                            onExited: hovered = false
                            onClicked: {
                                _page.saveScript(false, task)
                                _popup.close()
                            }
                            Label {
                                width: 120; height: 19
                                leftPadding: 10
                                verticalAlignment: Text.AlignVCenter
                                color: parent.hovered ? (parent.pressed ? "#3E5FB8" : "#39A0FF") : "#000000"
                                text: qsTr("Создать новый")
                            }
                        }
                    }
                }
            }
        }
    }
}
