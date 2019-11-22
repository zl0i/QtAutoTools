import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import LoadingAnimation 1.0
import Components.Controls 1.0

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
    property bool errorProcess: false
    property string info




    function reset() {
        info = ""        
        isReady = false
        errorProcess = false
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
        FlipButton {
            width: 70; height: 70
            isError: errorProcess
            flipped: isReady
            runningAnimation: _dialog.opened && !isReady
            onClicked: {
                _dialog.close()
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
               flickableDirection: Flickable.AutoFlickIfNeeded
               ScrollBar.vertical: ScrollBar {}
               ScrollBar.horizontal: ScrollBar {}
               TextArea.flickable: TextArea {
                   id: _infoArea                   
                   font.pixelSize: 12
                   selectByMouse: true
                   selectionColor: "#3A9AF2"
                   readOnly: true
                   text: info                  
                   textFormat: TextEdit.RichText
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
