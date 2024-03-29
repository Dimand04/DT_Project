#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <qdebug.h>
#include "global.h"
#include <QProcess>
#include <QDebug>

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



void MainMenu::showAutorization()
{
    m_PlayerID.clear();

    // if(!m_currentFrame.isEmpty())
    // {
    //     toggleFrame(false, m_currentFrame);
    // }

    // if(!ui->Autorization->isVisible())
    // {
    //     ui->Autorization->setVisible(true);
    //     ui->lineEdit_Login->setFocus();
    // }

    connect(ui->PB_AEnter, &QPushButton::clicked, this, &MainMenu::tryAutorization);
}



void MainMenu::tryAutorization()
{
    if(ui->lineEdit_Login->text().remove(" ").length() > 0 && ui->lineEdit_Password->text().remove(" ").length() > 0)
    {
        db = QSqlDatabase::database("main");
        if(getDBConnection(db))
        {
            QSqlQuery query(db);
            query.prepare("select id from player inner join authorization on player.id = authorization.id_player where player.player_name = ? and authorization.password = ?;");
            query.addBindValue(ui->lineEdit_Login->text());
            query.addBindValue(ui->lineEdit_Password->text());
            query.exec();
            if(query.next())
            {
                m_PlayerID = query.value(0).toString();
                ui->lineEdit_Login->clear();
                ui->lineEdit_Password->clear();
                disconnect(ui->PB_AEnter, &QPushButton::clicked, this, &MainMenu::tryAutorization);
                ui->Autorization->setVisible(false);
                ui->frame_main->setEnabled(true);
                showMainMenu();
            }
            else
            {
                QList<QMessageBox::Button> buttons;
                buttons.append(QMessageBox::Ok);
                buttons.append(QMessageBox::Cancel);
                if(showMessage("There is no any players with this registration data.\nYou want to create a new account?\nY/N", "Confirm choice", buttons, QMessageBox::Question) == QMessageBox::Ok)
                { //  QList<QMessageBox::Button>buttons={QMessageBox::Ok};
                    //showMessage("robit vashe Ok","ultraMegaHorosh",QMessageBox::Information,buttons);
                    query.prepare("insert into player (player_name, registration) values (?, ?);");
                    query.addBindValue(ui->lineEdit_Login->text());
                    query.addBindValue(QDate::currentDate().toString("yyyy-MM-dd"));
                    if(query.exec())
                    {
                        query.exec("select max(id) from player;");
                        if(query.next())
                        {
                            m_PlayerID = query.value(0).toString();
                            query.prepare("insert into authorization (id_player, password) values (?, ?);");
                            query.addBindValue(m_PlayerID);
                            query.addBindValue(ui->lineEdit_Password->text());
                            if(query.exec())
                            {
                                ui->lineEdit_Login->clear();
                                ui->lineEdit_Password->clear();
                                disconnect(ui->PB_AEnter, &QPushButton::clicked, this, &MainMenu::tryAutorization);
                                ui->Autorization->setVisible(false);
                                ui->frame_main->setEnabled(true);
                                showMainMenu();
                            }
                            else
                            {
                                showMessage("Something went wrong while creating new account.\nWe're sorry, please, try again later.", "Unexpected error", QMessageBox::Button::Ok, QMessageBox::Question);
                                ui->lineEdit_Login->clear();
                                ui->lineEdit_Password->clear();
                                ui->lineEdit_Login->setFocus();
                            }
                        }
                        else
                        {
                            showMessage("Something went wrong while creating new account.\nWe're sorry, please, try again later.", "Unexpected error", QMessageBox::Button::Ok, QMessageBox::Question);
                            ui->lineEdit_Login->clear();
                            ui->lineEdit_Password->clear();
                            ui->lineEdit_Login->setFocus();
                        }
                    }
                    else
                    {
                        showMessage("Something went wrong while creating new account.\nWe're sorry, please, try again later.", "Unexpected error", QMessageBox::Button::Ok, QMessageBox::Question);
                        ui->lineEdit_Login->clear();
                        ui->lineEdit_Password->clear();
                        ui->lineEdit_Login->setFocus();
                    }
                }
                else
                {
                    ui->lineEdit_Password->clear();
                    ui->lineEdit_Password->setFocus();
                }
            }
        }
    }
}
