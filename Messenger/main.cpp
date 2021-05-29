#include "mainwindow.h"
#include "authandregistration.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  //MainWindow w;
  //w.show();

  authAndRegistration auth;
  auth.show();
  return a.exec();
}
