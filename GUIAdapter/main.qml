import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0
import QtQml.Models 2.3

import Components.Dialogs 1.0
import "qrc:/GUIAdapter/qml"

ApplicationWindow {
    id: _window
    visible: true
    width: 720
    height: 480
    minimumWidth: 720
    minimumHeight: 360
    title: qsTr("QtAutoTools")

    font {
        pixelSize: 14
        family: "Roboto"
    }

    SettingsDialog {
        visible: true
    }

    Connections {
        target: _guiAdapter
        onStarted: _busyDialog.open()
        onFinished: _busyDialog.finished(exitCode)
        onNewOutputData: _busyDialog.addOutput(line)
        onNewErrorData: _busyDialog.addError(line)
    }



    BusyDialog {
        id: _busyDialog
        onKill: {
            _guiAdapter.kill();
        }
        onApplied: {
            close()
        }
    }






    ObjectModel {
        id: _objTool
        BuildPage {
            width: ListView.view.width
            height: ListView.view.height
            onRun: _guiAdapter.executeTask(task)

        }
        WinDeployQtPage {
            width: ListView.view.width
            height: ListView.view.height
        }
        QmldirPage {
            width: ListView.view.width
            height: ListView.view.height
        }
        LUpdatePage {
            width: ListView.view.width
            height: ListView.view.height
        }
        Settings {
            width: ListView.view.width
            height: ListView.view.height
        }
    }



    /*ListModel {
        id: _toolModel

    }*/


    Rectangle {
        width: 200; height: parent.height
        color: "#4B4B4B"

        ListView {
            id: _list
            width: 200; height: parent.height
            interactive: false
            currentIndex: 0
            model: ["1", "2", "3", "4", "5"]
            delegate: Rectangle {
                width: 200; height: 45
                color: "transparent"
                Label {
                    x: 20
                    width: parent.width-20; height: parent.height
                    verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 18
                    color: "#FFFFFF"
                    text: title
                }
                Rectangle {
                    width: 3; height: 45
                    color: "#39A0FF"
                    visible: parent.ListView.isCurrentItem
                    layer.enabled: true
                    layer.effect: DropShadow {
                        radius: 8
                        samples: 16
                        horizontalOffset: 3
                        color: "#39A0FF"
                    }
                }
                Rectangle {
                    width: parent.width; height: parent.height
                    color: "#808080"
                    opacity: 0.3
                    layer.enabled: true
                    visible: _mouseArea.hovered
                    Rectangle {
                        width: parent.width; height: 1
                        color: "#696969"
                    }
                    Rectangle {
                        y:parent.height-1
                        width: parent.width; height: 1
                        color: "#696969"
                    }
                }

                MouseArea {
                    id: _mouseArea
                    width: parent.width; height: parent.height
                    hoverEnabled: true
                    property bool hovered: false
                    onClicked:  {
                        _toolView.positionViewAtIndex(index, ListView.Center)
                        _list.currentIndex = index
                    }
                    onEntered: hovered = true
                    onExited: hovered = false
                }
            }
        }
    }

  ListView {
       id: _toolView
       x: 200; y:0
       width: parent.width-x; height: parent.height
       snapMode: ListView.SnapOneItem
       interactive: false
       model: _objTool
   }


}