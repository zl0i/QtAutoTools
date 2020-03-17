import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Controls 1.0
import Components.Dialogs 1.0

Item {
    id: _page

    property string title
    property Item contentItem
    property bool visibleRunButton: true
    property string buttonText: qsTr("Запустить")
    property bool visibleScriptButton: true
    property alias interactive: _flickable.interactive

    property var task: ({})
    signal run(var task)
    signal saveScript(var add, var script)

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: _page.title
    }

    Flickable {
        id: _flickable
        x: 20; y: 60
        width: parent.width; height: parent.height-y
        contentHeight: _content.height + 100
        interactive: contentHeight > height
        clip: true
        Column {
            id: _content
            x:0; y: 10
            children: _page.contentItem
        }
        Row {
            anchors { top: _content.bottom; topMargin: 20}
            spacing: 10
            CustomButton {
                visible: visibleRunButton
                text: _page.buttonText
                onClicked: {
                    _page.run(task)
                }
            }
            CustomButton {
                width: 40; height: 40
                visible: visibleScriptButton
                Image {
                    anchors.centerIn: parent
                    width: 16; height: 20
                    source: "qrc:/icon/script-white.svg"
                }
                onClicked:  {
                    var point = mapToItem(Overlay.overlay, mouseX, mouseY)
                    if(point.y + _popup.height + 20 > Overlay.overlay.height) {
                        _popup.y = -_popup.height+20
                    } else {
                        _popup.y = 20
                    }
                    _popup.open()
                }
                ScriptPopup {
                    id: _popup
                    x: 20; y: -height/2
                    onAddScript: _page.saveScript(true, task)
                    onNewScript: _page.saveScript(false, task)
                }
            }
        }
    }
}
