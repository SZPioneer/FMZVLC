#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void    onMenuUdpData();

private:
    Ui::MainWindow *ui;

    QUdpSocket*         m_pUDPHI;

private:
    int             m_iZoomVal          = 0;
    int             m_iBrightVal        = 0;
};

#endif // MAINWINDOW_H
