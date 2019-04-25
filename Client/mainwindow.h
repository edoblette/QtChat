/**
    * CLIENT SIDE
    * Projet Reseau
    * @teacher Pablo Rauzy <pr@up8.edu> <https://pablo.rauzy.name/teaching.html#rmpp>
    *
    * @autor Edgar Oblette <edwardoblette@gmail.com>
    * @collegues: Lina Tlemcem
    *             Nourdine ---
    *
    * 21/04/2019
    */
#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTextEdit>
#include <QWidget>

#include <QTextCursor>
#include <QListWidgetItem>

class EventHandler;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    friend class Client;
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void displayMsg(std::string);
        void Talk();
        void closeEvent(QCloseEvent *event);
        void AddClientToList(std::string);
        void RemClientOfList(std::string);
        void signalNewChat(std::string);




        //setter
        void set_addrEvent(EventHandler * eventHandler){
               wEventHandler = eventHandler;
        }

    public slots:
        void on_ui_sendButton_clicked();
        void onClientClicked(QListWidgetItem*);
        void CreateTab(std::string);
        void CreatePrivateMessageTab(std::string);
    signals:
        void CreateNewChat(std::string);

    private:
        Ui::MainWindow *ui;
        EventHandler * wEventHandler;




};

#endif // MAINWINDOW_H
