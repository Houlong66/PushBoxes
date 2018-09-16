#include "mainwindow.h"
#include <QLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLineEdit>
#include <QDebug>
#include<QVector>
#include<QDataStream>
#include<fstream>
#include<QInputDialog>
mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);


	createMenu();//�����˵����Ķ�����

	createAction();//�����˵�����һ����

	widget = new QWidget;

	setCentralWidget(widget);

	levelLabel = new QLabel(QStringLiteral("��ǰ�ؿ�"));

	stepLabel_1 = new QLabel(QStringLiteral("1����ҵ�ǰ����"));
	stepLabel_2 = new QLabel(QStringLiteral("2����ҵ�ǰ����"));

	levelLCD = new QLCDNumber;

	stepLCD_1 = new QLCDNumber;
	stepLCD_2 = new QLCDNumber;

	restartButton = new QPushButton(QStringLiteral("���¿�ʼ"));
	connect(restartButton, SIGNAL(clicked()), this, SLOT(restartGameSlot()));

	restartButton_1 = new QPushButton(QStringLiteral("���1���¿�ʼ"));
	connect(restartButton_1, SIGNAL(clicked()), this, SLOT(restartGameSlot_1()));

	restartButton_2 = new QPushButton(QStringLiteral("���2���¿�ʼ"));
	connect(restartButton_2, SIGNAL(clicked()), this, SLOT(restartGameSlot_2()));

	restartButton->setEnabled(false);
	restartButton_1->setEnabled(false);
	restartButton_2->setEnabled(false);

	QVBoxLayout *rightLayout = new QVBoxLayout;

	//�Ҳ������
	rightLayout->addWidget(levelLabel);

	rightLayout->addWidget(levelLCD);

	rightLayout->addWidget(stepLabel_1);

	rightLayout->addWidget(stepLCD_1);

	rightLayout->addWidget(stepLabel_2);

	rightLayout->addWidget(stepLCD_2);

	rightLayout->addWidget(restartButton);

	rightLayout->addWidget(restartButton_1);

	rightLayout->addWidget(restartButton_2);

	rightLayout->addSpacing(210);

	mainmap = new mappaint;

	QHBoxLayout *mainLayout = new QHBoxLayout;

	mainLayout->addWidget(mainmap);

	mainLayout->addLayout(rightLayout);

	widget->setLayout(mainLayout);

	mainmap->levelNow = -1;

	mainmap->stepNow_1 = 0;

	mainmap->man_x_1 = 0;

	mainmap->man_y_1 = 0;

	mainmap->stepNow_2 = 0;

	mainmap->man_x_2 = 0;

	mainmap->man_y_2 = 0;


	mainmap->BeginOrEnd = start::endGame;


	mainmap->update();

	boxNum_1 = 0;
	boxNum_2 = 0;

	levelLCDShow();
	stepLCDShow_1();
	stepLCDShow_2();

	createMap();

	//**************���������趨****************

	setWindowTitle(QStringLiteral("˫��������С��Ϸ"));

	widget->setFocus();

	statusBar()->showMessage(QStringLiteral("��ӭ����������С��Ϸ"));

}

mainwindow::~mainwindow()
{

}

void mainwindow::createMenu()
{
	startGameActionForOne = new QAction(QStringLiteral("��ʼ������Ϸ"), this);

	startGameActionForOne->setShortcut(QKeySequence("Ctrl+O"));

	connect(startGameActionForOne, SIGNAL(triggered()), this, SLOT(startGameSlotForOne()));

	startGameActionForTwo = new QAction(QStringLiteral("��ʼ˫����Ϸ"), this);

	startGameActionForTwo->setShortcut(QKeySequence("Ctrl+T"));

	connect(startGameActionForTwo, SIGNAL(triggered()), this, SLOT(startGameSlotForTwo()));

	startGameActionForOne->setStatusTip(QStringLiteral("��ʼһ������Ϸ."));
	startGameActionForTwo->setStatusTip(QStringLiteral("��ʼһ������Ϸ."));

	restartGameAction = new QAction(QStringLiteral("���¿�ʼ"), this);

	restartGameAction->setShortcut(QKeySequence("Ctrl+R"));

	restartGameAction->setStatusTip(QStringLiteral("���¿�ʼ����."));

	restartGameAction->setEnabled(false);

	connect(restartGameAction, SIGNAL(triggered()), this, SLOT(restartGameSlot()));

	endGameAction = new QAction(QStringLiteral("������Ϸ"), this);

	endGameAction->setShortcut(QKeySequence("Ctrl+E"));

	endGameAction->setStatusTip(QStringLiteral("������ǰ��Ϸ."));

	endGameAction->setEnabled(false);

	connect(endGameAction, SIGNAL(triggered()), this, SLOT(endGameSlot()));

	previousGatesAction = new QAction(QStringLiteral("ǰһ�ؿ�"), this);

	previousGatesAction->setShortcut(QKeySequence("Ctrl+P"));

	previousGatesAction->setStatusTip(QStringLiteral("ѡ��ǰһ�ؿ�"));

	previousGatesAction->setEnabled(false);

	connect(previousGatesAction, SIGNAL(triggered()), this, SLOT(previousGatesSlot()));

	nextGatesAction = new QAction(QStringLiteral("��һ�ؿ�"), this);

	nextGatesAction->setShortcut(QKeySequence("Ctrl+N"));

	nextGatesAction->setStatusTip(QStringLiteral("ѡ���һ�ؿ�"));

	nextGatesAction->setEnabled(false);

	connect(nextGatesAction, SIGNAL(triggered()), this, SLOT(nextGatesSlot()));

	customGatesAction = new QAction(QStringLiteral("ѡ��ؿ�"), this);

	customGatesAction->setShortcut(QKeySequence("Ctrl+C"));

	customGatesAction->setStatusTip(QStringLiteral("ѡ������ؿ�"));

	connect(customGatesAction, SIGNAL(triggered()), this, SLOT(customGatesSlot()));

	aboutAction = new QAction(QStringLiteral("����"), this);

	aboutAction->setShortcut(QKeySequence("Ctrl+A"));

	aboutAction->setStatusTip(QStringLiteral("����Ϸ��Ϣ"));

	connect(aboutAction, SIGNAL(triggered()
	), this, SLOT(aboutSlot()));
}

void mainwindow::createAction()
{
	gameMenu = menuBar()->addMenu(QStringLiteral("��Ϸ"));

	gameMenu->addAction(startGameActionForOne);

	gameMenu->addAction(startGameActionForTwo);

	gameMenu->addAction(restartGameAction);

	gameMenu->addAction(endGameAction);

	gatesMenu = menuBar()->addMenu(QStringLiteral("ѡ��ؿ�"));

	gatesMenu->addAction(previousGatesAction);

	gatesMenu->addAction(nextGatesAction);

	gatesMenu->addAction(customGatesAction);

	helpMenu = menuBar()->addMenu(QStringLiteral("����"));

	helpMenu->addAction(aboutAction);
}

void mainwindow::startGameSlotForOne()
{
	mainmap->BeginOrEnd = start::startForOne;
	qDebug() << "start for one" << mainmap->BeginOrEnd;
	widget->setFixedSize(mainmap->map_x + 150, mainmap->map_y);
	this->setFixedSize(mainmap->map_x + 150, mainmap->map_y);
	startGame(0);
}
void mainwindow::startGameSlotForTwo()
{
	mainmap->BeginOrEnd = start::startForTwo;
	qDebug() << "start for two" << mainmap->BeginOrEnd;
	widget->setFixedSize(mainmap->map_x * 2 + 30 + 150, mainmap->map_y);
	this->setFixedSize(mainmap->map_x * 2 + 30 + 150, mainmap->map_y);
	startGame(0);
}

void mainwindow::startGame(int x)
{
	widget->setFocus();
	qDebug() << "start game mainmap->BeginOrEnd" << mainmap->BeginOrEnd;

	endGameAction->setEnabled(true);

	restartGameAction->setEnabled(true);

	restartButton->setEnabled(true);
	if (mainmap->BeginOrEnd == start::startForTwo)
	{
		restartButton_1->setEnabled(true);
		restartButton_2->setEnabled(true);
	}
	else if (mainmap->BeginOrEnd == start::startForOne)
	{
		restartButton_1->setEnabled(false);
		restartButton_2->setEnabled(false);
	}
	if (x != 0)
	{
		previousGatesAction->setEnabled(true);
	}
	else if (x != map.size() - 1)
	{
		nextGatesAction->setEnabled(true);
	}

	if (x == 0)
		previousGatesAction->setEnabled(false);
	else if (x == map.size())
		nextGatesAction->setEnabled(false);


	int a = 0, b = 0;
	findManPos(x, a, b);
	mainmap->man_x_2 = mainmap->man_x_1 = a;
	mainmap->man_y_2 = mainmap->man_y_1 = b;
	boxNum_1 = boxNum_2 = 0;

	mainmap->mapNow_1.resize(map[x].size());
	mainmap->mapNow_2.resize(map[x].size());
	for (int i = 0; i<map[x].size(); ++i)
	{
		(mainmap->mapNow_1)[i].resize(map[x][i].size());
		(mainmap->mapNow_2)[i].resize(map[x][i].size());
	}

	for (int i = 0; i<map[x].size(); i++)
	{
		for (int j = 0; j<map[x][i].size(); j++)
		{
			mainmap->mapNow_1[i][j] = map[x][i][j];
			mainmap->mapNow_2[i][j] = map[x][i][j];
		}
	}

	mainmap->mapNow_1[mainmap->man_x_1][mainmap->man_y_1] = DEFINE::GROUND;
	mainmap->mapNow_2[mainmap->man_x_2][mainmap->man_y_2] = DEFINE::GROUND;
	mainmap->levelNow = x;

	mainmap->stepNow_1 = 0;
	mainmap->stepNow_2 = 0;

	stepLCDShow_1();
	stepLCDShow_2();
	levelLCDShow();


	mainmap->update();

	levelLCDShow();

}

void mainwindow::findManPos(int x, int& man_x, int& man_y)
{

	for (int i = 0; i<map[x].size(); ++i)
	{
		for (int j = 0; j<map[x][i].size(); ++j)
		{
			if (map[x][i][j] == DEFINE::MAN)
			{

				man_x = i;
				man_y = j;
			}
		}
	}
}

void mainwindow::restartGameSlot()
{
	startGame(mainmap->levelNow);
}

void mainwindow::restartGameSlot_1()
{
	qDebug() << "restart 1";
	int a = 0, b = 0;
	findManPos(mainmap->levelNow, a, b);
	mainmap->man_x_1 = a;
	mainmap->man_y_1 = b;
	boxNum_1 = 0;

	mainmap->mapNow_1.resize(map[mainmap->levelNow].size());
	for (int i = 0; i<map[mainmap->levelNow].size(); ++i)
	{
		(mainmap->mapNow_1)[i].resize(map[mainmap->levelNow][i].size());
	}

	for (int i = 0; i<map[mainmap->levelNow].size(); i++)
	{
		for (int j = 0; j<map[mainmap->levelNow][i].size(); j++)
		{
			mainmap->mapNow_1[i][j] = map[mainmap->levelNow][i][j];
		}
	}

	mainmap->mapNow_1[mainmap->man_x_1][mainmap->man_y_1] = DEFINE::GROUND;

	mainmap->stepNow_1 = 0;

	stepLCDShow_1();

	mainmap->update();
	widget->setFocus();
}

void mainwindow::restartGameSlot_2()
{
	qDebug() << "restart 2";
	int a = 0, b = 0;
	findManPos(mainmap->levelNow, a, b);
	mainmap->man_x_2 = a;
	mainmap->man_y_2 = b;
	boxNum_2 = 0;

	mainmap->mapNow_2.resize(map[mainmap->levelNow].size());
	for (int i = 0; i<map[mainmap->levelNow].size(); ++i)
	{
		(mainmap->mapNow_2)[i].resize(map[mainmap->levelNow][i].size());
	}

	for (int i = 0; i<map[mainmap->levelNow].size(); i++)
	{
		for (int j = 0; j<map[mainmap->levelNow][i].size(); j++)
		{
			mainmap->mapNow_2[i][j] = map[mainmap->levelNow][i][j];
		}
	}

	mainmap->mapNow_2[mainmap->man_x_2][mainmap->man_y_2] = DEFINE::GROUND;

	mainmap->stepNow_2 = 0;

	stepLCDShow_2();

	mainmap->update();
	widget->setFocus();
}

void mainwindow::endGameSlot()
{
	endGameAction->setEnabled(false);

	restartButton->setEnabled(false);

	restartGameAction->setEnabled(false);

	previousGatesAction->setEnabled(false);

	nextGatesAction->setEnabled(false);

	mainmap->levelNow = 0;

	mainmap->stepNow_1 = 0;
	mainmap->stepNow_2 = 0;

	boxNum_1 = 0;
	boxNum_2 = 0;

	mainmap->BeginOrEnd = start::endGame;

	levelLCDShow();

	stepLCDShow_1();
	stepLCDShow_2();
	widget->setFixedSize(mainmap->map_x + 150, mainmap->map_y);
	this->setFixedSize(mainmap->map_x + 150, mainmap->map_y);

	mainmap->update();

	QMessageBox::information(this, QStringLiteral("��Ϸ����"), QStringLiteral("��Ϸ�ѽ�����"), QMessageBox::Ok);

}

void mainwindow::previousGatesSlot()
{
	startGame(mainmap->levelNow - 1);
}

void mainwindow::nextGatesSlot()
{
	startGame(mainmap->levelNow + 1);
}

void mainwindow::customGatesSlot()
{
	resize(200, 100);
	bool ok;
	int value = QInputDialog::getInt(this, QStringLiteral("�ؿ���"),
		QStringLiteral("��ѡ��ؿ���1-79�أ�"), 1, 1, 79, 1, &ok);

	if (ok)
	{
		if (mainmap->BeginOrEnd == start::endGame)
		{
			mainmap->BeginOrEnd = start::startForOne;
		}
		qDebug() << "value:" << value;
		startGame(value - 1);
	}

}



void mainwindow::aboutSlot()
{
	QMessageBox::information(this, QStringLiteral("�����̳�"),
		QStringLiteral("���1ʹ��WASD�����������2ʹ�÷��������")
		, QMessageBox::Ok);
}

void mainwindow::levelLCDShow()
{
	levelLCD->display(mainmap->levelNow + 1);
}

void mainwindow::stepLCDShow_1()
{
	stepLCD_1->display(mainmap->stepNow_1);
}
void mainwindow::stepLCDShow_2()
{
	stepLCD_2->display(mainmap->stepNow_2);
}

void mainwindow::keyPressEvent(QKeyEvent *e)
{
	qDebug() << mainmap->levelNow;
	if (!(mainmap->levelNow == -1))
	{
		qDebug() << "key press";
		qDebug() << mainmap->BeginOrEnd;
		if (mainmap->BeginOrEnd == startForOne)
		{
			switch (e->key())
			{
				qDebug() << "key press";
			case Qt::Key_Up:
				keyUp_1();
				break;

			case Qt::Key_Left:
				keyLeft_1();
				break;

			case Qt::Key_Right:
				keyRight_1();
				break;

			case Qt::Key_Down:
				keyDown_1();
				break;

			case Qt::Key_W:
				keyUp_1();
				break;

			case Qt::Key_A:
				keyLeft_1();
				break;

			case Qt::Key_D:
				keyRight_1();
				break;

			case Qt::Key_S:
				keyDown_1();
				break;

			default:
				break;
			}
		}
		else if (mainmap->BeginOrEnd == startForTwo)
		{
			switch (e->key())
			{
				qDebug() << "key press";
			case Qt::Key_Up:
				keyUp_2();
				break;

			case Qt::Key_Left:
				keyLeft_2();
				break;

			case Qt::Key_Right:
				keyRight_2();
				break;

			case Qt::Key_Down:
				keyDown_2();
				break;

			case Qt::Key_W:
				keyUp_1();
				break;

			case Qt::Key_A:
				keyLeft_1();
				break;

			case Qt::Key_D:
				keyRight_1();
				break;

			case Qt::Key_S:
				keyDown_1();
				break;

			default:
				break;
			}
		}
	}
}

void mainwindow::keyLeft_1()
{
	int manx = mainmap->man_x_1;

	int many = mainmap->man_y_1;

	if (many - 1<0 || mainmap->mapNow_1[manx][many - 1] == DEFINE::WALL)
		return;

	if (mainmap->mapNow_1[manx][many - 1] == DEFINE::GROUND
		|| mainmap->mapNow_1[manx][many - 1] == DEFINE::GOAL)
	{

		--mainmap->man_y_1;
		if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
			|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
			mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
		else
			mainmap->mapNow_1[manx][many] = map[mainmap->levelNow][manx][many];
	}

	if (mainmap->mapNow_1[manx][many - 1] == DEFINE::BOX)
	{

		if (many - 2<0 || mainmap->mapNow_1[manx][many - 2] == DEFINE::BOX
			|| mainmap->mapNow_1[manx][many - 2] == DEFINE::WALL)
			return;
		if (mainmap->mapNow_1[manx][many - 2] == DEFINE::GROUND)
		{
			if (map[mainmap->levelNow][manx][many - 1] == DEFINE::GOAL)
				boxNum_1--;

			mainmap->mapNow_1[manx][many - 2] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];

			--mainmap->man_y_1;
		}

		if (mainmap->mapNow_1[manx][many - 2] == DEFINE::GOAL)
		{

			if (map[mainmap->levelNow][manx][many - 1] != DEFINE::GOAL)
			{
				boxNum_1++;

			}
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];

			mainmap->mapNow_1[manx][many - 2] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];
			--mainmap->man_y_1;
		}

	}
	mainmap->stepNow_1++;
	stepLCDShow_1();
	mainmap->update();
	boxNumCheck_1();

}
void mainwindow::keyRight_1()
{
	int manx = mainmap->man_x_1;

	int many = mainmap->man_y_1;

	if (many + 1>mainmap->mapNow_1[0].size()
		|| mainmap->mapNow_1[manx][many + 1] == DEFINE::WALL)
	{
		return;
	}

	if (mainmap->mapNow_1[manx][many + 1] == DEFINE::GROUND
		|| mainmap->mapNow_1[manx][many + 1] == DEFINE::GOAL)
	{

		++mainmap->man_y_1;
		if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
			|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
			mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
		else
			mainmap->mapNow_1[manx][many] =
			map[mainmap->levelNow][manx][many];
	}

	if (mainmap->mapNow_1[manx][many + 1] == DEFINE::BOX)
	{
		if (many + 2>mainmap->mapNow_1[0].size()
			|| mainmap->mapNow_1[manx][many + 2] == DEFINE::BOX
			|| mainmap->mapNow_1[manx][many + 2] == DEFINE::WALL)
			return;
		if (mainmap->mapNow_1[manx][many + 2] == DEFINE::GROUND)
		{
			if (map[mainmap->levelNow][manx][many + 1] == DEFINE::GOAL)
				boxNum_1--;
			mainmap->mapNow_1[manx][many + 2] = DEFINE::BOX;
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];

			++mainmap->man_y_1;
		}

		if (mainmap->mapNow_1[manx][many + 2] == DEFINE::GOAL)
		{

			if (map[mainmap->levelNow][manx][many + 1] != DEFINE::GOAL)
			{
				boxNum_1++;
			}
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];

			mainmap->mapNow_1[manx][many + 2] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];
			++mainmap->man_y_1;
		}

	}
	mainmap->stepNow_1++;
	stepLCDShow_1();
	mainmap->update();
	boxNumCheck_1();

}
void mainwindow::keyUp_1()
{
	int manx = mainmap->man_x_1;

	int many = mainmap->man_y_1;

	if (manx - 1<0 || mainmap->mapNow_1[manx - 1][many] == DEFINE::WALL)
		return;

	if (mainmap->mapNow_1[manx - 1][many] == DEFINE::GROUND
		|| mainmap->mapNow_1[manx - 1][many] == DEFINE::GOAL)
	{

		--mainmap->man_x_1;
		if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
			|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
			mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
		else
			mainmap->mapNow_1[manx][many] =
			map[mainmap->levelNow][manx][many];
	}

	if (mainmap->mapNow_1[manx - 1][many] == DEFINE::BOX)
	{

		if (manx - 2<0 || mainmap->mapNow_1[manx - 2][many] == DEFINE::BOX
			|| mainmap->mapNow_1[manx - 2][many] == DEFINE::WALL)
			return;
		if (mainmap->mapNow_1[manx - 2][many] == DEFINE::GROUND)
		{
			if (map[mainmap->levelNow][manx - 1][many] == DEFINE::GOAL)
				boxNum_1--;

			mainmap->mapNow_1[manx - 2][many] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];

			--mainmap->man_x_1;
		}

		if (mainmap->mapNow_1[manx - 2][many] == DEFINE::GOAL)
		{

			if (map[mainmap->levelNow][manx - 1][many] != DEFINE::GOAL)
			{
				boxNum_1++;

			}
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];

			mainmap->mapNow_1[manx - 2][many] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx - 1][many];
			--mainmap->man_x_1;
		}

	}
	mainmap->stepNow_1++;
	stepLCDShow_1();
	mainmap->update();
	boxNumCheck_1();

}
void mainwindow::keyDown_1()
{
	int manx = mainmap->man_x_1;

	int many = mainmap->man_y_1;

	if (manx + 1>mainmap->mapNow_1[0].size()
		|| mainmap->mapNow_1[manx + 1][many] == DEFINE::WALL)
	{
		qDebug() << "error1";
		return;
	}

	if (mainmap->mapNow_1[manx + 1][many] == DEFINE::GROUND
		|| mainmap->mapNow_1[manx + 1][many] == DEFINE::GOAL)
	{

		++mainmap->man_x_1;
		if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
			|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
			mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
		else
			mainmap->mapNow_1[manx][many] =
			map[mainmap->levelNow][manx][many];
	}

	if (mainmap->mapNow_1[manx + 1][many] == DEFINE::BOX)
	{
		if (manx + 2>mainmap->mapNow_1[0].size()
			|| mainmap->mapNow_1[manx + 2][many] == DEFINE::BOX
			|| mainmap->mapNow_1[manx + 2][many] == DEFINE::WALL)
		{
			return;
		}
		if (mainmap->mapNow_1[manx + 2][many] == DEFINE::GROUND)
		{
			if (map[mainmap->levelNow][manx + 1][many] == DEFINE::GOAL)
				boxNum_1--;

			mainmap->mapNow_1[manx + 2][many] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];

			++mainmap->man_x_1;
		}

		if (mainmap->mapNow_1[manx + 2][many] == DEFINE::GOAL)
		{

			if (map[mainmap->levelNow][manx + 1][many] != DEFINE::GOAL)
			{
				boxNum_1++;
			}
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];

			mainmap->mapNow_1[manx + 2][many] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_1[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_1[manx][many] =
				map[mainmap->levelNow][manx][many];
			++mainmap->man_x_1;
		}

	}
	mainmap->stepNow_1++;
	stepLCDShow_1();
	mainmap->update();
	boxNumCheck_1();

}

void mainwindow::keyLeft_2()
{
	int manx = mainmap->man_x_2;

	int many = mainmap->man_y_2;

	if (many - 1<0 || mainmap->mapNow_2[manx][many - 1] == DEFINE::WALL)
		return;

	if (mainmap->mapNow_2[manx][many - 1] == DEFINE::GROUND
		|| mainmap->mapNow_2[manx][many - 1] == DEFINE::GOAL)
	{

		--mainmap->man_y_2;
		if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
			|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
			mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
		else
			mainmap->mapNow_2[manx][many] =
			map[mainmap->levelNow][manx][many];
	}

	if (mainmap->mapNow_2[manx][many - 1] == DEFINE::BOX)
	{

		if (many - 2<0 || mainmap->mapNow_2[manx][many - 2] == DEFINE::BOX
			|| mainmap->mapNow_2[manx][many - 2] == DEFINE::WALL)
			return;
		if (mainmap->mapNow_2[manx][many - 2] == DEFINE::GROUND)
		{
			if (map[mainmap->levelNow][manx][many - 1] == DEFINE::GOAL)
				boxNum_2--;

			mainmap->mapNow_2[manx][many - 2] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];

			--mainmap->man_y_2;
		}

		if (mainmap->mapNow_2[manx][many - 2] == DEFINE::GOAL)
		{

			if (map[mainmap->levelNow][manx][many - 1] != DEFINE::GOAL)
			{
				boxNum_2++;

			}
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];

			mainmap->mapNow_2[manx][many - 2] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];
			--mainmap->man_y_2;
		}

	}
	mainmap->stepNow_2++;
	stepLCDShow_2();
	mainmap->update();
	boxNumCheck_2();

}
void mainwindow::keyRight_2()
{
	int manx = mainmap->man_x_2;

	int many = mainmap->man_y_2;

	if (many + 1>mainmap->mapNow_2[0].size()
		|| mainmap->mapNow_2[manx][many + 1] == DEFINE::WALL)
	{
		return;
	}

	if (mainmap->mapNow_2[manx][many + 1] == DEFINE::GROUND
		|| mainmap->mapNow_2[manx][many + 1] == DEFINE::GOAL)
	{

		++mainmap->man_y_2;
		if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
			|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
			mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
		else
			mainmap->mapNow_2[manx][many] =
			map[mainmap->levelNow][manx][many];
	}

	if (mainmap->mapNow_2[manx][many + 1] == DEFINE::BOX)
	{
		if (many + 2>mainmap->mapNow_2[0].size()
			|| mainmap->mapNow_2[manx][many + 2] == DEFINE::BOX
			|| mainmap->mapNow_2[manx][many + 2] == DEFINE::WALL)
			return;
		if (mainmap->mapNow_2[manx][many + 2] == DEFINE::GROUND)
		{
			if (map[mainmap->levelNow][manx][many + 1] == DEFINE::GOAL)
				boxNum_2--;
			mainmap->mapNow_2[manx][many + 2] = DEFINE::BOX;
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];

			++mainmap->man_y_2;
		}

		if (mainmap->mapNow_2[manx][many + 2] == DEFINE::GOAL)
		{

			if (map[mainmap->levelNow][manx][many + 1] != DEFINE::GOAL)
			{
				boxNum_2++;
			}
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];

			mainmap->mapNow_2[manx][many + 2] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];
			++mainmap->man_y_2;
		}

	}
	mainmap->stepNow_2++;
	stepLCDShow_2();
	mainmap->update();
	boxNumCheck_2();

}
void mainwindow::keyUp_2()
{
	int manx = mainmap->man_x_2;

	int many = mainmap->man_y_2;

	if (manx - 1<0 || mainmap->mapNow_2[manx - 1][many] == DEFINE::WALL)
		return;

	if (mainmap->mapNow_2[manx - 1][many] == DEFINE::GROUND
		|| mainmap->mapNow_2[manx - 1][many] == DEFINE::GOAL)
	{

		--mainmap->man_x_2;
		if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
			|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
			mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
		else
			mainmap->mapNow_2[manx][many] =
			map[mainmap->levelNow][manx][many];
	}

	if (mainmap->mapNow_2[manx - 1][many] == DEFINE::BOX)
	{

		if (manx - 2<0 || mainmap->mapNow_2[manx - 2][many] == DEFINE::BOX
			|| mainmap->mapNow_2[manx - 2][many] == DEFINE::WALL)
			return;
		if (mainmap->mapNow_2[manx - 2][many] == DEFINE::GROUND)
		{
			if (map[mainmap->levelNow][manx - 1][many] == DEFINE::GOAL)
				boxNum_2--;

			mainmap->mapNow_2[manx - 2][many] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];

			--mainmap->man_x_2;
		}

		if (mainmap->mapNow_2[manx - 2][many] == DEFINE::GOAL)
		{

			if (map[mainmap->levelNow][manx - 1][many] != DEFINE::GOAL)
			{
				boxNum_2++;

			}
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];

			mainmap->mapNow_2[manx - 2][many] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx - 1][many];
			--mainmap->man_x_2;
		}

	}
	mainmap->stepNow_2++;
	stepLCDShow_2();
	mainmap->update();
	boxNumCheck_2();

}
void mainwindow::keyDown_2()
{
	int manx = mainmap->man_x_2;

	int many = mainmap->man_y_2;

	if (manx + 1>mainmap->mapNow_2[0].size()
		|| mainmap->mapNow_2[manx + 1][many] == DEFINE::WALL)
	{
		return;
	}

	if (mainmap->mapNow_2[manx + 1][many] == DEFINE::GROUND
		|| mainmap->mapNow_2[manx + 1][many] == DEFINE::GOAL)
	{

		++mainmap->man_x_2;
		if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
			|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
			mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
		else
			mainmap->mapNow_2[manx][many] =
			map[mainmap->levelNow][manx][many];
	}

	if (mainmap->mapNow_2[manx + 1][many] == DEFINE::BOX)
	{
		if (manx + 2>mainmap->mapNow_2[0].size()
			|| mainmap->mapNow_2[manx + 2][many] == DEFINE::BOX
			|| mainmap->mapNow_2[manx + 2][many] == DEFINE::WALL)
		{
			return;
		}
		if (mainmap->mapNow_2[manx + 2][many] == DEFINE::GROUND)
		{
			if (map[mainmap->levelNow][manx + 1][many] == DEFINE::GOAL)
				boxNum_2--;

			mainmap->mapNow_2[manx + 2][many] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];

			++mainmap->man_x_2;
		}

		if (mainmap->mapNow_2[manx + 2][many] == DEFINE::GOAL)
		{

			if (map[mainmap->levelNow][manx + 1][many] != DEFINE::GOAL)
			{
				boxNum_2++;
			}
			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];

			mainmap->mapNow_2[manx + 2][many] = DEFINE::BOX;

			if (map[mainmap->levelNow][manx][many] == DEFINE::BOX
				|| map[mainmap->levelNow][manx][many] == DEFINE::MAN)
				mainmap->mapNow_2[manx][many] = DEFINE::GROUND;
			else
				mainmap->mapNow_2[manx][many] =
				map[mainmap->levelNow][manx][many];
			++mainmap->man_x_2;
		}

	}
	mainmap->stepNow_2++;
	stepLCDShow_2();
	mainmap->update();
	boxNumCheck_2();

}


void mainwindow::boxNumCheck_1()
{
	qDebug() << box_1[mainmap->levelNow];

	if (boxNum_1 == box_1[mainmap->levelNow])

	{

		endGameAction->setEnabled(false);

		restartGameAction->setEnabled(false);

		restartButton->setEnabled(false);

		if (mainmap->levelNow == map.size())

		{

			QMessageBox::information(this, QStringLiteral("��ϲͨ��")
				, QStringLiteral("��ϲ���1ʤ����")
				, QMessageBox::Ok);

			mainmap->levelNow = 0;

			mainmap->stepNow_1 = 0;

			boxNum_1 = 0;

			levelLCDShow();

			stepLCDShow_1();

			mainmap->BeginOrEnd = 1;

			mainmap->update();

		}

		else

		{

			QMessageBox::information(this
				, QStringLiteral("��ϲ����")
				, QStringLiteral("��ϲ���1��ɱ��أ�������һ��")
				, QMessageBox::Ok);

			startGame(mainmap->levelNow + 1);

		}

	}

}
void mainwindow::boxNumCheck_2()

{
	qDebug() << box_2[mainmap->levelNow];

	if (boxNum_2 == box_2[mainmap->levelNow])

	{

		endGameAction->setEnabled(false);

		restartGameAction->setEnabled(false);

		restartButton->setEnabled(false);

		if (mainmap->levelNow == map.size())

		{

			QMessageBox::information(this
				, QStringLiteral("��ϲͨ��")
				, QStringLiteral("��ϲ���2ͨ�أ�")
				, QMessageBox::Ok);

			mainmap->levelNow = 0;

			mainmap->stepNow_2 = 0;

			boxNum_2 = 0;

			levelLCDShow();

			stepLCDShow_2();

			mainmap->BeginOrEnd = 1;

			mainmap->update();

		}

		else

		{

			QMessageBox::information(this
				, QStringLiteral("��ϲ����")
				, QStringLiteral("��ϲ���2��ɱ��أ�������һ��")
				, QMessageBox::Ok);

			startGame(mainmap->levelNow + 1);

		}

	}

}

void mainwindow::createMap()
{
	QFile file(":/image/images/Map.txt");
	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "file open fail.";
	}
	QTextStream in(&file);
	int N = 0;
	in >> N;
	map.resize(N);
	box_1.assign(N, 0);
	box_2.assign(N, 0);
	int row = 0, col = 0;
	for (int i = 0; i < N; ++i)
	{
		in >> row >> col;
		map[i].resize(row);
		for (int j = 0; j < row; ++j)
			map[i][j].resize(col);

		for (int j = 0; j < row; ++j)
		{
			for (int k = 0; k < col; ++k)
			{
				in >> map[i][j][k];
				if (map[i][j][k] == DEFINE::BOX)
				{
					++box_1[i];
					++box_2[i];
				}
			}
		}
	}
	qDebug() << "map size" << map.size();
}
