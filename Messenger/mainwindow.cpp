#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authandregistration.h"

#include <QDateTime>
#include <QException>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QTime>

MainWindow::MainWindow(BusinessLogic *bl,QWidget *parent)
  : QMainWindow(parent),bl(bl)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //ui->moreBtn->setStyleSheet("#moreBtn{ padding: 20px 0; } #moreBtn:hover{ background-color: #363459; }");

  QPixmap pix(":/icons/icons/profile.png");
  int w = ui->iconLabel->width();
  int h = ui->iconLabel->height();
  ui->iconLabel->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

  //this->setWindowFlags(Qt::CustomizeWindowHint);
  this->setWindowFlags(Qt::FramelessWindowHint);
  ui->message->setMaxLength(1300);
  //connect(bl, &BusinessLogic::HasData, this, &MainWindow::HasDataHandler);
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout,bl,&BusinessLogic::PollMessages);
  timer->start(60000);
}

MainWindow::~MainWindow()
{
  delete ui;
}

/*void MainWindow::on_moreBtn_clicked()
{
  if(ui->rightMenuBlock->width() == 0) {
    ui->rightMenuBlock->setMinimumWidth(280);
    ui->rightMenuBlock->setMaximumWidth(280);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->moreBtn->setStyleSheet("#moreBtn{ background-color: #363459; padding: 20px 0; }");
  } else {
    ui->rightMenuBlock->setMinimumWidth(0);
    ui->rightMenuBlock->setMaximumWidth(0);
    ui->moreBtn->setStyleSheet("#moreBtn{ background-color: transparent; padding: 20px 0; } #moreBtn:hover{ background-color: #363459; }");
  }

  if(ui->stackedWidget_2->currentIndex() == 0) {
    ui->backBtn->setVisible(false);
  }

}*/

void MainWindow::on_settingsRightBlockBtn_clicked()
{
  ui->stackedWidget_2->setCurrentIndex(1);
  ui->backBtn->show();
}

void MainWindow::on_backBtn_clicked()
{
  int i = ui->stackedWidget_2->currentIndex();
  if(i > 0) {
    ui->stackedWidget_2->setCurrentIndex(--i);
    if(i == 0) {
      ui->backBtn->setVisible(false);
    }
  }
}

void MainWindow::on_logOutBtn_clicked()
{
  try{
    //client->closeConnection();
    this->close();
    authAndRegistration* auth = new authAndRegistration();
    auth->show();
  }
  catch(const QException& ex)
  {
    qDebug() << ex.what();
  }
  //
}

void MainWindow::on_closeApp_clicked()
{
  //client->closeConnection();
  QApplication::exit();
}

void MainWindow::on_pushButton_2_clicked()
{
  //this->showFullScreen();

  int width = this->width();
  int height  = this->height();
  QDesktopWidget desktop;
  QRect rect;
  QPoint center;


  if(!this->isMaximized())
  {
    this->setWindowState(Qt::WindowMaximized);
    ui->pushButton_2->setIcon(QIcon(":/icons/icons/sizeWindow.png"));
  }
  else
  {
    rect = desktop.availableGeometry(desktop.primaryScreen());
    center = rect.center();
    center.setX(center.x() - (this->width()/2));
    center.setY(center.y() - (this->height()/2));
    move(center);
    ui->pushButton_2->setIcon(QIcon(":/icons/icons/expad-arrows.png"));
    this->QMainWindow::move(qApp->desktop()->availableGeometry(this).center() - this->QMainWindow::rect().center());
    this->activateWindow();
    this->setWindowState(Qt::WindowMinimized);

    //this->setMinimumSize((width * 60) / 100, (height * 62.96) / 100);
    //this->setMinimumSize((this->maximumWidth() * 60) / 100, (this->maximumHeight() * 62.96) / 100);
    //this->setMaximumSize((this->maximumWidth() * 60) / 100, (this->maximumHeight() * 62.96) / 100);
  }
}

void MainWindow::on_pushButton_clicked()
{
  this->showMinimized();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  current = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
  if(pressed)
  {
    this->move(mapToParent(event->pos() - current));
  }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
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

void MainWindow::on_voiceBtn_clicked()
{
  QMessageBox msg;
  if(ui->message->text() != "" && ui->message->maxLength() <= 1300)
  {
    //QString str(ui->message->text().toStdString().c_str());
    QFrame * sendMsgFrame = new QFrame(this);
    sendMsgFrame->setMinimumWidth(0);
    sendMsgFrame->setMaximumWidth(700);
    sendMsgFrame->setStyleSheet("background: transparent;");

    QLabel * sendText = new QLabel (this);
    sendText->setText(ui->message->text());
    sendText->setStyleSheet("background-color: #212121; border-radius: 5px; border-bottom-right-radius: 0; color: #dcdcdc; border: 1px solid #111111; font-size: 15px; padding: 10px;");
    sendText->setScaledContents(true);
    sendText->setFont(QFont("Microsoft YaHei UI"));
    sendText->setMinimumWidth(0);
    sendText->setMaximumWidth(700);
    sendText->setWordWrap(true);
    sendText->setAlignment(Qt::AlignVCenter);

    QLabel * sendPersonImg = new QLabel(this);
    sendPersonImg->setFixedSize(40, 40);
    int w = sendPersonImg->width();
    int h = sendPersonImg->height();
    QPixmap pix(":/icons/icons/user.png");
    sendPersonImg->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    QLabel * dateTime = new QLabel(this);
    //dateTime->setText(QDate::currentDate().toString());
    dateTime->setText(QTime::currentTime().toString());
    dateTime->setStyleSheet("background-color: none; padding: 10px 0;color: #808080; border: 0; font-size: 12px;");
    dateTime->setFont(QFont("Microsoft YaHei UI"));

    QVBoxLayout * txtL = new QVBoxLayout(this);
    txtL->addWidget(sendText);
    txtL->addWidget(dateTime, 0, Qt::AlignRight);

    QGridLayout * sendFormLayout = new QGridLayout(this);
    //sendFormLayout->addWidget(sendText, 0, 0, Qt::AlignRight);
    sendFormLayout->addLayout(txtL, 0, 0, Qt::AlignRight);
    sendFormLayout->addWidget(sendPersonImg, 0, 1, Qt::AlignRight | Qt::AlignTop);
    //sendFormLayout->addWidget(dateTime, 0, 0, Qt::AlignRight | Qt::AlignBottom);
    sendFormLayout->setColumnStretch(0, 1);

    sendMsgFrame->setLayout(sendFormLayout);

    ui->contentFormLayout->setAlignment(Qt::AlignBottom);
    ui->contentFormLayout->addWidget(sendMsgFrame);

    /* --- */
    try {
      QByteArray arrBlock;
      QDataStream out(&arrBlock, QIODevice::WriteOnly);
      //out.setVersion(QDataStream::Qt_5_10);
      QString m = ui->message->text();
      out << quint16(0) << m;

      out.device()->seek(0);
      out << quint16(arrBlock.size() - sizeof(quint16));

      //client->tcpSocket->write(arrBlock);
    }
    catch (const QException& ex) {
      qDebug() << ex.what();
    }
    /* --- */

    ui->message->clear();
  }
  else if (ui->message->maxLength() > 1300)
  {
    msg.setWindowTitle("Failure!");
    msg.setText("The number of characters exceeds the maximum size (1300).");
    msg.exec();
  }
}

void MainWindow::on_addBtn_clicked()
{
  if(ui->searchText->text() != "")
  {
    QFrame * lframe = new QFrame(this);
    lframe->setObjectName("frame");
    lframe->setStyleSheet("#frame { /*background-color: #5E5C8D;*/ color: #dcdcdc; border: 0 solid #3F3D62; margin: 5px 0; }"
                         "#frame:hover { background-color: #5E5C8D; }");
    lframe->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

    QLabel * img = new QLabel(this);
    img->setFixedSize(40, 40);
    int w = img->width();
    int h = img->height();
    QPixmap pix(":/icons/icons/user.png");
    img->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    QLabel * name = new QLabel(this);
    name->setText(ui->searchText->text());
    name->setStyleSheet("color: #D8D9FA; font-size: 14px; margin: 0 10px;");
    name->setFont(QFont("Microsoft YaHei UI"));

    QFormLayout * formLayout = new QFormLayout();

    formLayout->addRow(img, name);
    formLayout->setAlignment(Qt::AlignCenter);

    lframe->setLayout(formLayout);
    ui->formLayout_2->addWidget(lframe);
  }
}
