#include <fstream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

static const std::string seed =
    "-A^B=1  f(A)=B  f(B)=BA-\n"
    "=44 3 17 2 anichrist!!!=\n"
    "^f(BA) = f(B)f(A) = BAB$\n"
    "^Decree of trude partei$\n"
    "f(BAB)=f(BA)f(B)=BAраBBA\n";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_command_returnPressed()
{
    const auto cmd = ui->command->text();
    if (cmd == "seed")
        log(QString::fromStdString(seed));
    else if (cmd == "format") {
        log("creating storage");
    }
}

void MainWindow::log(QString message)
{
    ui->log->append(message);
}
