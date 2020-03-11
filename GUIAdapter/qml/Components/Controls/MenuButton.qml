import QtQuick 2.0

MouseArea {
    id: _menuButton
    width: 18
    height: 15
    Column {
        spacing: 5
        Repeater {
            model: 3
            Rectangle {
                width: 18; height: 1
                color: _menuButton.pressed ? "#39A0FF" : "#C4C4C4"
            }
        }
    }
}
