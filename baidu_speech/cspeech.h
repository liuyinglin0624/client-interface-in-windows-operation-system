#ifndef CSPEECH_H
#define CSPEECH_H

#include <QObject>
#include"http.h"
#include"QJsonDocument"
#include"QJsonObject"
#include"QJsonArray"
#include"QHostInfo"
#include"QByteArray"
#include"QFile"

const QString baidu_token = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "r6iiRdSl9NP8m0B4PEfySl7I";
const QString client_secret = "Nl8V4umYdsslrK1Bd65eprigwziQfq2C";

const QString baidu_speech = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";

class CSpeech : public QObject
{
    Q_OBJECT
public:
    explicit CSpeech(QObject *parent = nullptr);
    // 语音听写
    QString speechIdentify(QString fileName);
    // 解析json返回值
    QString getJsonValue(QByteArray replyDate,QString key);
signals:
private:

};

#endif // CSPEECH_H
