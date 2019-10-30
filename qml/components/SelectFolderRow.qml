import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

Row {
    id: _root
    spacing: 10
    height: 40

    property string text: ""
    property real widthText: 150
    property real widthField: 200

    property bool isFolderButton: true
    property bool isClearButton: false

    property alias path: _field.text

    signal setPath(var path)

    Label {
        width: widthText; height: parent.height
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        text: _root.text
    }
    TextField {
        id: _field
        width: widthField; height:  parent.height
        selectByMouse : true
        selectionColor: "#87CEFA"
        onTextChanged: {
            _root.setPath(text)
        }
    }
    Button {
        width: 40; height:  parent.height
        visible:  _root.isFolderButton
        text: "..."
        onClicked:  {
            _dialog.open()
        }
    }
    Button {
        width: 40; height:  parent.height
        visible: _root.isClearButton
        text: "x"
        onClicked:  {
            _field.clear()
        }
    }
    FolderDialog {
        id: _dialog
        onAccepted: {
            _field.text = String(currentFolder).slice(8)
        }
    }

}
