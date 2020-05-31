import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

import Components.Dialogs 1.0

Row {
    id: _root
    spacing: 10
    height: 40

    property string label

    property real widthLabel: 150
    property real widthField: 200

    property bool isPopupButton: true
    property bool isClearButton: false
    property bool isPlusButton: false

    property alias text: _field.text
    property alias fieldFocus: _field.focus
    property alias textValidator: _field.validator

    property var flagsModel
    property var librariesModel

    property var filterFile: qsTr("Все файлы (*)")

    enum Mode {
        File,
        Files,
        Folder,
        Flags,
        Libraries
    }
    property int mode: LabelFieldDialog.Mode.Folder

    signal access(var text)
    signal plusClicked()
    signal clearClicked()

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
            if(_root.mode === LabelFieldDialog.Mode.Folder) {
                var item = _folderComponent.createObject(_root)
                if(_field.text.length > 0) {
                    item.folder = "file:///" + _field.text
                }
                item.open()                
            }
            if(_root.mode === LabelFieldDialog.Mode.File) {
                item = _fileComponent.createObject(_root)
                if(_field.text.length > 0) {
                    var buf = _field.text.split("/")
                    buf.pop()
                    item.folder = "file:///" + buf.join("/")
                }
                item.open()
            }
            if(_root.mode === LabelFieldDialog.Mode.Files) {
                item = _fileComponent.createObject(_root)
                item.fileMode = FileDialog.OpenFiles
                if(_field.text.length > 0) {
                    buf = _field.text.split("/")
                    buf.pop()
                    item.folder = "file:///" + buf.join("/")
                }
                item.open()
            }
            if(_root.mode === LabelFieldDialog.Mode.Flags) {
                item = _flagsComponent.createObject(_root, {"flagsList": _field.text.split(" ")})
                item.open()
            }
            if(_root.mode === LabelFieldDialog.Mode.Libraries) {
                var lib = _field.text == "" ? Array() : _field.text.split(" ")
                item = _librariesComponent.createObject(_root, {"librariesList": lib })
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
            _root.clearClicked();
        }
    }
    Button {
        width: 40; height:  parent.height
        visible: _root.isPlusButton
        text: "+"
        onClicked:  {
            _root.plusClicked()
        }
    }
    Component {
        id: _folderComponent
        FolderDialog {
            onAccepted: {                
                _field.text = String(currentFolder).slice(8)
                _root.access(_field.text)
            }
        }
    }
    Component {
        id: _fileComponent
        FileDialog {
            fileMode: FileDialog.OpenFile
            nameFilters: _root.filterFile
            onAccepted: {
                if(fileMode == FileDialog.OpenFile) {
                    _field.text = String(currentFile).slice(8)
                    _root.access(_field.text)
                }
                if(fileMode == FileDialog.OpenFiles) {
                    _field.text = files.map(function (item) {
                        return String(item).slice(8)
                    }).join(" ")
                    _root.access(_field.text)
                }
            }
        }
    }
    Component {
        id: _flagsComponent
        FlagsDialog {
            model: _root.flagsModel
            onApply: {
                _field.text = flags
                _root.access(flags)
                close()
            }
        }
    }    
    Component {
        id: _librariesComponent
        LibrariesDialog {
            model: _root.librariesModel
            onApply: {                
                _field.text = libraries
                _root.access(libraries)
                close()
            }
        }
    }    
}
