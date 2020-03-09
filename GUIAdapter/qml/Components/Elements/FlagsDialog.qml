import QtQuick 2.13
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

    signal apply(var flags)


    property var flagsList: []



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

            ScrollBar.vertical: ScrollBar {}

            delegate: Item {
                id: _delegate
                width: parent.width; height: 35

                Component.onCompleted: {
                    if(_dialog.flagsList.indexOf(modelData.name) > -1) {
                        _checBox.checked = true
                    }
                }

                CheckBox {
                    id: _checBox
                    anchors.verticalCenter: parent.verticalCenter
                    width: 35; height: 35


                    onCheckedChanged: {
                        if(checked) {
                            var pos = _dialog.flagsList.indexOf(modelData.name)
                            if(pos === -1)
                                _dialog.flagsList.push(modelData.name)
                        }
                        else {
                            pos = _dialog.flagsList.indexOf(modelData.name)
                            if(pos > -1)
                                _dialog.flagsList.splice(pos, 1)
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
                        id: _toolTip
                        x: parent.mouseX; y: parent.mouseY - height - 10
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
            text: qsTr("Применить")
            onClicked: {
                if(flagsList.length === 1)
                    _dialog.apply(_dialog.flagsList[0])
                else
                    _dialog.apply(_dialog.flagsList.join(" "))
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
