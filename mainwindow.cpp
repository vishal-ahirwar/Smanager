#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QApplication>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->info_txt->setAlignment(Qt::AlignBottom);
    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::onAboutClicked);
    ui->btn_cancel_timer_2->setDisabled(true);
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

    if(!system("shutdown -c"))ui->cnfrm_txt->setText("poweroff timer has been canceled successfuly!");
    else ui->cnfrm_txt->setText("Failed to cancel poweroff Timer, Unknown Error Occurred!");
    ui->btn_cancel_timer_2->setDisabled(true);
}


void MainWindow::on_btn_set_timer_2_clicked()
{
    auto result=QMessageBox::question(this,"poweroff now","are you sure you wanna shutdown now?");
    if(result)
    {
#if defined(WIN32)
        system("shutdown /h");
#else
        system("poweroff");
#endif
    }

}

