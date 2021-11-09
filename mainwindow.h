#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"qmytcpclient.h"
#include"Packdef.h"
#include<string>
#include"QStringListModel"
#include"CCtrlDashBoard.h"
#include<map>
#include"cspeech.h"
#include"caudio.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void sendMessage();
    void slot_ReadyData( char* szbuf , int nLen );
    void slot_GetChatterRs(char* szbuf , int nLen );
    void slot_GetSpeedInfo(char* szbuf , int nLen );
    void slot_GetStopRs(char* szbuf , int nLen );
    void slot_GetbaseMoveA1Rs(char* szbuf , int nLen );
public slots:
    void slot_AnalysisReadyDate(char* szbuf , int nLen);
    void slot_AnalysisChatterRs(char* szbuf , int nLen);
    void slot_AnalysisFailRs(char* szbuf , int nLen);
    void slot_AnalysisBaseMoveRs(char* szbuf , int nLen);
public slots:
    void slot_LinerSpeedValueChange(int val);
    void slot_AngerSpeedValueChange(int val);
    void slot_pushButtonClick();
    void slot_pushButtonRelease();
    void slot_pressVoice();
    void slot_releaseVoice();
    void closeEvent(QCloseEvent *event);
private:
    void Logging(std::string msg);
    void InitKey2Command();
private:
    Ui::MainWindow *ui;
    QMyTcpClient* m_pKernel;
    QMyTcpClient* m_pAnalysis;
    QStringListModel m_logging_model;
    CCtrlDashBoard* m_LinerSpeed_DashBoard;
    CCtrlDashBoard* m_AngerSpeed_DashBoard;
    std::map<char,std::vector<std::string>> m_mapKey2Command;
    CAudio* m_audio;
};

struct protocal_map
{
    PackType m_nType;
    void (MainWindow::*PFUN)(char*,int);
};

struct protocal_analysis_map
{
    PackType m_nType;
    void (MainWindow::*PFUN)(char*,int);
};

#endif // MAINWINDOW_H
