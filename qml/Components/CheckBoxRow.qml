import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12


RowLayout {
    id: _root
    spacing: 10
    height: 40

    property string text: ""
    property real widthText: 150
    property alias checked: _checkBox.checked


    Label {
        width: widthText; height: parent.height
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        text: _root.text
    }
    CheckBox {
        id: _checkBox
        width: 40; height: parent.height
    }

}
