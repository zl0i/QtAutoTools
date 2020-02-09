import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import Components.Controls 1.0
import Components.Elements 1.0

Dialog {
    id: _dialog
    x: parent.width/2 - width/2; y: parent.height/2 - height/2
    width: 463; height: _swipeView.currentItem.contentHeight + 60
    padding: 0
    modal: true; dim: true
    closePolicy: Popup.NoAutoClose

    Behavior on height {
        NumberAnimation { duration: 200 }
    }

    Overlay.modal: Rectangle {
        color: "#DF000000"
    }

    background: Rectangle {
        width: parent.width; height: parent.height; radius: 10
        color: "#FFFFFF"
    }

    contentItem: Item {
        width: parent.width; height: parent.height
        Label {
            x: 20; y: 20
            font.pixelSize: 18
            text: qsTr("Первоначальная настройка")
        }
        SwipeView {
            id: _swipeView
            x: 20; y: 60
            width: parent.width-x-20; height:  _dialog.height-y-20
            clip: true
            //interactive: false
            currentIndex: 0

            Item {
                width: _swipeView.width; height: _swipeView.height
                property int contentHeight: 120

                LabelFieldDialog {
                    id: _qtPathField
                    label: qsTr("Папка Qt")
                }
                CustomButton {
                    x: parent.width-width; y: parent.height-height
                    width: 70; height: 40
                    enabled: _qtPathField.text.length > 0
                    text: qsTr("Далее")
                    onClicked: {
                        _detector.detect(_qtPathField.text)
                        _swipeView.incrementCurrentIndex()
                    }
                }
            }
            Item {
                width: _swipeView.width; height: _swipeView.height
                property int contentHeight: 290
                Column {
                    width: parent.width
                    spacing: 15
                    LabelComboBox {
                        label: qsTr("Версия Qt")
                        model: _detector.qtVersion
                        onActivated: _detector.detectProfile(currentText)
                    }
                    LabelComboBox {
                        label: qsTr("Профиль Qt")
                        model: _detector.qtProfile
                        onCurrentTextChanged: _detector.setProfile(currentText)
                    }
                    LabelComboBox {
                        label: qsTr("Комилятор")
                        model: _detector.compilerList
                        onCurrentTextChanged: _detector.setCompiler(currentText)
                    }
                    LabelComboBox {
                        label: qsTr("Qt Installer Framework")
                        model: _detector.installerVerison
                        onCurrentTextChanged: _detector.setInstallerFramework(currentText)
                    }
                }
                CustomButton {
                    x: parent.width-width; y: parent.height-height
                    width: 70; height: 40
                    text: qsTr("Готово")
                    onClicked: _dialog.close()
                }
            }
        }
    }
}
