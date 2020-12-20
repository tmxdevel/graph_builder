import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import "."

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Графопостроитель 2000 ультра")
    color: "#313332"

    Column {
        anchors.fill: parent
        spacing: 0

        FuncCombobox {id: func}

        Divider {}

        MultiplierInput {id: mulInput}

        Divider {}

    }

}
