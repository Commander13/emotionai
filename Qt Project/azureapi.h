#ifndef AZUREAPI_H
#define AZUREAPI_H

//#include "azureapi_global.h"
#include <QUrl>
#include <array>

using namespace std;

class AzureAPI
{


public:
    typedef enum {
        anger ,
        contempt ,
        disgust ,
        fear,
        happiness ,
        neutral ,
        sadness ,
        surprise
    } Emotions;

    std::array<int,8> emotionMap;

    AzureAPI() : emotionMap ({ 2,3,4,1,7,5,1,6 }) {}

    //int emotionMap[8] = {2, 3, 4, 1, 7, 5, 1, 6};


    //use
    int getScoreForUser(QString userID, QByteArray imageURL, QByteArray text);

    //AzureAPI();
    //Don't use
    Emotions fetchEmotionForImageURL(QByteArray serviceURL);
    double fetchSentimentForText(QByteArray text);
    QString fetchTextForSoundFile();
    bool saveScoreForUser(QString userID, int score, int emotionIndex, double sentiment);



};

#endif // AZUREAPI_H
