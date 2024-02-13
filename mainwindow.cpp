#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <utility>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

static const std::string seed =
    "-A^B=1  f(A)=B  f(B)=BA-\n"
    "=44 3 17 2 anichrist!!!=\n"
    "^f(BA) = f(B)f(A) = BAB$\n"
    "^Decree of trude partei$\n"
    "f(BAB)=f(BA)f(B)=BAраBBA\n";

static const std::string board =
    "85076   71518   66954   71463   88351   75094  187258   66540\n"
    "71518   68649   59043   62711   79339   65419  183610   62189\n"
    "66954   59043   63942   59170   69775   63719  212875   52339\n"
    "71463   62711   59170   71945   76417   72660  178287   58128\n"
    "88351   79339   69775   76417  108757   89332  202084   74788\n"
    "75094   65419   63719   72660   89332   88322  210994   60839\n"
    "187258  183610  212875  178287  202084  210994 2419643  199576\n"
    "66540   62189   52339   58128   74788   60839  199576   61841\n";


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

QStringList blocks()
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
	return ret;
}

QString hexdump(QString str)
{
	QString ret;
	int offset = 0;
	for (const auto c : str) {
		if (c == '\n')
			ret += c;
		else
			ret += QString("%1 ").arg(c.unicode());
	}
	return ret;
}

QString hexdump(QStringList list)
{
	QString ret;
	for (const auto s : list)
		ret += hexdump(s);
	return ret;
}

QString unique()
{
    std::istringstream I(board);
    int i;
    std::map<int, int> seen;
    while (I >> i) {
        ++seen[i];
    }
    QString ret;
    for (const auto p : seen)
        ret += QString("%1:%2, ").arg(p.first).arg(p.second);
    if (ret.size() == 0)
        return "unique";
    return ret;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->command->setFocus();
    QGridLayout *layout = new QGridLayout(ui->tab_board);
    std::istringstream I(::board);
    const int boardsize = 8;
    for (int i = 0; i < boardsize; i++) {
        QLabel *label = new QLabel(ui->tab_board);
        layout->addWidget(label, boardsize, i + 1);
        label->setFont(ui->log->font());
        label->setText(QString::asprintf("%c", 'a' + i));
        label = new QLabel(ui->tab_board);
        layout->addWidget(label, i, 0);
        label->setFont(ui->log->font());
        label->setText(QString::asprintf("%i", boardsize - i));
    }
    for (int i = 0; i < boardsize; i++)
        for (int j = 0; j < boardsize; j++) {
            //const auto field = QString::asprintf("%c%i", 'a' + j, boardsize - i);
            //field = QString();
            auto label = new QLabel(ui->tab_board);
            //label->setText(field);
            label->setFont(ui->log->font());
            board[i][j] = label;
            layout->addWidget(board[i][j], i, j + 1);
            int data;
            I >> data;
            unsigned char r = data / 128 / 128;
            unsigned char g = data / 128;
            unsigned char b = data;
            //QColor color{QRgb(data)};
            const auto c = QString::asprintf("#%02x%02x%02x", r, g, b);
            //log(c);
            board[i][j]->setStyleSheet("color: yellow; background-color: \"" + c + "\";");
        }
    ui->tab_board->setLayout(layout);
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
    else if (cmd == "board")
        log(QString::fromStdString(::board));
    else if (cmd == "unique")
        log(unique());
    else if (cmd == "dim")
        log(QString("%1 %2").arg(dim().first).arg(dim().second));
    else if (cmd == "blocks")
        log(hexdump(blocks()));
    else if (cmd == "format") {
        log("creating storage");
    }
}

void MainWindow::log(QString message)
{
    ui->log->append(message);
}
