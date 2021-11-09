#include "cspeech.h"

CSpeech::CSpeech(QObject *parent) : QObject(parent)
{

}

QString CSpeech::speechIdentify(QString fileName)
{
    // 获取access_token;
    QString tokenUrl = QString(baidu_token).arg(client_id).arg(client_secret);

    QMap<QString,QString> header;
    header.insert(QString("Content-Type"),QString("audio/pcm;rate=16000"));

    QByteArray requestDate;  // 请求内容
    QByteArray replyDate;   // 回复内容

    Http m_http;
    bool result = m_http.post_sync(tokenUrl,header,requestDate,replyDate);
    QString strToken;
    if(result)
    {
        QString key = "access_token";
        strToken = getJsonValue(replyDate,key);
    }
    else
    {
        qDebug() << "获取token失败";
    }
    qDebug() << strToken;
    //识别语音
    QString strUrl = QString(baidu_speech).arg(QHostInfo::localHostName()).arg(strToken);

    //文件转换为QbyteArrsy;
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly);
    requestDate = file.readAll();
    file.close();

    // 发起请求
    replyDate.clear();
    QString strText;
    bool result_speech = m_http.post_sync(strUrl,header,requestDate,replyDate);
    qDebug() << replyDate;
    if(result_speech)
    {
        QString key = "result";
        strText = getJsonValue(replyDate,key);
        qDebug() << strText;
        return strText;
    }
    else
    {
        qDebug() << "解析失败";
    }

    return QString("");
}

// 解析Json
QString CSpeech::getJsonValue(QByteArray replyDate,QString key)
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(replyDate,&jsonError);
    // json没有问题的情况
    if(jsonError.error == QJsonParseError::NoError)
    {
        // 对象存在
        if(document.isObject())
        {
            QJsonObject obj = document.object();
            // object中包含key
            if(obj.contains(key))
            {
                QJsonValue value = obj.value(key);
                // 字符串
                if(value.isString())
                {
                    return value.toString();
                }
                // 数组
                else if(value.isArray())
                {
                    QJsonArray arr = value.toArray();
                    return arr[0].toString();
                }
            }
        }
    }
    return "";
}
