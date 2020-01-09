import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: _window
    visible: true
    width: 720
    height: 480
    minimumWidth: 720
    minimumHeight: 360
    title: qsTr("QtAutoTools")    



    font {
        pixelSize: 14
        family: "Roboto"
    }


    readonly property var toolsModel: [
        {
            "title": "windeployqt",            
            "component": "qml/WinDeployQtPage.qml"
        },
        {
            "title": "installer",           
            "component": "/qml/InstallerPage.qml"
        },
        {
            "title": "qmldir",            
            "component": "/qml/QmldirPage.qml"
        },        
        {
            "title": "lupdate",           
            "component": "/qml/LUpdatePage.qml"
        },
        {
            "title": qsTr("Настройки"),
            "visible": true,
            "component": "/qml/Settings.qml"
        }
    ]


    Rectangle {
        width: 200; height: parent.height
        color: "#4B4B4B"

        ListView {
            id: _list
            width: 200; height: parent.height
            interactive: false
            model: toolsModel
            delegate: Rectangle {
                width: 200; height: 45
                color: "transparent" //ListView.isCurrentItem ? "#87CEEB" : "#FFFFFF"
                Label {
                    x: 20
                    width: parent.width-20; height: parent.height
                    verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 18
                    //font.weight: Font.Bold
                    color: "#FFFFFF"
                    text: modelData.title
                }
                Rectangle {                   
                    width: 3; height: 45
                    color: "#39A0FF"
                    visible: parent.ListView.isCurrentItem
                    layer.enabled: true
                    layer.effect: DropShadow {
                        radius: 8
                        samples: 16
                        horizontalOffset: 3
                        color: "#39A0FF"
                    }
                }
                Rectangle {
                    width: parent.width; height: parent.height
                    color: "#808080"
                    opacity: 0.3
                    layer.enabled: true
                    visible: _mouseArea.hovered
                    Rectangle {
                        width: parent.width; height: 1
                        color: "#696969"
                    }
                    Rectangle {
                        y:parent.height-1
                        width: parent.width; height: 1
                        color: "#696969"
                    }
                }

                MouseArea {
                    id: _mouseArea
                    width: parent.width; height: parent.height
                    hoverEnabled: true
                    property bool hovered: false
                    onClicked: {
                        _list.currentIndex = index
                        _loader.source = modelData.component

                    }
                    onEntered: hovered = true
                    onExited: hovered = false
                }
            }
        }
    }

    Loader {
        id: _loader
        x: 200; y:0
        width: parent.width-x; height: parent.height
        source: "qml/WinDeployQtPage.qml"
        asynchronous: true
    }
}
