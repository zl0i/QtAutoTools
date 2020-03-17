import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Popup {
    id: _popup
    width: 120; height: 50
    padding: 0

    signal addScript()
    signal newScript()

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
                _popup.addScript()
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
                _popup.newScript()
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
