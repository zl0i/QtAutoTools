import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQml 2.14

import Components.Dialogs 1.0
import Components.Controls 1.0
import Components.Elements 1.0

BasicPage {
    id: _scriptPage
    title: qsTr("Скрипты")
    visibleRunButton: false
    visibleScriptButton: false

    property bool addToScriptMode
    property var addScript

    Binding {
        target: _scriptPage
        property: "addToScriptMode"
        value: false
        when: !_scriptPage.ListView.isCurrentItem
        restoreMode: Binding.RestoreValue
    }

    function newScript(script) {
        script.environment = _guiAdapter.settings
        script.label = script.tool
        _scriptDialog.script = { name: "ScriptName", version: "1.1", tasks: [script] }
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
            width: _scriptPage.width-40; height: count*40+10
            model: _guiAdapter.scripts.getNameScripts()
            interactive: count*40 > _scriptPage.height-100
            delegate: ScriptDelegate {
                name: modelData
                x: 5
                width: parent.width-10
                height: _delegate.name === name ? 50 : 40
                onHoveredChanged: {
                    if(hovered) {
                        _delegate.name = modelData
                        _delegate.y = index*40
                        _delegate.visible = true
                    }
                }
            }
            ScriptDelegate {
                id: _delegate
                x: 5; width: parent.width-10; height: 50
                visible: false
                property int index: 0
                layer.enabled: true
                layer.effect: DropShadow {                    
                    radius: 8
                    samples: _delegate.mouseArea.pressed ? 30 : 16
                }
                onHoveredChanged: {
                    if(!hovered) {
                        visible = false
                        if(!openedConfirmDialog)
                            name = ""
                    }
                }
                onOpenScript: {
                    var script = _guiAdapter.scripts.getScriptByName(name)
                    if(addToScriptMode) {
                        script.tasks.push(addScript)
                        resetAddToScriptMode()
                    }
                    _scriptDialog.script = script
                    _scriptDialog.open()
                }
                onRemoveScript: {
                    _guiAdapter.scripts.removeScript(name)
                    _listScript.model =  _guiAdapter.scripts.getNameScripts()
                }
                onRunScript: _scriptPage.run(name)
                onReleased: _delegate.openScript(_delegate.name)
            }
        }
        CustomButton {
            text: qsTr("Добавить")
            onClicked: {
                _scriptDialog.script = { name: "ScriptName", version: "1.1", tasks: [] }
                _scriptDialog.open()
            }
        }
    }
    ScriptDialog {
        id: _scriptDialog
        onSaveScript: {
            if(renamed) {
                _guiAdapter.scripts.removeScript(oldName+".json")
            }
            _guiAdapter.scripts.saveScript(script, script.name)
            _listScript.model =  _guiAdapter.scripts.getNameScripts()
        }
    }
}
