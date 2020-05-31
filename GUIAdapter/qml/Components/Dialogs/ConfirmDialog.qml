import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.14
import QtGraphicalEffects 1.0

import Components.Controls 1.0

Dialog {
    id: _dialog

    parent: Overlay.overlay
    x: parent.width/2 - width/2; y:parent.height/2 - height/2
    width: 280; height: 120
    padding: 0
    modal: true; dim: true
    closePolicy: Popup.NoAutoClose

    property string mode: "info"
    property string info: ""
    signal accept()
    signal cancel()

    function show(mode, info) {
        _dialog.mode = mode
        _dialog.info = info
        _dialog.open()
    }

    StateGroup {
        state: _dialog.mode
        states: [
            State {
                name: "info"
                PropertyChanges {
                    target: _cancelButton
                    visible: false
                }
                PropertyChanges {
                    target: _okButton
                    style: "blue"
                }
            },
            State {
                name: "confirm"
                PropertyChanges {
                    target: _cancelButton
                    visible: true
                    style: "red"
                }
                PropertyChanges {
                    target: _okButton
                    style: "blue"
                }
            },
            State {
                name: "delete"
                PropertyChanges {
                    target: _cancelButton
                    visible: true
                    style: "blue"
                }
                PropertyChanges {
                    target: _okButton
                    style: "red"
                }
            }
        ]
    }

    Overlay.modal: Rectangle { color: "#80000000" }

    background: Rectangle {
        width: 280; height: 120; radius: 10
        color: "#FFFFFF"
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 8
            samples: 16
            color: "#80000000"
        }
    }

    contentItem: Item {
        Label {
            x: 20; y: 20
            width: parent.width-40; height: 35
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            text: info
        }

        Row {
            x: parent.width/2 - width/2; y: parent.height-height-15
            spacing: 20
            CustomButton {
                id: _cancelButton
                width: 100
                text: qsTr("Отмена")
                onClicked:  _dialog.cancel()
            }
            CustomButton {
                id: _okButton
                width: 100
                text: qsTr("Ок")
                onClicked: _dialog.accept()
            }
        }
    }
}
