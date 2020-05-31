import QtQuick 2.12
import QtQuick.Controls 2.12

MouseArea {
    width: 25; height: 25
    property var imageWidth: width
    property var imageHeight: height
    property var image
    cursorShape: Qt.PointingHandCursor
    Image {
        x: parent.width/2 - width/2; y: parent.height/2 - height/2
        width: imageWidth; height: imageHeight
        source: parent.image
    }
}


