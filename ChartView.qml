import QtQuick 2.0
import Sachi.Chart 1.0

Rectangle {
    id: root

    color: "transparent"

    property GraphDataModel chartData: ({})

    property alias from: chart.from
    property alias to: chart.to

    property alias aMul: chart.aMul
    property alias bMul: chart.bMul
    property alias cMul: chart.cMul

    property alias funcIndex: chart.funcIndex

    Chart {
        id: chart
        anchors.fill: parent
        clip: true
        model: chartData
    }

    function updateGrid() {
        chart.updateGrid()
        chart.update()
    }

}
