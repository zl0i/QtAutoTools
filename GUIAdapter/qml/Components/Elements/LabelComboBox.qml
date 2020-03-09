import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: _root
    width: parent.width;  height: 40

    property string label: ""
    property real widthLabel: 150
    property var model

    property alias currentIndex: _comboBox.currentIndex
    property alias currentText: _comboBox.currentText

    signal activated(var index)


   Label {
        width: widthLabel; height: 40
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        text: _root.label
    }
    ComboBox {
        id: _comboBox
        x: parent.width-width
        height: 40
        model: _root.model
        onActivated: {
            _root.activated(currentIndex)
        }

    }
}
