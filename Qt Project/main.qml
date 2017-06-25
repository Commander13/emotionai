import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Universal 2.1
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Patient Emotion Tracker")

    Universal.theme: Universal.Light


    Item{
        id: rootItem
        anchors.fill: parent

        Image{
            id: backgroundImage
            anchors.fill: rootItem

            source: "/Images/centralscreenbg.png"
        }

        Image{
            id: listViewBackground
            anchors.fill: listView
            source:"/Images/panellistbg.png"
        }

        Text{
            id: listViewTitle
            text:"Patients"
            color:"whitesmoke"
            font.pixelSize: 18
            anchors{
                bottom: listView.top
                left: listView.left
            }
        }

//        Text{
//            id: testText
//            text: listView.currentPatient
//            anchors{
//                left: rootItem.left
//                verticalCenter: rootItem.verticalCenter
//            }
//        }

        ListView{
            id: listView
            anchors{
                centerIn: rootItem
            }

            width: rootItem.width * 1/3
            height: rootItem.height * 3/4

            highlight: Rectangle{
                        color: "lightsteelblue"
                        radius: 5
                        anchors{
                            margins:50
                        }
            }

            highlightFollowsCurrentItem: true

            focus: true

            property string currentPatient


            currentIndex: 0

            delegate: Item{
                id: rootDelegateItem

                width: listView.width
                height: listView.height * 1/8

                Component.onCompleted:{
                    if(index == 0){
                        listView.currentPatient = name
                    }
                }

                Text{
                    id: delegateText
                    anchors{
                        centerIn: parent
                    }

                    text: name
                    color:"black"
                }

                MouseArea{
                    id: delegateMouseArea
                    anchors.fill: rootDelegateItem
                    onClicked:{
                        listView.currentIndex = index
                        listView.currentPatient = name
                    }
                }

            }

            model: patientModel

        }


        Row{
            id: buttonRow

            z:5

            width: listView.width
            anchors{
                top: listView.bottom
                topMargin:10
                horizontalCenter: listView.horizontalCenter
            }

            spacing: 20

            HuronButton{
                id: sessionButton

                width:buttonRow.width/2 - 10
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
                    anchors.centerIn: sessionButton
                    text:"Session"
                    font.family: "Helvetica"
                    font.pixelSize: 12
                    color:"whitesmoke"
                }

                onButtonClicked: {
                    sessionPage.currentPatient = listView.currentPatient
                    sessionPage.showMaximized()
                    sessionPage.visible = true
                }

            }

            HuronButton{
                id: trendButton

                width:buttonRow.width/2 - 10
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
                    anchors.centerIn: trendButton
                    text:"View Trend"
                    font.family: "Helvetica"
                    font.pixelSize: 12
                    color:"whitesmoke"
                }

                onButtonClicked: {
                    trendPage.currentPatient = listView.currentPatient
                    trendPage.visible = true
                    trendPage.showMaximized()
                }

            }


        }


        SessionPage{
            id: sessionPage
            visible: false

        }

        TrendPage{
            id: trendPage
            visible: false
        }

        ListModel{
            id: patientModel
            ListElement{
                name: "John Smith"
            }
            ListElement{
                name:"Ellis Gray"
            }
            ListElement{
                name:"Thomas Dunkin"
            }

            ListElement{
                name:"Jennifer Lee"
            }

            ListElement{
                name: "Mohammed Abdalla"
            }

            ListElement{
                name:"Alison Bell"
            }

            ListElement{
                name: "Luke Skywalker"
            }

            ListElement{
                name:"Ryley Thompson"
            }

        }
    }





}
