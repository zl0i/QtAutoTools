import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: _root
    width: parent.width;  height: 40

    property string label: ""
    property real widthLabel: 150
    property alias checked: _checkBox.checked
    property bool enabledCheckBox: true


   Label {
        width: widthLabel; height: 40
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WordWrap
        text: _root.label
    }
    CheckBox {
        id: _checkBox
        x: parent.width-width
        width: 40; height: 40
        enabled: enabledCheckBox
        onCheckedChanged: {
            _root.checkedChanged(checked)
        }
    }
}
