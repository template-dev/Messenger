#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clientStuff.h"
#include "businesslogic.h"

#include <QFrame>
#include <QLabel>
#include <QMainWindow>
#include <QDate>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(BusinessLogic *bl,QWidget *parent = nullptr);
  ~MainWindow();

  bool eventFilter(QObject *object, QEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  QPoint current;
  bool pressed;

private slots:
  void on_moreBtn_clicked();

  void on_settingsRightBlockBtn_clicked();

  void on_backBtn_clicked();

  void on_logOutBtn_clicked();

  void on_closeApp_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

  void on_voiceBtn_clicked();

  void on_addBtn_clicked();

  void on_topSettings_clicked();
  void HasDataHandler(QString msg);

private:
  Ui::MainWindow *ui;
  bool leftMenuFlag;
  //ClientStuff *client;
  BusinessLogic *bl;
};
#endif // MAINWINDOW_H
