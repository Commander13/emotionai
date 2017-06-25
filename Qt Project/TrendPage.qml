import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtCharts 2.2

Window{
    id: sessionPageWindow

    minimumHeight: 600
    minimumWidth: 800

    property string currentPatient

    Item{
        id: rootItem

        anchors{
            fill: parent
        }


        ChartView{
            title: "Trend for Patient: %1".arg(currentPatient)
            anchors{
                fill: rootItem
                margins:20
            }
            antialiasing: true

            LineSeries{
                name:"PatientLineSeries"
                XYPoint { x: 0; y:95}
                XYPoint { x: 1; y:90}
                XYPoint { x: 2; y:85}
                XYPoint { x: 3; y:45}
                XYPoint { x: 4; y:95}
                XYPoint { x: 5; y:94}
                XYPoint { x: 6; y:90}
                XYPoint { x: 7; y:95}
                XYPoint { x: 8; y:98}
                XYPoint { x: 9; y:92}
                XYPoint { x: 10; y:89}
            }
        }

    }
}
