import QtQuick 2.12
import QtQuick.Controls 2.5

import Components.Controls 1.0
import Components.Elements 1.0

BasicPage {

    title: "Build"

    contentItem: [
        LabelFieldRow {
            label: qsTr("Исполняемый файл")
            filterFile: qsTr("Испольняемый файл (*.exe)")
            mode: LabelFieldRow.Mode.File
            onTextChanged: {

            }
        },
        LabelFieldRow {
            label: qsTr("Папка развертывания")
            onTextChanged: {

            }
        }

    ]
}
