import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import LoadingAnimation 1.0

Dialog {
    id: _dialog

    parent: Overlay.overlay
    x:parent.width/2-width/2; y:20
    width: parent.width/2; height: showInfo ? parent.height-40 : 150
    modal: true; dim: true
    padding: 20
    closePolicy: Popup.NoAutoClose
    clip: true

    Behavior on height {
        NumberAnimation { duration: 150 }
    }

    property bool showInfo: false
    property bool isReady: false
    property string info



    function reset() {
        info = ""
        showInfo = false
        isReady = false
    }


    Overlay.modal: Rectangle {
        color: "#DF000000"
    }

    background: Rectangle {
        width: parent.width; height: parent.height
        radius: 10
        color: "#FFFFFF"
        Image {
            x:parent.width-30; y:5
            width: 25; height: 25
            source: "qrc:/icon/exit-black.svg"

        }
    }

    contentItem: Column {
        width: parent.width-40; height: parent.height-40
        spacing: 10
        Flipable {
            id: _flipable
            x: parent.width/2-width/2;
            width: 70; height: 70
            property bool flipped: isReady

            front: LoadingAnimation {
                width: 70; height: 70
                externalColor: "#000000"
                internalColor: "#3A9AF2"
                lineWidth: 2
                internalRadius: externalRadius-5
                running: _dialog.opened && !isReady
            }
            back: Rectangle {
                width: 70; height: 70; radius: 35
                color: _mouseArea.pressed ? "#215A8E" : "#3A9AF2"
                layer.enabled: true
                layer.effect: DropShadow {
                    samples: 16
                    radius: 8
                    verticalOffset: _mouseArea.pressed ? 2 : 4
                    horizontalOffset: _mouseArea.pressed ? 2 : 4
                    color: "#80000000"
                }
                Image {
                    anchors { centerIn: parent; horizontalCenterOffset: 5 }
                    width: 47; height: 27
                    rotation: 270
                    mirror: true
                    source: "qrc:icon/success-white.svg"
                }
                MouseArea {
                    id: _mouseArea
                    anchors.fill: parent
                    onClicked: {
                        _dialog.close()
                    }
                }
            }
            transform: Rotation {
                id: _rotation
                origin.x: _flipable.width
                origin.y: _flipable.height
                axis.x: 1; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
                angle: 0    // the default angle
            }
            states: State {
                name: "back"
                PropertyChanges { target: _rotation; angle: 180 }
                when: _flipable.flipped
            }

            transitions: Transition {
                NumberAnimation { target: _rotation; property: "angle"; duration: 500 }
            }

        }
        Label {
            width: parent.width; height: 20
            horizontalAlignment: Text.AlignHCenter
            text: isReady ? qsTr("Готово") : qsTr("Ждите. Операция выполняется")
        }
        Rectangle {
           width: _dialog.width-40; height: _dialog.height-160
           border { width: 1; color: "#C4C4C4" }
           Flickable {
               id: _flickable
               anchors.fill: parent
               visible: _dialog.showInfo
               //contentWidth: _infoArea.contentWidth
               //contentHeight: _infoArea.contentHeight
               flickableDirection: Flickable.AutoFlickIfNeeded
               ScrollBar.vertical: ScrollBar { }
               ScrollBar.horizontal: ScrollBar {}
               TextArea.flickable: TextArea {
                   id: _infoArea
                   //width: _dialog.width-40; height: _dialog.height-160
                   selectByMouse: true
                   selectionColor: "#3A9AF2"
                   readOnly: true
                   text: info

                   /*background: Rectangle {

                   }*/
               }
           }
        }




        Image {
            x:parent.width/2-width/2; //y: parent.height-20
            width: 20; height: 10
            source: "qrc:/icon/arrow-black.svg"
            rotation: showInfo ? 180 : 0
            MouseArea {
                width: 20; height: 10
                onClicked: {
                    showInfo = !showInfo
                }
            }
        }
    }

}
