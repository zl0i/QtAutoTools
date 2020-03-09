import QtQuick 2.12
import QtQuick.Controls 2.5



BasicPage {
    id: _scriptPage
    title: qsTr("Скрипты")
    visibleButton: false


    contentItem: ListView {
        width: _scriptPage.width-40; height: _scriptPage.height
        model: _guiAdapter.scripts.getNameScripts()
        delegate: Item {
            width: parent.width
            height: 40
            Rectangle {
                width: parent.width; height: 1
                color: "#C4C4C4"
            }
            Rectangle {
                y: 40
                width: parent.width; height: 1
                color: "#C4C4C4"
            }
            Label {
                x: 20
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                text: modelData
            }
            Rectangle {
                x: parent.width-width-20; y: 7.5
                width: 25; height: 25
                color: "green"
                MouseArea {
                    width: parent.width; height: parent.height
                    onClicked: _scriptPage.run(modelData)
                }
            }
        }
    }
}
