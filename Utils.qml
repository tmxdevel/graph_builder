pragma Singleton

import QtQuick 2.12

Item {

    readonly property bool isDebug: Qt.application.arguments[1] === "--debug"

    function logD(message) {
        if(isDebug) console.log(message)
    }

}
