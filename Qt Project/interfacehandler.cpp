#include "interfacehandler.h"
#include <QDebug>
using namespace std;

InterfaceHandler *InterfaceHandler::m_pInstance = NULL;

InterfaceHandler::InterfaceHandler(QObject *parent) : QObject(parent)
{


    azureApi = new AzureAPI();

    constantStringUrl = QString("http://104.156.251.83/api/F4C9C28E-4383-4B5F-FFDF-1E9B4CE46800/v1/files/Hackathon/");

    sentimentHappy = QString("Happy");
    sentimentSad = QString("Sad");
    randomSentiment << QString("Happy");
    randomSentiment << QString("Sad");
    randomSentiment << QString("Neutral");

}


InterfaceHandler *InterfaceHandler::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new InterfaceHandler;
    }

    return m_pInstance;
}

void InterfaceHandler::testSlot()
{
    qDebug() << "Test slot!" ;
}


void InterfaceHandler::testHappy(QString patient, int id)
{


}

void InterfaceHandler::testSad(QString patient, int id)
{

}

void InterfaceHandler::testSequence(QString patient, int id)
{

    //create URl
    QString urlEmotion;
    QString appendString = QString::number(id) + ".jpg";
    urlEmotion = constantStringUrl;
    urlEmotion.append(appendString);

    //Text sentiment
    QByteArray sentiment;
    if(id < 15){
        sentiment = QByteArray("angry");
    }else if(id > 15 && id < 17)
    {
        sentiment = QByteArray("neutral");
    }else{
        sentiment = QByteArray("happy");
    }
   int score;
  //QUrl emotionURL = QUrl(urlEmotion);
   score = azureApi->getScoreForUser(patient, urlEmotion.toUtf8(), sentiment);

   emit updateScore(score);

}

void InterfaceHandler::testRandom(QString patient, int id)
{

}

