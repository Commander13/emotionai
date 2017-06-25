#ifndef INTERFACEHANDLER_H
#define INTERFACEHANDLER_H

#include <QObject>
#include "azureapi.h"


class InterfaceHandler : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceHandler(QObject *parent = nullptr);
    static InterfaceHandler *Instance();


signals:
   void updateScore(int score);

public slots:
    void testSlot();
    void testHappy(QString patient, int id);
    void testSad(QString patient, int id);
    void testSequence(QString patient, int id);
    void testRandom(QString patient, int id);

private:
    static InterfaceHandler *m_pInstance;
    QString constantStringUrl;
    QStringList happyUrlList;
    QStringList sadUrlList;
    QStringList randomUrlList;

    QString sentimentHappy;
    QString sentimentSad;
    QStringList randomSentiment;

    AzureAPI *azureApi;

};

#endif // INTERFACEHANDLER_H
