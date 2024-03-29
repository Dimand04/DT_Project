#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <qdebug.h>
#include "global.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi (this);
    connect (ui->BTN_Heroes,&QPushLabel::clicked,this,&MainMenu::showHeroesMenu);
    connect (ui->LB_OpenMainMenu,&QPushLabel::clicked,this,&MainMenu::showMainMenu);
    connect (ui->PB_PlayerAvatar,&QPushLabel::clicked,this,&MainMenu::showPlayerProfile);
}

MainMenu::~MainMenu()
{
    delete ui;
}
//iugbuyu
void MainMenu::showMainMenu()
{
    ui->frame_profile -> setGeometry (ui-> frame_profile ->x(),721, ui->frame_profile->width(), ui->frame_profile->height ());
    ui->Heroes -> setGeometry (ui-> Heroes ->x(),721, ui->Heroes->width(), ui->Heroes->height ());
    ui->frame_main->setGeometry(ui->frame_main->x(),40,ui->frame_main->width(),ui->frame_main->height());
    ui->Heroes->setEnabled(false);
    ui->frame_main->setEnabled(true);
    ui->frame_profile->setEnabled(false);

    db=QSqlDatabase::database("main");
    if(getDBConnection(db))
    {
        QList<QMessageBox::Button>buttons={QMessageBox::Ok};
        showMessage("robit vashe Ok","ultraMegaHorosh",QMessageBox::Information,buttons);
    }
    else
    {
        QList<QMessageBox::Button>buttons={QMessageBox::Ok};
        showMessage("ne robit","feels badman",QMessageBox::Critical,buttons);
    }
}

void MainMenu::showHeroesMenu()
{
    ui->frame_main -> setGeometry (ui-> frame_main ->x(),721, ui->frame_main->width(), ui->frame_main->height ());
    ui->frame_profile -> setGeometry (ui-> frame_profile ->x(),721, ui->frame_profile->width(), ui->frame_profile->height ());
    ui->Heroes->setGeometry(ui->Heroes->x(),40,ui->Heroes->width(),ui->Heroes->height());
    ui->Heroes->setEnabled(true);
    ui->frame_main->setEnabled(false);
    ui->frame_profile->setEnabled(false);
}

void MainMenu::showPlayerProfile()
{
    ui->frame_main -> setGeometry (ui-> frame_main ->x(),721, ui->frame_main->width(), ui->frame_main->height ());
    ui->Heroes -> setGeometry (ui-> Heroes ->x(),721, ui->Heroes->width(), ui->Heroes->height ());
    ui->frame_profile->setGeometry(ui->frame_profile->x(),40,ui->frame_profile->width(),ui->frame_profile->height());
    ui->Heroes->setEnabled(false);
    ui->frame_main->setEnabled(false);
    ui->frame_profile->setEnabled(true);
}

