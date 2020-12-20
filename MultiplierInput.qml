import QtQuick 2.0
import QtQuick.Controls 2.4

Rectangle {
    id: root

    readonly property string ma: mulA.value
    readonly property string mb: mulB.value
    readonly property string mc: mulC.value

    width: parent.width
    height: 50

    color: "#191919"

    Row {
        anchors.fill: parent
        spacing: 0

        LabeledInput {
            id: mulA
            labelText: "A:"
        }
        LabeledInput {
            id: mulB
            labelText: "B:"
        }
        LabeledInput {
            id: mulC
            labelText: "C:"
        }


    }

}
