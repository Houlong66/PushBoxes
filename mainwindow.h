#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mappaint.h"
#include <QtWidgets/QMainWindow>
#include "ui_Sokoban.h"
#include <QLabel>
#include <QLCDNumber>
#include "define.h"
#include <QPushButton>
#include<vector>
#include<define.h>
using namespace std;
class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = 0);
	~mainwindow();

	//*******************�˵���************************

	QMenu *gameMenu;
	QMenu *gatesMenu;
	QMenu *helpMenu;
	QAction *startGameActionForOne;
	QAction *startGameActionForTwo;
	QAction *restartGameAction;
	QAction *endGameAction;
	QAction *previousGatesAction;
	QAction *nextGatesAction;
	QAction *customGatesAction;
	QAction *aboutAction;
	void createMenu();
	void createAction();

	//******************�������*************************

	std::vector<int> box_1;
	int boxNum_1;
	std::vector<int> box_2;
	int boxNum_2;
	int chooseNum;
	std::vector<std::vector<std::vector<int> > > map;
	void createMap();
	void findManPos(int x, int& man_x, int& man_y);

	//******************���沼��****************************

	QWidget *widget;
	mappaint *mainmap;
	QLabel *levelLabel;
	QLabel *stepLabel_1;
	QLabel *stepLabel_2;
	QLCDNumber *levelLCD;
	QLCDNumber *stepLCD_1;
	QLCDNumber *stepLCD_2;
	QPushButton *restartButton;
	QPushButton *restartButton_1;
	QPushButton *restartButton_2;

	//*************��Ϸ����**********************

	void keyPressEvent(QKeyEvent *e);
	void keyUp_1();
	void keyLeft_1();
	void keyRight_1();
	void keyDown_1();
	void boxNumCheck_1();
	void keyUp_2();
	void keyLeft_2();
	void keyRight_2();
	void keyDown_2();
	void boxNumCheck_2();
	void startGame(int x);

public slots:

	//******************�˵���������**********************

	void startGameSlotForOne();
	void startGameSlotForTwo();
	void restartGameSlot();
	void restartGameSlot_1();
	void restartGameSlot_2();
	void endGameSlot();
	void previousGatesSlot();
	void nextGatesSlot();
	void customGatesSlot();
	void aboutSlot();
	void levelLCDShow();//�ؿ���ʾ
	void stepLCDShow_1();//������ʾ
	void stepLCDShow_2();//������ʾ
private:
	Ui::QpushBoxClass ui;

};
#endif // MAINWINDOW_H
