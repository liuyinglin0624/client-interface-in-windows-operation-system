#include "http.h"
#include"QDebug"
Http::Http(QObject *parent) : QObject(parent)
{

}

bool Http::post_sync(QString Url,QMap<QString,QString> mapHeader ,QByteArray requestDate,QByteArray &replyDate)
{
    QNetworkAccessManager manager; // 发送请求对象
    QNetworkRequest request;// 具体请求

    request.setUrl(Url);
    QMap<QString,QString>::iterator ite = mapHeader.begin();
    while(ite != mapHeader.end())
    {
        request.setRawHeader(ite.key().toLatin1(),ite.value().toLatin1());
        ite++;
    }

    QNetworkReply* reply = manager.post(request,requestDate);
    QEventLoop l;

    // 返回服务器发送信号
    connect(reply,&QNetworkReply::finished,&l,&QEventLoop::quit);
    l.exec();  // 循环等待,返回结束循环

    if(reply != nullptr && reply->error() == QNetworkReply::NoError)
    {
        replyDate = reply->readAll();

        return true;
    }

    return false;
}
