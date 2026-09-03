#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>

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
    QMenu *menu;
    QPalette *oldPalette;
    void history_QStyle();
    void white_QPalette();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
