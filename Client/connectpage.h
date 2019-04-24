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
#ifndef CONNECTPAGE_H
#define CONNECTPAGE_H

#include <QDialog>
#include <iostream>
namespace Ui {
class ConnectPage;
}

class EventHandler;
class ConnectPage : public QDialog
{
    friend class EventHandler;
    Q_OBJECT

    public:
        explicit ConnectPage(QWidget *parent = nullptr );
        ~ConnectPage();

    //setter
    void set_addrEvent(EventHandler * eventHandler){
           cEventHandler = eventHandler;
    }

private slots:
    void on_pushButton_clicked();

private:
        Ui::ConnectPage *ui;
        EventHandler * cEventHandler;


protected:
        std::string _host ;
        int _port;
        std::string _name;

};

#endif // CONNECTPAGE_H
