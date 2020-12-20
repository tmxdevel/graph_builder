import QtQuick 2.0

Rectangle {

    readonly property string value: mulA.text
    property alias labelText: label.text

    width: parent.width / 3
    height: parent.height

    clip: true

    color: "transparent"

    Text {
        id: label

        height: parent.height

        verticalAlignment: Text.AlignVCenter

        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.top: parent.top

        color: "#DADAD9"

        text: "A:"

        font.pixelSize: 24
    }

    Rectangle {
        height: parent.height - 8

        anchors.left: label.right
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 4

        color: "#262728"

        TextEdit {
            id: mulA

            anchors.fill: parent

            verticalAlignment: TextEdit.AlignVCenter

            color: "#DADAD9"

            font.pixelSize: 24

        }

    }


}
