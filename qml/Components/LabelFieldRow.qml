import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

Row {
    id: _root
    spacing: 10
    height: 40

    property string label

    property real widthLabel: 150
    property real widthField: 200

    property bool isPopupButton: true
    property bool isClearButton: false

    property alias text: _field.text


    property var flagsModel

    enum Mode {
        File,
        Folder,
        Flags
    }
    property int mode: LabelFieldRow.Mode.Folder

    Label {
        width: widthLabel; height: parent.height
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        text: _root.label
    }
    TextField {
        id: _field
        width: widthField; height:  parent.height
        selectByMouse : true
        selectionColor: "#87CEFA"
        background: Rectangle {
            border { width: parent.focus ? 2 : 1; color: parent.focus ? "#39A0FF" : "#C4C4C4" }
        }
    }
    Button {
        width: 40; height:  parent.height
        visible:  _root.isPopupButton
        text: "..."       
        onClicked:  {
            if(_root.mode === LabelFieldRow.Mode.Folder) {
                var item = _folderComponent.createObject(_root)
                item.open()
                return
            }
            if(_root.mode === LabelFieldRow.Mode.File) {
                item = _fileComponent.createObject(_root)
                item.open()
            }
            if(_root.mode === LabelFieldRow.Mode.Flags) {
                item = _flagsComponent.createObject(_root)
                item.open()
            }
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
    Component {
        id: _folderComponent
        FolderDialog {
            onAccepted: {
                _field.text = String(currentFolder).slice(8)
            }
        }
    }
    Component {
        id: _fileComponent
        FileDialog {
            fileMode: FileDialog.OpenFile
            onAccepted: {
                _field.text = String(currentFile).slice(8)
            }
        }
    }
    Component {
        id: _flagsComponent
        FlagsDialog {
            model: _root.flagsModel
            onSetFlags: {
                _field.text = flags
                close()
            }

        }
    }

}
