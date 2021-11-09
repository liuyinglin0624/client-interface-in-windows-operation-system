#ifndef CAUDIO_H
#define CAUDIO_H

#include <QObject>
#include<QAudioFormat>
#include<QAudioDeviceInfo>
#include<QAudioInput>
#include<QFile>
class CAudio : public QObject
{
    Q_OBJECT
public:
    explicit CAudio(QObject *parent = nullptr);

public:
    // 开始录音
    bool startAudio(QString fileName);
    // 停止录音
    void stopAudio();
signals:

private:
    QAudioInput* m_Audio;
    QFile*      m_file;

};

#endif // CAUDIO_H
