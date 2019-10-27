import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: _window
    visible: true
    width: 720
    height: 480
    title: qsTr("QtAutoTools")


    font {
        pixelSize: 14

    }


    readonly property var toolsModel: [
        {
            "title": "windeployqt",
            "info": "Подключает все библиотеки используемые в exe файле",
            "component": "qml/WinDeployQtPage.qml"
        },
        {
            "title": "installer",
            "info": "Создани уставнощика из деплоя",
            "component": "/qml/InstallerPage.qml"
        },
        {
            "title": "qmldir",
            "info": "Автоматическое создание и заполение qmldir",
            "component": "/qml/QmldirPage.qml"
        },
        {
            "title": "qmlplugindump",
            "info": "Создание файла описания м",
            "component": "/qml/QmlplugindumpPage.qml"
        },
        {
            "title": "lupdate",
            "info": "",
            "component": "/qml/LUpdatePage.qml"
        },
        {
            "title": "Настройки",
            "info": "",
            "component": "/qml/Settings.qml"
        }

    ]


    Rectangle {
        width: 200; height: parent.height
        color: "#A9A9A9"

        ListView {
            id: _list
            width: parent.width; height: parent.height
            interactive: false
            model: toolsModel
            delegate: Rectangle {
                width: parent.width; height: 45
                color: "transparent" //ListView.isCurrentItem ? "#87CEEB" : "#FFFFFF"
                Label {
                    x: 20
                    width: parent.width-20; height: parent.height
                    verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 14
                    font.weight: Font.Bold
                    text: modelData.title
                }
                Rectangle {
                    x:0; y:7
                    width: 4; height: parent.height-14
                    color: "#1E90FF"
                    visible: parent.ListView.isCurrentItem
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
    }
}
