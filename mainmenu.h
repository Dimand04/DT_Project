#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QProcess>

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



private:
    Ui::MainMenu *ui;
    QProcess *test;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main");
    QString currentIDPlayer;

};
#endif // MAINMENU_H
