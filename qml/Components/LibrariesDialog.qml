import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Controls 1.0

Dialog {
    id: _dialog

    parent: Overlay.overlay
    x:parent.width/2-width/2; y:20
    width: Math.max(260, parent.width/2); height: parent.height-40
    modal: true; dim: true
    closePolicy: Popup.NoAutoClose

    property var model

    signal apply(var libraries)

    property var librariesList: []

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
        Label {
            font.pixelSize: 18
            text: qsTr("Библиотеки")
        }
        ListView {
            id: _librariesList
            x: 0; y: 25
            width: parent.width; height: parent.height-65
            clip: true
            model: _dialog.model
            spacing: 10

            ScrollBar.vertical: ScrollBar {}

            delegate: Item {
                width: parent.width; height: 35
                CheckBox {
                    id: _checBox
                    anchors.verticalCenter: parent.verticalCenter
                    width: 35; height: 35
                    tristate: true

                    Component.onCompleted: {
                        if(_dialog.librariesList.indexOf("-" + modelData) > -1) {
                            _checBox.checkState = Qt.Checked
                        }
                        if(_dialog.librariesList.indexOf("--no-" + modelData) > -1) {
                            _checBox.checkState = Qt.PartiallyChecked
                        }
                    }

                    onCheckStateChanged: {
                        if(checkState === 0) { // delete xml
                            var pos = _dialog.librariesList.indexOf("-"+modelData);
                            if(pos > -1)
                                _dialog.librariesList.splice(pos, 1)
                        }
                        if(checkState === 1) { // --no-xml
                            _dialog.librariesList.push("--no-"+modelData)
                        }
                        if(checkState === 2) { // -xml
                            pos = _dialog.librariesList.indexOf("--no-"+modelData);
                            if(pos > -1)
                                _dialog.librariesList[pos] = "-"+modelData
                        }
                    }
                }
                Label {
                    x: 45; y: 0
                    width: 100; height: 35
                    verticalAlignment: Text.AlignVCenter
                    text: modelData
                }
            }
        }

        CustomButton {
            x: parent.width-240; y: parent.height-35
            width: 100
            text: qsTr("Применить")
            onClicked: {
                _dialog.apply(_dialog.librariesList.join(" "))
            }
        }
        CustomButton {
            x: parent.width-width-20; y: parent.height-35
            width: 100
            text: qsTr("Отмена")
            onClicked: {
                _dialog.close()
            }
        }
    }

}
