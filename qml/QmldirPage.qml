import QtQuick 2.12
import QtQuick.Controls 2.5

import Components 1.0
import AutoTools 1.0

Item {

    QmlDir {
        id: _qmldir
        onFinished: {
            _busiDialog.close()
        }
        onError: {
            console.log(str)
            _busiDialog.close()
        }
    }

    BusiDialog {
        id: _busiDialog
    }

    Label {
        x: 20; y: 20
        font.pixelSize: 18
        font.weight: Font.Bold
        text: "QmlDir"
    }

    Flickable {
        x: 20; y: 50
        width: parent.width-40; height: parent.height-y
        contentHeight: _content.height+20
        clip: true
        Column {
            id: _content
            width: parent.width
            spacing: 20
            LabelFieldRow {
                label: qsTr("Папка с компонентами")
                onTextChanged:  {
                    _qmldir.setPath(text)
                }
            }
            ListView {
                width: parent.width
                height: count * 40 + (count-1) * spacing
                spacing: 15
                model: 2
                delegate: Row {
                    width: parent.width; height: 40
                    spacing: 15
                    ComboBox {
                        width: 120
                        model: ["", "Singleton", "Internal"]
                    }
                    TextField {
                        width: 120; height: 40
                        text: "CustomCursor"
                    }
                    TextField {
                        width: 40; height: 40
                        text: "1.0"
                    }
                    TextField {
                        width: 150; height: 40
                        text: "CustomCursor.qml"
                    }
                }
            }
            LabelCheckBox {
                label: qsTr("Создать запись о типах qmldir")
            }
            LabelCheckBox {
                label: qsTr("Поддержка Qt Quick Designer")
            }

            Button {
                text: qsTr("Создать")
                onClicked: {                   
                    _qmldir.createModule()
                }
            }
        }
    }
}
