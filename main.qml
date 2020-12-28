import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import Sachi.Chart 1.0
import "."

Window {
    id: root
    width: 1280
    height: 720
    visible: true
    title: qsTr("Графопостроитель 2000 ультраааааааааааааааААААААААААААААА!!!!!!!!!!!!!!!!!!")
    color: "#313332"

    GraphDataModel {
        id: chartData
    }

    Column {
        id: inputs
        anchors.fill: parent
        anchors.bottomMargin: root.height - 100
        spacing: 0

        FuncCombobox {id: func}

        Divider {}

        MultiplierInput {id: mulInput}

        Divider {}



    }

    Rectangle {
        id: tableWrap
        anchors.top: inputs.bottom
        anchors.left: parent.left
        anchors.bottom: boundsInput.top
        width: 150
        clip: true
        color: "white"
        ListView {
            id: table
            anchors.fill: parent
            model: chart.model
            clip: true

            ScrollBar.vertical: ScrollBar {}

            delegate: Rectangle {
                color: "white"
                border.width: 1
                border.color: "black"
                width: parent.width
                height: 50
                Text {
                    width:60
                    leftPadding: 10
                    id: valX
                    text: valueX.toFixed(2)
                }

                Text {
                    id: valY
                    anchors.left: valX.right
                    text: valueY.toFixed(2)
                }
            }

        }
    }

    Chart {
        id: chart
        anchors.top: inputs.bottom
        anchors.left: tableWrap.right
        anchors.right: parent.right
        anchors.bottom: boundsInput.top
        clip: true

        from: fromIn.text
        to: toIn.text

        aMul: mulInput.ma
        bMul: mulInput.mb
        cMul: mulInput.mc

        funcIndex: func.currentFunction
    }





    Row {
        id: boundsInput
        height: 50
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 100
        Text{
            text:"x ∈ ["
            color: "#DADAD9"
            font.pixelSize: 26
        }
        TextEdit {
            id: fromIn
            width: 60
            color: "#DADAD9"
            font.pixelSize: 26
            clip: true
        }
        Text {
            text: ";"
            color: "#DADAD9"
            font.pixelSize: 26
        }
        TextEdit {
            id: toIn
            width: 60
            color: "#DADAD9"
            font.pixelSize: 26
            clip: true
        }
        Text{
            text:"]"
            color: "#DADAD9"
            font.pixelSize: 26
        }
        Button {
            text: "Render"
            onClicked: {
                chart.updateGrid()
                chart.update()

                table.model = []
                table.model = chart.model
            }
        }
    }

}
