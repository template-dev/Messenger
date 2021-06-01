#include "authandregistration.h"
#include "ui_authandregistration.h"
#include "mainwindow.h"

#include <QDesktopWidget>
#include <QPainter>
#include <qdesktopwidget.h>
#include <QMouseEvent>
#include <QMessageBox>

authAndRegistration::authAndRegistration(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::authAndRegistration)
{
  ui->setupUi(this);

  this->setWindowFlags(Qt::FramelessWindowHint);

  client = new ClientStuff("localhost", 6547);
  bl = new BusinessLogic(client);
  //setStatus(client->getStatus());
  //connect(bl,&BusinessLogic::HasData,this,&authAndRegistration::HasDataHandler);
  //connect(client, &ClientStuff::hasReadSome, this, &authAndRegistration::receivedSomething);
  //connect(client, &ClientStuff::statusChanged, this, &authAndRegistration::setStatus);
  // FIXME change this connection to the new syntax
  connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(gotError(QAbstractSocket::SocketError)));
}

authAndRegistration::~authAndRegistration()
{
  delete ui;
}
void authAndRegistration::on_signUpBtn_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
  ui->signInBtn->setStyleSheet(""
    "#signInBtn { border: 0; background: 0; padding: 10px 0; color: #dcdcdc; }"
  "");

  ui->signInBtn->setStyleSheet(""
    "#signInBtn:hover { border: 0; background: 0; padding: 10px 0; color: #dcdcdc; background-color: #2F1E54; }"
  "");

  if(ui->stackedWidget->currentIndex() == 1)
  {
    ui->signUpBtn->setStyleSheet(""
      "border: 0;"
      "background: 0;"
      "padding: 10px 0;"
      "color: #dcdcdc;"
      "background-color: #2F1E54;"
    "");
  }
  else
  {
    ui->signUpBtn->setStyleSheet(""
      "border: 0;"
      "background: 0;"
      "padding: 10px 0;"
      "color: #dcdcdc;"
    "");
  }
}

void authAndRegistration::on_signInBtn_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
  ui->signUpBtn->setStyleSheet(""
    "#signUpBtn { border: 0; background: 0; padding: 10px 0; color: #dcdcdc; }"
  "");

  ui->signUpBtn->setStyleSheet(""
    "#signUpBtn:hover { border: 0; background: 0; padding: 10px 0; color: #dcdcdc; background-color: #2F1E54; }"
  "");
  if(ui->stackedWidget->currentIndex() == 0)
  {
    ui->signInBtn->setStyleSheet(""
      "border: 0;"
      "background: 0;"
      "padding: 10px 0;"
      "color: #dcdcdc;"
      "background-color: #2F1E54;"
    "");
  }
  else
  {
    ui->signInBtn->setStyleSheet(""
      "border: 0;"
      "background: 0;"
      "padding: 10px 0;"
      "color: #dcdcdc;"
    "");
  }
}

void authAndRegistration::on_loginBtn_clicked()
{
  //
  if(client->getStatus() == false)
  {
    client->connect2host();

    /* --- */
    /*QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    out << quint16(0) << ui->lineEdit->text();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);*/
    /* --- */

    this->close();
    MainWindow* main = new MainWindow(bl);
    main->show();
  }
}

void authAndRegistration::on_pushButton_clicked()
{
  this->showMinimized();
}

void authAndRegistration::on_closeApp_clicked()
{
  QApplication::exit();
}

void authAndRegistration::on_pushButton_2_clicked()
{
  int width = this->width();
  int height  = this->height();
  QDesktopWidget desktop;
  QRect rect;
  QPoint center;

  if(!this->isMaximized())
  {
    this->setWindowState(Qt::WindowMaximized);
    //this->setFixedSize(this->maximumWidth(), this->maximumHeight());
    ui->pushButton_2->setIcon(QIcon(":/icons/icons/sizeWindow.png"));
    /*int width = this->size().width();
    int height = this->size().height();
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);*/
  }
  else
  {
    rect = desktop.availableGeometry(desktop.primaryScreen());
    center = rect.center();
    center.setX(center.x() - (this->width()/2));
    center.setY(center.y() - (this->height()/2));
    move(center);
    this->move(qApp->desktop()->availableGeometry(this).center() - this->QMainWindow::rect().center());
    ui->pushButton_2->setIcon(QIcon(":/icons/icons/expad-arrows.png"));
    this->setMinimumSize((width * 60) / 100, (height * 62.96) / 100);
    //this->setMinimumSize((this->maximumWidth() * 60) / 100, (this->maximumHeight() * 62.96) / 100);
    //this->setMaximumSize((this->maximumWidth() * 60) / 100, (this->maximumHeight() * 62.96) / 100);

  }
}

void authAndRegistration::mousePressEvent(QMouseEvent *event)
{
    current = event->pos();
}

void authAndRegistration::mouseMoveEvent(QMouseEvent *event)
{
    if(pressed)
    {
        this->move(mapToParent(event->pos() - current));
    }
}

bool authAndRegistration::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->title && event->type() == QEvent::MouseButtonPress)
    {
        current.setX(ui->title->x()+50);
        current.setY(ui->title->y()+70);
        pressed = true;
        return true;
    }
    if (object == ui->title && event->type() == QEvent::MouseButtonRelease)
    {
        pressed = false;
        return true;
    }
    else
        return false;
}

void authAndRegistration::gotError(QAbstractSocket::SocketError err)
{
    //qDebug() << "got error";
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }

    //ui->textEdit_log->append(strError);
    qDebug() << strError;
}

void authAndRegistration::setStatus(bool newStatus)
{
    if(newStatus)
    {
        /*ui->label_status->setText(
                    tr("<font color=\"green\">CONNECTED</font>"));
        ui->pushButton_connect->setVisible(false);
        ui->pushButton_disconnect->setVisible(true);*/
      //QMessageBox msg;
      /*msg.setText("Connected!");
      msg.exec();*/
    }
    else
    {
        /*ui->label_status->setText(
                tr("<font color=\"red\">DISCONNECTED</font>"));
        ui->pushButton_connect->setVisible(true);
        ui->pushButton_disconnect->setVisible(false);*/
      /*QMessageBox msg;
      msg.setText("Disconnected!");
      msg.exec();*/
    }
}

void authAndRegistration::receivedSomething(QString msg)
{
  /*QMessageBox m;
  m.setText(msg);
  m.exec();*/
}

void authAndRegistration::on_loginBtn_2_clicked()
{
  QString username = ui->lineEdit_4->text();
  QString password = ui->lineEdit_5->text();
  client->connect2host();
  bl->CreateNewUser(username, password);
  this->close();
  //disconnect(bl,&BusinessLogic::HasData,this,&authAndRegistration::HasDataHandler);
  MainWindow* main = new MainWindow(bl);
  main->show();
}

void authAndRegistration::HasDataHandler(QString message)
{

}
