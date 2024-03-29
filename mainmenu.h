#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QProcess>
#include <QSqlQuery>
#include <QDate>
#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <QBuffer>
#include <QFileDialog>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
public slots:
    void showMainMenu();
    void showHeroesMenu();
    void showPlayerProfile();
    void showAutorization();
    void tryAutorization();

private:
    Ui::MainMenu *ui;
    QProcess *test;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main");
    QString m_PlayerID,
            m_currentFrame,
            currentIDPlayer;

private:
    void toggleFrame(const int, QString);
    void toggleFrame(bool);
    //void toggleFrame(bool, QString);
    void toggleFrame();
};
#endif // MAINMENU_H
