#include "caudio.h"
#include"QMessageBox"
CAudio::CAudio(QObject *parent) : QObject(parent)
{

}

bool CAudio::startAudio(QString fileName)
{
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice(); // 获取默认的输入设备
    if(device.isNull())
    {
        QMessageBox::information(NULL,"提示","录音设备不存在");
        return false;
    }

    // 音频编码要求
    QAudioFormat m_format;
    m_format.setSampleRate(16000);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec(QString("audio/pcm"));

    // 判断设备是否支持该格式
    if(!device.isFormatSupported(m_format))
    {
        m_format = device.nearestFormat(m_format);
    }
    // 打开音频文件
    this->m_file = new QFile;
    m_file->setFileName(fileName);
    m_file->open(QIODevice::WriteOnly);

    this->m_Audio = new QAudioInput(m_format,this);
    m_Audio->start(m_file);

}

void CAudio::stopAudio()
{
    this->m_Audio->stop();
    this->m_file->close();
    delete m_file;
    m_file = NULL;
}
