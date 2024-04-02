#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QApplication>
#include<QMessageBox>
#include<fstream>
namespace  {
const char*StateFile{"smanager.cnf"};
}
int MainWindow::SaveState(int flag)
{
    std::fstream file;
    file.open(StateFile,std::ios_base::out);
    if(file.is_open())
    {
        file<<flag;
        file.close();
        return 0;
    }else
    {
        QMessageBox::critical(this,"Something went wrong!","Failed to Create State File!");
        return -1;
    };

};
int MainWindow::LoadState(int&flag)
{
    std::fstream file;
    file.open(StateFile,std::ios_base::in);
    if(file.is_open())
    {
        file>>flag;
        file.close();
        return 0;
    }else
    {
        return -1;
    };
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->info_txt->setAlignment(Qt::AlignBottom);
    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::onAboutClicked);
    int flag{0};
    if(LoadState(flag)==-1)SaveState(0);
    ui->btn_cancel_timer_2->setDisabled(!flag);
    if(flag)
    {
        ui->cnfrm_txt->setText("Warning: Shutdown is already in Queue please Cancel the Timer First");
        ui->btn_set_timer->setDisabled(true);
    }
}
void MainWindow::onAboutClicked()
{
    QApplication::aboutQt();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionRestart_triggered()
{
    QApplication::beep();
}


void MainWindow::on_btn_set_timer_clicked()
{
    ui->btn_cancel_timer_2->setDisabled(false);
    SaveState(1);
#if defined(WIN32)
    QString cmd{" shutdown -s -t "};
    cmd+=QString::number(ui->seconds->value()*60);
#else
    QString cmd{"shutdown -P +"};
    cmd+=QString::number(ui->seconds->value());
#endif
    if(!system(cmd.toStdString().c_str()))this->ui->cnfrm_txt->setText(QString("Machine will shutdown in ")+QString::number(ui->seconds->value())+"minutes");
    else this->ui->cnfrm_txt->setText("Failed to set poweroff timer!");
}


void MainWindow::on_btn_cancel_timer_2_clicked()
{
    SaveState(0);
#if defined(WIN32)
    if(!system("shutdown -a"))ui->cnfrm_txt->setText("poweroff timer has been canceled successfuly!");
    else ui->cnfrm_txt->setText("Failed to cancel poweroff Timer, Unknown Error Occurred!");
    ui->btn_cancel_timer_2->setDisabled(true);
#else
    if(!system("shutdown -c"))ui->cnfrm_txt->setText("poweroff timer has been canceled successfuly!");
    else ui->cnfrm_txt->setText("Failed to cancel poweroff Timer, Unknown Error Occurred!");
    ui->btn_cancel_timer_2->setDisabled(true);
#endif
}


void MainWindow::on_btn_set_timer_2_clicked()
{
    auto result=QMessageBox::question(this,"poweroff now","are you sure you wanna shutdown now?");
    if(result==QMessageBox::Yes)
    {
#if defined(WIN32)
        system("shutdown /h");
#else
        system("poweroff");
#endif
    }

}

