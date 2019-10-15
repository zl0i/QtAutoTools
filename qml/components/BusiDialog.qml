import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Dialog {
    id: _dialog

    parent: Overlay.overlay
    x:parent.width/2-width/2; y:parent.height/2-height/2
    width: 240; height: 150
    modal: true; dim: true
    padding: 0
    closePolicy: Popup.NoAutoClose



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
        BusyIndicator {
            x: parent.width/2-width/2; y: 30
            running: true
        }
        Label {
            x: parent.width/2-width/2; y: parent.height-height - 20
            text: qsTr("Ждите. Операция выполняется")
        }


    }

}
