import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import "."

ComboBox {
    id: control

    property int currentFunction: currentIndex

    onCurrentFunctionChanged: Utils.logD("Current function index:" + currentFunction)

    width: parent.width

    font.pixelSize: 24

    background: Rectangle {
            width: parent.width
            height: parent.height
            color: "#191919"
        }
    contentItem: Text {
        leftPadding: 12
        topPadding: 8
        bottomPadding: 8
        text: control.displayText
        font: control.font
        color: "#DADAD9"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        textFormat: Text.RichText
    }
    delegate: ItemDelegate {
        width: control.width
        background: Rectangle {
            width: parent.width
            height: parent.height
            color: "#404244"
        }
        contentItem: Text {
            text: modelData
            color: "#DADAD9"
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            textFormat: Text.RichText
        }

        highlighted: control.highlightedIndex === index
    }
    model: [ "y=a+b·sin(x+c)", "y=a+b·ln(x+c)", "y=a+b·cos(x)·e<sup>–c·x</sup>" ]
}
