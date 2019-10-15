import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

Row {
    id: _root
    spacing: 10

    property string text: ""
    property alias path: _field.text

    signal setPath(var path)

    Label {
        width: 150; height: 40
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        text: _root.text
    }
    TextField {
        id: _field
        width: 200; height: 40
        onTextChanged: {
            _root.setPath(text)
        }
    }
    Button {
        width: 40; height: 40
        text: "..."
        onClicked:  {
            _dialog.open()
        }
    }
    FolderDialog {
        id: _dialog
        onAccepted: {
            _field.text = String(currentFolder).slice(8)
        }
    }

}
