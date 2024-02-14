#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class Field;

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

private slots:
    void on_command_returnPressed();
    void log(QString);

private:
    Ui::MainWindow *ui;
    Field *board[8][8];
    Field *create_field(QString);
};
#endif // MAINWINDOW_H
