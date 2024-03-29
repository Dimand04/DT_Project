#ifndef GLOBAL_H
#define GLOBAL_H
#include <QSqlDatabase>
#include <qmessagebox.h>
#include <QProcess>
#include <QDebug>

bool getDBConnection(QSqlDatabase db);
int showMessage(QString message, QString windowTitle, QMessageBox::Icon, QList<QMessageBox::Button>buttons);
#endif // GLOBAL_H
