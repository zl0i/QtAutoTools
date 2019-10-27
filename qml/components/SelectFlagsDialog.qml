import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Dialog {
    id: _dialog

    parent: Overlay.overlay
    x:parent.width/2-width/2; y:parent.height/2-height/2
    width: 300; height: 400
    modal: true; dim: true
    padding: 0
    closePolicy: Popup.NoAutoClose

    property var model
    property var flagsList: []

    signal setFlags(var list)

    Overlay.modal: Rectangle {
        color: "#DF000000"
    }

    background: Rectangle {
        width: parent.width; height: parent.height
        radius: 10
        color: "#FFFFFF"
    }

    contentItem: Item {
        width: parent.width; height: parent.height
        ListView {
            y: 10
            width: parent.width; height: parent.height-y-60
            clip: true
            model: _dialog.model
            delegate: Item {
                width: parent.width; height: 40
                CheckBox {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 40; height: 40
                    onCheckedChanged: {
                        if(checked) {
                            _dialog.flagsList.push(modelData.name)
                        }
                        else {
                            var pos = flagsList.indexOf(modelData.name);
                            flagsList.splice(pos, 1)
                        }
                    }
                }
                Label {
                    x: 45
                    width: parent.width-x; height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    text: modelData.name
                }
                MouseArea {
                    x: 45
                    width: parent.width-x; height: parent.height
                    hoverEnabled: true
                    property bool hovered: false
                    onEntered: hovered = true
                    onExited: hovered = false
                    CustomToolTip {
                        visible: parent.hovered
                        delay: 500
                        text: modelData.description
                    }
                }
            }
        }

        Rectangle {
            x: 0; y: parent.height-60
            width: parent.width; height: 1
            color: "#828282"
        }
        Button {
            x: 20; y: parent.height-50
            text: qsTr("Сохранить")
            onClicked: {
                _dialog.setFlags(_dialog.flagsList)
            }
        }
        Button {
            x: parent.width-width-20; y: parent.height-50
            text: qsTr("Отмена")
            onClicked: {
                _dialog.close()
            }
        }
    }

}
