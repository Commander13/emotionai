import QtQuick 2.3
import QtGraphicalEffects 1.0

Item {
    id: buttonRect
    width: 200
    height: 80
    //color:"transparent"
    property string stateFlag;
    signal buttonClicked

    property alias sourceNormal: backgroundImageNormal.source
    property alias sourceActive: backgroundImageActive.source
    property alias sourceHover: backgroundImageHover.source
    property alias currentState : buttonRect.state
    property alias pressedState:  mouseArea.pressed
    property alias hoverState: mouseArea.containsMouse

    enabled: true

    //state: stateFlag == "normal" ? "NORMAL":"ACTIVE"

    states:[
        State{
            name: "NORMAL"
            PropertyChanges{
                target:backgroundImageNormal
                visible: true
                restoreEntryValues: true
            }
        },
        State{
            name:"ACTIVE"
            PropertyChanges{
                target: backgroundImageActive
                visible:true
                restoreEntryValues: true
            }
        },
        State{
            name:"HOVER"
            PropertyChanges{
                target: backgroundImageHover
                visible: true
                restoreEntryValues: true
            }
        },
        State{
            name:"DISABLED"
            PropertyChanges{
                target:disabledColorOverlay
                visible: true
                color: Qt.rgba(0.25,0.25,0.25,0.4)
                restoreEntryValues: true
            }
            PropertyChanges{
                target: backgroundImageNormal
                visible: true
                restoreEntryValues: true
            }
            PropertyChanges{
                target: buttonRect
                enabled: false
                restoreEntryValues: true
            }
        }

    ]
    Image{
        id: backgroundImageActive
        anchors.fill: parent
        visible:false

    }
    Image{
        id: backgroundImageNormal
        anchors.fill: parent
        visible: false

    }
    Image{
        id: backgroundImageHover
        anchors.fill:parent
        visible:false
        source:""
    }

    ColorOverlay{
        id: disabledColorOverlay
        anchors.fill: parent
        source: parent
        visible: false
        z:4
    }

    MouseArea{
        id: mouseArea
        anchors.fill: buttonRect
        hoverEnabled: true
        enabled: true
        focus: true
        z:1
        onClicked:{
            console.log("clicked")
            buttonClicked()
        }
    }


}
