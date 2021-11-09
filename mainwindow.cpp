#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitKey2Command();
    this->ui->listView_logging->setModel(&this->m_logging_model);

    this->ui->lineEdit_IP->setText(QString(_DEF_SERVERIP));
    this->ui->lineEdit_port->setText(QString().number(_DEF_PORT));
    this->ui->checkBox_auto_connect->setCheckState(Qt::CheckState::Checked);

    this->m_AngerSpeed_DashBoard = new CCtrlDashBoard(this->ui->widget_anger_speed,false,CCtrlDashBoard::ST_ARCBAR);
    this->m_LinerSpeed_DashBoard = new CCtrlDashBoard(this->ui->widget_liner_speed);
    this->m_AngerSpeed_DashBoard->setGeometry(this->ui->widget_anger_speed->rect());
    this->m_LinerSpeed_DashBoard->setGeometry(this->ui->widget_liner_speed->rect());
    this->m_AngerSpeed_DashBoard->setValue(0);
    this->m_LinerSpeed_DashBoard->setValue(0);
    this->ui->horizontalSlider_angerspeed->setValue(180);
    this->ui->horizontalSlider_linerspeed->setValue(100);
    this->m_pKernel = new QMyTcpClient;
    m_pAnalysis = new QMyTcpClient;

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendMessage()));

    if(this->m_pKernel->InitNetWork(_DEF_SERVERIP,_DEF_PORT))
    {
        Logging("connect server successfully");
    }
    else
    {
        Logging("connect server fail");
    }

    if(this->m_pAnalysis->InitNetWork(_DEF_COMMANDANALYSISIP,_DEF_COMMANDANALYSISPORT))
    {
        Logging("connect command_analysis server sueecssfully");
    }
    else
    {
        Logging("connect command_analysis server fail");
    }

    connect(this->ui->horizontalSlider_angerspeed,SIGNAL(valueChanged(int)),this,SLOT(slot_AngerSpeedValueChange(int)));

    connect(this->ui->horizontalSlider_linerspeed,SIGNAL(valueChanged(int)),this,SLOT(slot_LinerSpeedValueChange(int)));

    connect(this->m_pKernel,SIGNAL(SIG_ReadyData(char*,int)),this,SLOT(slot_ReadyData(char*,int)));

    connect(this->m_pAnalysis,SIGNAL(SIG_ReadyData(char*,int)),this,SLOT(slot_AnalysisReadyDate(char*,int)));

    // 键盘控制节点
    connect(this->ui->pushButton_up,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));
    connect(this->ui->pushButton_down,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));
    connect(this->ui->pushButton_left,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));
    connect(this->ui->pushButton_right,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));
    connect(this->ui->pushButton_stop,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));
    connect(this->ui->pushButton_leftup,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));
    connect(this->ui->pushButton_rightup,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));
    connect(this->ui->pushButton_leftdown,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));
    connect(this->ui->pushButton_rightdown,SIGNAL(pressed()),this,SLOT(slot_pushButtonClick()));

    connect(this->ui->pushButton_up,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));
    connect(this->ui->pushButton_down,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));
    connect(this->ui->pushButton_left,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));
    connect(this->ui->pushButton_right,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));
    connect(this->ui->pushButton_stop,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));
    connect(this->ui->pushButton_leftup,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));
    connect(this->ui->pushButton_rightup,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));
    connect(this->ui->pushButton_leftdown,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));
    connect(this->ui->pushButton_rightdown,SIGNAL(released()),this,SLOT(slot_pushButtonRelease()));

    connect(this->ui->toolButton_stop,SIGNAL(clicked()),this,SLOT(slot_pushButtonRelease()));


    connect(this->ui->pushButton_voice,SIGNAL(pressed()),this,SLOT(slot_pressVoice()));
    connect(this->ui->pushButton_voice,SIGNAL(released()) , this, SLOT(slot_releaseVoice()));

    this->m_audio = new CAudio;

}

MainWindow::~MainWindow()
{
    delete ui;
}

protocal_map Protocalmap_Entry[]=
{
    {DEF_PACK_CHATTER_RS,&MainWindow::slot_GetChatterRs},
    {DEF_PACK_SPEED_INFO,&MainWindow::slot_GetSpeedInfo},
    {DEF_PACK_STOP0_RS  ,&MainWindow::slot_GetStopRs},
    {DEF_PACK_BASEMOVEA1_RS ,&MainWindow::slot_GetbaseMoveA1Rs},
    {0,0}
};

protocal_analysis_map Analysismap_Entry[] =
{
    {DEF_ANALYSIS_FAIL_RS,&MainWindow::slot_AnalysisFailRs},
    {DEF_ANALYSIS_CHATTER_RS,&MainWindow::slot_AnalysisChatterRs},
    {DEF_ANALYSIS_BASEMOVE_RS,&MainWindow::slot_AnalysisBaseMoveRs},
    {0,0}
};

void MainWindow::InitKey2Command()
{
    this->m_mapKey2Command['i'] = std::vector<std::string>{"MOV","UP"};
    this->m_mapKey2Command['j'] = std::vector<std::string>{"TURN","LEFT"};
    this->m_mapKey2Command[','] = std::vector<std::string>{"MOV","DOWN"};
    this->m_mapKey2Command['l'] = std::vector<std::string>{"TURN","RIGHT"};
    this->m_mapKey2Command['u'] = std::vector<std::string>{"MOV","UPLEFT"};
    this->m_mapKey2Command['o'] = std::vector<std::string>{"MOV","UPRIGHT"};
    this->m_mapKey2Command['m'] = std::vector<std::string>{"MOV","DOWNLEFT"};
    this->m_mapKey2Command['.'] = std::vector<std::string>{"MOV","DOWNRIGHT"};
    this->m_mapKey2Command['k'] = std::vector<std::string>{"STOP"};

    this->m_mapKey2Command['I'] = std::vector<std::string>{"MOV","UP"};
    this->m_mapKey2Command['J'] = std::vector<std::string>{"TURN","LEFT"};
    this->m_mapKey2Command['<'] = std::vector<std::string>{"MOV","DOWN"};
    this->m_mapKey2Command['L'] = std::vector<std::string>{"TURN","RIGHT"};
    this->m_mapKey2Command['U'] = std::vector<std::string>{"MOV","UPLEFT"};
    this->m_mapKey2Command['O'] = std::vector<std::string>{"MOV","UPRIGHT"};
    this->m_mapKey2Command['M'] = std::vector<std::string>{"MOV","DOWNLEFT"};
    this->m_mapKey2Command['>'] = std::vector<std::string>{"MOV","DOWNRIGHT"};
    this->m_mapKey2Command['K'] = std::vector<std::string>{"STOP"};
}
//////////////////////////////analysis_recv///////////////////////////////
void MainWindow::slot_AnalysisFailRs(char* szbuf , int nLen)
{
    Logging("指令解析失败，请重新输入");
}

void MainWindow::slot_AnalysisBaseMoveRs(char* szbuf , int nLen)
{
    STRU_ANALYSIS_BASEMOVE_RS * rq = (STRU_ANALYSIS_BASEMOVE_RS*)szbuf;
    Logging(QString("Analysis success:%1,%2,%3").arg(rq->m_szContext1).arg(rq->m_szContext2).arg(rq->m_szContext3).toStdString());

    QString strAction = rq->m_szContext1;
    QString strForward = rq->m_szContext2;

    // 对于拐弯的语音指令,添加限定
    if(strAction == "TURN")
    {
        sprintf(rq->m_szContext3,"%d",90);
    }

    STRU_BASEMOVEA1_RQ rs;
    sprintf(rs.m_szAction,rq->m_szContext1);
    sprintf(rs.m_szForward,rq->m_szContext2);
    sprintf(rs.m_szDistance,rq->m_szContext3);

    rs.m_nAngleSpeed = this->ui->horizontalSlider_angerspeed->value();
    rs.m_nlinearSpeed = this->ui->horizontalSlider_linerspeed->value();

    this->m_pKernel->SendData((char*)&rs,sizeof(rs));
    return ;
}

void MainWindow::slot_AnalysisChatterRs(char* szbuf , int nLen)
{
    STRU_ANALYSIS_CHART_RS* rs = (STRU_ANALYSIS_CHART_RS*)szbuf;
    Logging(rs->m_szContext);
}

void MainWindow::slot_AnalysisReadyDate(char* szbuf , int nLen)
{
    PackType* pack = (PackType*)szbuf;
    int i = 0;
    while(Analysismap_Entry[i].m_nType != 0 && Analysismap_Entry[i].PFUN != 0)
    {
        if(Analysismap_Entry[i].m_nType == *pack)
        {
            (this->*Analysismap_Entry[i].PFUN)(szbuf,nLen);
            break;
        }
        i++;
    }

}
//////////////////////////////analysis_recv///////////////////////////////
void MainWindow::slot_pushButtonRelease()
{
    STRU_STOP0_RQ rq;
    this->m_pKernel->SendData((char*)&rq,sizeof(rq));
    return;
}

void MainWindow::slot_pressVoice()
{
    this->ui->pushButton_voice->setIcon(QIcon(":/processing.png"));
    this->ui->label_state->setText(QString("松开完成"));

    this->m_audio->startAudio("./temp_video/temp.pcm");

}

void MainWindow::slot_releaseVoice()
{
    this->m_audio->stopAudio();
    this->ui->label_state->setText(QString("正在解析"));

    CSpeech speech;
    QString textRes = speech.speechIdentify("./temp_video/temp.pcm");
    Logging(textRes.toStdString());
    QChar val1 = textRes[0];
    if(val1 == "停")
    {
        STRU_STOP0_RQ rq;
        this->m_pKernel->SendData((char*)&rq,sizeof(rq));
        return;
    }

    this->ui->pushButton_voice->setIcon(QIcon(":/voice_record.png"));
    this->ui->label_state->setText(QString("按下说话"));
    // 将请求发送回去
    STRU_ANALYSIS_SPEECHRQ rq;
    sprintf(rq.m_szContext,textRes.toStdString().c_str());
    //sprintf_s(rq.m_szContext,MAX_SIZE,textRes.toStdString().c_str());
    this->m_pAnalysis->SendData((char*)&rq,sizeof(rq));

    this->ui->pushButton_voice->setIcon(QIcon(":/voice_record.png"));
    this->ui->label_state->setText(QString("按下说话"));
}


//////////////////////////////robot_contral///////////////////////////////
void MainWindow::slot_GetbaseMoveA1Rs(char* szbuf , int nLen )
{
    STRU_BASEMOVEA1_RS* rs = (STRU_BASEMOVEA1_RS*)szbuf;
    if(rs->m_nResult)
    {
        Logging("BaseMoving success");
    }
    else
    {
        Logging("BaseMoving fail");
    }
}

void MainWindow::slot_GetStopRs(char* szbuf , int nLen )
{
    STRU_STOP0_RS* rs = (STRU_STOP0_RS*)szbuf;
    if(rs->m_nResult)
    {
        Logging("STOP success");
    }
    else
    {
        Logging("STOP fail");
    }
}

void MainWindow::slot_GetSpeedInfo(char* szbuf , int nLen )
{
    STRU_SPEED_INFO* si = (STRU_SPEED_INFO*)szbuf;

    this->m_AngerSpeed_DashBoard->setValue(abs(si->m_fAngerSpeed* 100) );
    this->m_LinerSpeed_DashBoard->setValue(abs(si->m_fLinearSpeed * 100));

    if(si->m_fAngerSpeed > 0)
    {
        this->ui->label_angerforward->setText(QString("positive"));
    }
    else
    {
        this->ui->label_angerforward->setText(QString("negative"));
    }

    if(si->m_fLinearSpeed > 0)
    {
        this->ui->label_linerforward->setText(QString("positive"));
    }
    else
    {
        this->ui->label_linerforward->setText(QString("negative"));
    }
}

void MainWindow::slot_pushButtonClick()
{
    QPushButton* btn = (QPushButton*)sender();
    std::string strKey = btn->text().toStdString();
    std::string strTemp;

    // 拿到键盘字母
    std::vector<std::string> vecCommand = this->m_mapKey2Command[btn->text().toStdString()[0]];

    // 将字符发送出去
    if(vecCommand.size() == 1)
    {
        STRU_STOP0_RQ rq;
        this->m_pKernel->SendData((char*)&rq,sizeof(rq));
        return ;
    }
    if(vecCommand.size() == 2)
    {
        STRU_BASEMOVEA1_RQ rq;
        strcpy_s(rq.m_szAction,COMMAND_LENGTH,vecCommand[0].c_str());
        strcpy_s(rq.m_szForward,COMMAND_LENGTH,vecCommand[1].c_str());
        rq.m_nlinearSpeed = this->ui->horizontalSlider_linerspeed->value();
        rq.m_nAngleSpeed = this->ui->horizontalSlider_angerspeed->value();
        this->m_pKernel->SendData((char*)&rq,sizeof(rq));
        return ;
    }
}

void MainWindow::slot_LinerSpeedValueChange(int val)
{
    this->ui->label_setliner->setText(QString("linear_speed:%1").arg(val));
}

void MainWindow::slot_AngerSpeedValueChange(int val)
{
    this->ui->label_setangers->setText(QString("anger_speed:%1").arg(val));
}

void MainWindow::slot_GetChatterRs(char* szbuf , int nLen )
{
    STRU_CHATTRE_RS* rs = (STRU_CHATTRE_RS*)szbuf;
    std::string strTitle = "【service】: ";
    strTitle += rs->m_szContext;
    Logging(strTitle);
}

void MainWindow::slot_ReadyData( char* szbuf , int nLen )
{
    PackType* pack = (PackType*)szbuf;
    int i = 0;
    while(Protocalmap_Entry[i].m_nType != 0 && Protocalmap_Entry[i].PFUN != 0)
    {
        if(Protocalmap_Entry[i].m_nType == *pack)
        {
            (this->*Protocalmap_Entry[i].PFUN)(szbuf,nLen);
            break;
        }
        i++;
    }
}
//////////////////////////////robot_contral///////////////////////////////


void MainWindow::sendMessage()
{
    STRU_CHATTRE_RQ rq;
    sprintf(rq.m_szContext,"chatter:[hello server]");
    this->m_pKernel->SendData((char*)&rq,sizeof(rq));

    STRU_ANALYSIS_CHART_RQ anaRq;
    sprintf(anaRq.m_szContext,"chatter:[hello server]");
    this->m_pAnalysis->SendData((char*)&anaRq,sizeof(anaRq));
}

void MainWindow::Logging(std::string msg)
{
    this->m_logging_model.insertRows(this->m_logging_model.rowCount(),1);

    QVariant new_row(msg.c_str());
    this->m_logging_model.setData(this->m_logging_model.index(m_logging_model.rowCount()-1),new_row);

    this->ui->listView_logging->scrollToBottom();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    STRY_ANALYSIS_QUIT_RQ rq;
    this->m_pAnalysis->SendData((char*)&rq,sizeof(rq));
}


