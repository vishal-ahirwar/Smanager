#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void onAboutClicked();
private slots:
    void on_actionQuit_triggered();

    void on_actionRestart_triggered();

    void on_btn_set_timer_clicked();

    void on_btn_cancel_timer_2_clicked();

    void on_btn_set_timer_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
