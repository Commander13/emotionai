import QtQuick 2.7
import QtQuick.Window 2.2
import QtMultimedia 5.0
import QtQuick.Controls 1.4

Window{
    id: sessionPageWindow

    minimumHeight: 600
    minimumWidth: 800

    property string currentPatient


    Item{
        id: rootItem

        property int counter:0

        anchors{
            fill: parent
        }

        Text{
            id: patientText
            anchors{
                left: rootItem.left
                top: rootItem.top
                margins:20
            }

            z:5

            text: "Patient: %1".arg(sessionPageWindow.currentPatient)
            color:"white"

            font.pixelSize: 20

        }

        Image{
            id: backgroundImage
            anchors.fill: rootItem

            source: "/Images/centralscreenbg.png"
        }

        Text{
            id: progressBarText
            anchors{
                centerIn: progressBar
            }

            z:5

            text: "%1%".arg(progressBar.value)
            font.pointSize: 24
        }

        ProgressBar{
            id: progressBar
            anchors{
                top: rootItem.top
                topMargin:20
                horizontalCenter: rootItem.horizontalCenter
            }

            width: cameraItem.width
            height: 60

            minimumValue: 0
            maximumValue: 100
            value: 50


        }

        Item{
            id: cameraItem
            width: rootItem.width *1/2
            height: rootItem.height * 2/3
            anchors{
                horizontalCenter: rootItem.horizontalCenter
                top: progressBar.bottom
                topMargin:20

            }

            Camera{
                id: camera

            }

            VideoOutput{
                source: camera
                focus: visible
                anchors.fill: parent

            }
        }

        Timer{
            id: timer
            interval: 500
            repeat: true
            onTriggered:{
                    rootItem.counter = rootItem.counter + 1
                if(rootItem.counter < 31){
                    interfaceHandler.testSequence(listView.currentPatient, rootItem.counter);
                }
            }
        }

        Connections{
            id: connectionToInterfaceHandler
            target: interfaceHandler

            onUpdateScore:{
                progressBar.value = score
                console.log("Progress bar value updated to: " + score)
            }
        }

        Row{
            id: startStopButtonRow
            anchors{
                top: cameraItem.bottom
                topMargin:20
                horizontalCenter: cameraItem.horizontalCenter
                bottom: rootItem.bottom
                bottomMargin:20
            }

            width: cameraItem.width * 2/3

            spacing:10

            HuronButton{
                id: startButton

                width:startStopButtonRow.width/2 - 10
                height:60

                sourceNormal:"/Images/normalbutton.png"
                sourceActive:"/Images/activebutton.png"
                sourceHover: "/Images/hoverbutton.png"


                state: if(pressedState == 1)
                       {
                           return "ACTIVE"
                       }
                       else if(hoverState == 1)
                       {
                           return "HOVER"
                       }
                       else{
                            return "NORMAL"
                       }

                Text{
                    anchors.centerIn: startButton
                    text:"Start"
                    font.family: "Helvetica"
                    font.pixelSize: 12
                    color:"whitesmoke"
                }

                onButtonClicked: {
                    timer.start()
                }

            }

            HuronButton{
                id: stopButton

                width:startStopButtonRow.width/2 - 10
                height:60

                sourceNormal:"/Images/normalbutton.png"
                sourceActive:"/Images/activebutton.png"
                sourceHover: "/Images/hoverbutton.png"


                state: if(pressedState == 1)
                       {
                           return "ACTIVE"
                       }
                       else if(hoverState == 1)
                       {
                           return "HOVER"
                       }
                       else{
                            return "NORMAL"
                       }

                Text{
                    anchors.centerIn: stopButton
                    text:"Stop"
                    font.family: "Helvetica"
                    font.pixelSize: 12
                    color:"whitesmoke"
                }

                onButtonClicked: {
                      timer.stop()
                }

            }

        }
    }


}
