import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

Row {
    id: _root
    spacing: 10
    height: 40

    property string text: ""
    property var model
    property real widthText: 150
    property real widthField: 200

    property bool isFlagsButton: true
    property bool isClearButton: false

    property alias flags: _field.text
    property alias list: _dialog.flagsList

    signal setFlags(var flags)

    Label {
        width: widthText; height: parent.height
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        text: _root.text
    }
    TextField {
        id: _field
        width: 200; height:  parent.height
        selectByMouse: true
        selectionColor: "#87CEFA"
        onTextChanged: {
            _root.setFlags(text)
        }
    }
    Button {
        width: 40; height:  parent.height
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
    SelectFlagsDialog {
        id: _dialog
        model: _root.model
        onSetFlags: {
            //console.log(Array(list).join(' '))
            //_field.text = Array(list).join(" ")
            _field.text = ""
            list.forEach(function(item) {
                _field.text += item + " "
            })
            close()
        }


    }

}
