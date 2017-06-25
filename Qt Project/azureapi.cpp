#include "azureapi.h"
#include "QUrl"
#include <QNetworkReply>
#include "QUrl"
#include "QUrlQuery"
#include "QEventLoop"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "QVariant"
#include <QDebug>

int currentScore = 50;

//AzureAPI::AzureAPI()
//{

//}

AzureAPI::Emotions AzureAPI::fetchEmotionForImageURL(QByteArray imageURL)
{

    QNetworkAccessManager mgr;

    QUrlQuery postData;
    postData.addQueryItem("Content-Type", "application/json");
    postData.addQueryItem("Ocp-Apim-Subscription-Key", "bbebd00a43654a7b8428c2f3abe481b0");
    // Build your JSON string as usual
    QByteArray jsonString = "{\"url\":\"";
    jsonString.append(imageURL);
    jsonString.append("\"}");
    // For your "Content-Length" header
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    // Time for building your request
    QUrl serviceURL("https://westus.api.cognitive.microsoft.com/emotion/v1.0/recognize");
    QNetworkRequest request(serviceURL);

    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
    request.setRawHeader("Ocp-Apim-Subscription-Key", "bbebd00a43654a7b8428c2f3abe481b0");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    // Use QNetworkReply * QNetworkAccessManager::post(const QNetworkRequest & request, const QByteArray & data); to send your request. Qt will rearrange everything correctly.
    QNetworkReply * reply = mgr.post(request, jsonString);

    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QByteArray response_data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response_data);
    reply->deleteLater();
    QJsonArray jsonArray = json.array();
    QStringList emotions = jsonArray.first().toObject().value("scores").toObject().keys();
    QJsonObject dic = jsonArray.first().toObject().value("scores").toObject();

    double max = 0;
    int hotIndex = 0;
    for (int i=0; i<dic.count(); i++) {
        QJsonValue thatHotVal = dic[emotions[i]];  //find(emotions.at(i));
        double currentVal = thatHotVal.toDouble();
        if (currentVal > max) {
            max = currentVal;
            hotIndex = i;
        }
    }
    Emotions returnEmote = Emotions(hotIndex);
    return returnEmote;
}

double AzureAPI::fetchSentimentForText(QByteArray text)
{

    QNetworkAccessManager mgr;
    // Build your JSON string as usual
    QByteArray jsonString = "{\"documents\": [{\"language\": \"en\",\"id\": \"420\",\"text\": \"";
    jsonString.append(text);
    jsonString.append("\"}]}""}");

    // For your "Content-Length" header
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    // Time for building your request
    QUrl serviceURL("https://westus.api.cognitive.microsoft.com/text/analytics/v2.0/sentiment");
    QNetworkRequest request(serviceURL);

    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
    request.setRawHeader("Ocp-Apim-Subscription-Key", "28c6aafdec7c44ea9870fe684381b289");
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    // Use QNetworkReply * QNetworkAccessManager::post(const QNetworkRequest & request, const QByteArray & data); to send your request. Qt will rearrange everything correctly.
    QNetworkReply * reply = mgr.post(request, jsonString);

    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QByteArray response_data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response_data);
    reply->deleteLater();
    QJsonObject topLevelObject = json.object();
    double score = topLevelObject.value("documents").toArray().first().toObject().value("score").toDouble();

    return score;
}

QString AzureAPI::fetchTextForSoundFile() {

    //Get me that dirty access token
    QNetworkAccessManager mgr;
    // Build your JSON string as usual
    QByteArray jsonString = "{\"documents\": [{\"language\": \"en\",\"id\": \"420\",\"text\": \"That meme is absolutely barbaric my good friend poop head.\"}]}""}";

    // For your "Content-Length" header
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    // Time for building your request
    QUrl serviceURL("https://api.cognitive.microsoft.com/sts/v1.0/issueToken");
    QNetworkRequest request(serviceURL);

    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
    request.setRawHeader("Ocp-Apim-Subscription-Key", "d5f1ca79899b414195d1824313f43e47");
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Content-Length", 0);

    // Use QNetworkReply * QNetworkAccessManager::post(const QNetworkRequest & request, const QByteArray & data); to send your request. Qt will rearrange everything correctly.
    QNetworkReply * reply = mgr.post(request, "");

    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QByteArray thatDirtyToken= reply->readAll();
    reply->deleteLater();

    //Use that dirty token to slap some audio out
    QNetworkAccessManager newMgr;
    // Time for building your request
    QUrl newURL("https://speech.platform.bing.com/speech/recognition/interactive/cognitiveservices/v1?language=en&locale=US&format=your_format&requestid=your_guid");
    QNetworkRequest newRequest(newURL);

    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
    request.setRawHeader("Authorization", thatDirtyToken);
    request.setRawHeader("Content-Type", "audio/wav; codec=\"audio/pcm\"; samplerate=16000");
    request.setRawHeader("Content-Length", postDataSize);
    QByteArray test = "audio/wav; codec=\"audio/pcm\"; samplerate=16000";

    // Use QNetworkReply * QNetworkAccessManager::post(const QNetworkRequest & request, const QByteArray & data); to send your request. Qt will rearrange everything correctly.
    QNetworkReply *newReply = newMgr.post(newRequest, jsonString);

    QObject::connect(&newMgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

   QByteArray response_data = newReply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response_data);
    reply->deleteLater();
    QJsonObject topLevelObject = json.object();
    //double score = topLevelObject.value("documents").toArray().first().toObject().value("score").toDouble();

    return "I enjoy the fresh scent of asbestos in the morning.";
}

int AzureAPI::getScoreForUser(QString userID, QByteArray imageURL, QByteArray text) {

    qDebug() << "input: " << userID << imageURL
             << text;
    AzureAPI *api = new AzureAPI();
    AzureAPI::Emotions emotion = api->fetchEmotionForImageURL(imageURL);
    int emotionIndex = api->emotionMap[emotion];
    double sentiment = api->fetchSentimentForText(text);
    if (emotion == api->happiness && sentiment >= 0.6) {
        currentScore += 3;
    } else if (emotion == api->happiness && sentiment < 0.4) {
        currentScore -= 1;
    } else if (emotion == api->happiness) {
        currentScore += 2;
    } else if (emotion == api->sadness && sentiment < 0.4) {
        currentScore -= 3;
    } else if (emotion == api->sadness && sentiment >=0.6) {
        currentScore -= 1;
    } else if (emotion == api->sadness) {
        currentScore -= 2;
    } else if (emotion == api->neutral && (sentiment >= 0.4 && sentiment <= 0.6)) {
        currentScore += 0;
    } else if (emotion == api->neutral) {
        currentScore -= 1;
    } else if (sentiment >= 0.6) {
        currentScore -= 1;
    } else {
        currentScore -= 2;
    }
    if (currentScore > 100) currentScore = 0; else if (currentScore < 0) currentScore = 0;
    if (api->saveScoreForUser(userID, currentScore, emotionIndex, sentiment)) {
        qDebug() << "Error saving data point!";
    }
    return currentScore;
}

//Returns false on succcess
bool AzureAPI::saveScoreForUser(QString userID, int score, int emotionIndex, double sentiment) {
    QNetworkAccessManager mgr;

    QUrlQuery postData;
    postData.addQueryItem("Content-Type", "application/json");
    postData.addQueryItem("Ocp-Apim-Subscription-Key", "bbebd00a43654a7b8428c2f3abe481b0");
    // Build your JSON string as usual

    QByteArray jsonString = "{\"name\": \"";
    jsonString.append(userID);
    //jsonString.append("shittyMcShitface@shit.shit");
    jsonString.append("\",\"score\": ");
    jsonString.append(QString::number(score));
    jsonString.append(",\"faceSentiment\":");
    jsonString.append(QString::number(emotionIndex));
    jsonString.append(",\"toneSentiment\": ");
    jsonString.append(QString::number(sentiment));
    jsonString.append("}");
    qDebug() << jsonString;
    // For your "Content-Length" header
    QByteArray postDataSize = QByteArray::number(jsonString.size());

    // Time for building your request
    QUrl serviceURL("https://calm-beach-82148.herokuapp.com/users/addSession");
    QNetworkRequest request(serviceURL);
    request.setRawHeader("Content-Type", "application/json");
    // Use QNetworkReply * QNetworkAccessManager::post(const QNetworkRequest & request, const QByteArray & data); to send your request. Qt will rearrange everything correctly.
    QNetworkReply * reply = mgr.post(request, jsonString);

    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QByteArray response_data = reply->readAll();
    qDebug() << response_data;
    if (response_data.length() > 0) {
        return false;
    } else {
        return true;
    }
}
