import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

import Components.Controls 1.0
import Components.Dialogs 1.0

Rectangle {
    id: _delegate


    property string name
    property alias hovered: _mouseArea.hovered
    property alias mouseArea: _mouseArea
    property alias openedConfirmDialog: _confirmDialog.opened

    signal runScript(var name)
    signal openScript(var name)
    signal removeScript(var name)

    signal pressed()
    signal released()

    function isFirst() {
        return index == 0
    }

    Rectangle {
        x: 5
        width: parent.width-10
        height: 1
        color: "#A1A1A1"
        opacity: 0.5
        visible: !isFirst()
    }

    Label {
        x: 20
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        text: _delegate.name
    }

    MouseArea {
        id: _mouseArea
        width: parent.width; height: parent.height
        hoverEnabled: true
        property bool hovered: false

        onEntered: hovered = true
        onExited: hovered = false
        onPressed: _delegate.pressed()
        onReleased: _delegate.released()
    }
    ImageButton {
        x: parent.width-width-60; y: parent.height/2 - height/2
        width: 17; height: 17
        imageWidth: 13; imageHeight: 13
        image: "qrc:/icon/delete-black.svg"
        onClicked: _confirmDialog.show("delete", qsTr("Удалить скрипт %1?").arg(name))
        ConfirmDialog {
            id: _confirmDialog
            onAccept: {
                _delegate.removeScript(name)
                close()
            }
            onCancel: close()
        }
    }
    RunButton {
        x: parent.width-width-30; y: parent.height/2 - height/2
        onClicked: _delegate.runScript(name)
        onEntered: _mouseArea.hovered = true
    }


}
