import QtQuick 2.0

Rectangle {
    id: root

    property color mainColor: "#191919"
    property color dividerColor: "#404244"

    width: parent.width
    height: 3

    color: mainColor

    Rectangle {
        width: parent.width*0.75
        height: parent.height
        anchors.leftMargin: parent.width*0.125;
        anchors.left: parent.left
        color: dividerColor
    }

}
