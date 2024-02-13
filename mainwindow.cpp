#include <cassert>
#include <iostream>
#include <utility>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

static const std::string seed =
    "-A^B=1  f(A)=B  f(B)=BA-\n"
    "=44 3 17 2 anichrist!!!=\n"
    "^f(BA) = f(B)f(A) = BAB$\n"
    "^Decree of trude partei$\n"
    "f(BAB)=f(BA)f(B)=BAраBBA\n";

std::pair<int, int> dim()
{
	const std::string &str = seed;
	assert(str.back() == '\n');
	int x = str.find('\n');
	int y = std::count(str.begin(), str.end(), '\n');
	const auto s = QString::fromStdString(str);
	assert(s.size() == (x + 1) * y);
	return std::make_pair(x, y);
}

QString blocks()
{
	const auto str = QString::fromStdString(seed);
	QStringList ret;
	int block_w = 3;
	int block_h = dim().second;
	for (int i = 0; i < dim().first / block_w; ++i) {
		QString s;
		s.resize((block_h + 1) * block_w, '\n');
		ret.push_back(s);
	}
	int x = 0, y = 0;
	for (const auto c : str) {
		if (c == '\n') {
			x = 0;
			++y;
			continue;
		}
		int i = x / block_w;
		int j = (x % block_w) * (block_h + 1) + y;
		ret[i][j] = c;
		x++;
	}
	const auto acc = [](const QStringList &list) {
		QString ret;
		for (const auto s : list) {
			ret += s;
			ret += '\n';
		}
		return ret;
	};
	return acc(ret);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->command->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_command_returnPressed()
{
    const auto cmd = ui->command->text();
    ui->command->setText(QString());
    if (cmd == "seed")
        log(QString::fromStdString(seed));
    else if (cmd == "dim")
	log(QString("%1 %2").arg(dim().first).arg(dim().second));
    else if (cmd == "blocks")
	log(blocks());
    else if (cmd == "format") {
        log("creating storage");
    }
}

void MainWindow::log(QString message)
{
    ui->log->append(message);
}
