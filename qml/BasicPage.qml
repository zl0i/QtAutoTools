import QtQuick 2.12
import QtQuick.Controls 2.5

import Components.Controls 1.0
import Components.Dialogs 1.0

Item {
    id: _page

    property string title
    property Item contentItem
    property string buttonText: qsTr("Запустить")
    property alias busiDialog: _busiDialog

    signal run()
    signal kill()

    BusyDialog {
        id: _busiDialog
        onKill: _page.kill()
    }

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: _page.title
    }

    Flickable {
        x: 20; y: 60
        width: parent.width; height: parent.height-y
        contentHeight: _content.height + 100
        interactive: contentHeight > height
        clip: true
        Column {
            id: _content
            x:0; y: 10
            children: _page.contentItem
        }
        CustomButton {
            id: _button
            anchors { top: _content.bottom; topMargin: 20}
            text: _page.buttonText
            onClicked: {
                _busiDialog.reset()
                _page.run()
            }
        }
    }
}
