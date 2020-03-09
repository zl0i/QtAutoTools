import QtQuick 2.12
import QtGraphicalEffects 1.0

import Components.Elements 1.0

Flipable {
    id: _flipable
    x: parent.width/2-width/2;
    width: 70; height: 70

    property bool flipped: false
    property bool runningAnimation: false
    property bool isError: false

    signal clicked()

    front: LoadingAnimation {
        width: 70; height: 70
        externalColor: "#000000"
        internalColor: "#3A9AF2"
        lineWidth: 2
        internalRadius: externalRadius-5
        running: runningAnimation
    }
    back: Rectangle {
        width: 70; height: 70; radius: 35
        color: {
            if(isError) {
                return _mouseArea.pressed ? "#981F1F" : "#E31F1F"
            } else {
                return _mouseArea.pressed ? "#215A8E" : "#3A9AF2"
            }
        }
        layer.enabled: true
        layer.effect: DropShadow {
            samples: 16
            radius: 8
            verticalOffset: _mouseArea.pressed ? 2 : 4
            horizontalOffset: _mouseArea.pressed ? 2 : 4
            color: "#80000000"
        }
        Image {
            anchors { centerIn: parent; horizontalCenterOffset: isError ? 0 : 5 }
            width: isError ? 8 : 47
            height: isError ? 34: 27
            antialiasing: true
            smooth: true
            rotation: 270
            mirror: true
            source: isError ? "qrc:icon/error-white.svg" : "qrc:icon/success-white.svg"
        }
        MouseArea {
            id: _mouseArea
            anchors.fill: parent
            onClicked: {
                _flipable.clicked()
            }
        }
    }
    transform: Rotation {
        id: _rotation
        origin.x: _flipable.width
        origin.y: _flipable.height
        axis.x: 1; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
        angle: 0    // the default angle
    }
    states: State {
        name: "back"
        PropertyChanges { target: _rotation; angle: 180 }
        when: _flipable.flipped
    }

    transitions: Transition {
        NumberAnimation { target: _rotation; property: "angle"; duration: 500 }
    }

}
