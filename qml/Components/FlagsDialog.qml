import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Controls 1.0

Dialog {
    id: _dialog

    parent: Overlay.overlay
    x:parent.width/2-width/2; y:20
    width: Math.max(260, parent.width/2); height: parent.height-40
    modal: true; dim: true    
    closePolicy: Popup.NoAutoClose

    property var model


    signal setFlags(var flags)

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
        Label {
            font.pixelSize: 18
            text: qsTr("Флаги")
        }
        ListView {
            id: _flagList
            x: 0; y: 25
            width: parent.width; height: parent.height-65
            clip: true
            model: _dialog.model
            spacing: 10

            property var flagsList: []

            delegate: Item {
                width: parent.width; height: 35
                CheckBox {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 35; height: 35
                    onCheckedChanged: {
                        if(checked) {
                            _flagList.flagsList.push(modelData.name)
                        }
                        else {
                            var pos = _flagList.flagsList.indexOf(modelData.name);
                            _flagList.flagsList.splice(pos, 1)
                        }
                    }
                }
                Label {
                    x: 45; y: 0
                    width: parent.width-x;
                    text: modelData.name
                }
                Label {
                     x: 45; y: 15
                     width: parent.width-x
                     elide: Text.ElideRight
                     text: modelData.description
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

        CustomButton {
            x: parent.width-240; y: parent.height-35
            width: 100
            text: qsTr("Выбрать")
            onClicked: {
                _dialog.setFlags(_flagList.flagsList.join(" "))
            }
        }
        CustomButton {
            x: parent.width-width-20; y: parent.height-35
            width: 100
            text: qsTr("Отмена")
            onClicked: {
                _dialog.close()
            }
        }
    }

}
