import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Dialogs 1.0
import Components.Controls 1.0

BasicPage {
    id: _scriptPage
    title: qsTr("Скрипты")
    visibleRunButton: false
    visibleScriptButton: false

    property bool addToScriptMode: false
    property var addScript

    function newScript(script) {
        script.environment = _guiAdapter.settings
        script.label = script.tool
        _scriptDialog.script = { name: "ScriptName", version: "1.0", tasks: [script] }
        _scriptDialog.open()
    }

    function addToScript(script) {
        script.environment = _guiAdapter.settings
        script.label = script.tool
        addScript = script
        addScript.label = addScript.tool
        addToScriptMode = true
    }

    function resetAddToScriptMode() {
        addScript = {}
        addToScriptMode = false
    }

    contentItem: Column {
        spacing: 10
        ListView {
            id: _listScript
            width: _scriptPage.width-40; height: count*40
            model: _guiAdapter.scripts.getNameScripts()
            interactive: count*40 > _scriptPage.height-100
            delegate: Rectangle {
                width: parent.width; height: 40

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
                MouseArea {
                    width: parent.width; height: parent.height
                    onClicked: {
                        var script = _guiAdapter.scripts.getScriptByName(modelData)
                        if(addToScriptMode) {
                            script.tasks.push(addScript)
                            resetAddToScriptMode()
                        }
                        _scriptDialog.script = script
                        _scriptDialog.open()
                    }
                }
                MouseArea {
                    x: parent.width-width-60; y: 15
                    width: 17; height: 17
                    onClicked: {
                        _guiAdapter.scripts.removeScript(modelData)
                        _listScript.model =  _guiAdapter.scripts.getNameScripts()
                    }
                    Image {
                        width: 13; height: 13
                        source: "qrc:/icon/delete-black.svg"
                        layer.enabled: parent.pressed
                        layer.effect: ColorOverlay {
                            color: "#39A0FF"
                        }

                    }
                }

                Image {
                    x: parent.width-width-30; y: 10.5
                    width: 14; height: 19
                    source: "qrc:/icon/arrow-right.svg"
                    layer.enabled: _mouseDelegate.pressed
                    layer.effect: ColorOverlay {
                        color: "#39A0FF"
                    }
                    MouseArea {
                        id: _mouseDelegate
                        width: parent.width; height: parent.height
                        onClicked: _scriptPage.run(modelData)
                    }
                }

            }
        }
        CustomButton {
            text: qsTr("Добавить")
            onClicked: {
                _scriptDialog.script = { name: "ScriptName", version: "1.0", tasks: [] }
                _scriptDialog.open()
            }
        }

    }
    ScriptDialog {
        id: _scriptDialog
        onSaveScript: {
            _guiAdapter.scripts.saveScript(script, script.name)
            _listScript.model =  _guiAdapter.scripts.getNameScripts()
        }

    }
}
