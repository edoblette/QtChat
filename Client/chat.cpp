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

#include "ui_chat.h"
#include "eventshandler.hpp"
// ne pas remplir name, si chat public
chat::chat(QWidget *parent, EventHandler * addrEventHandler, std::string name ) :
    QWidget(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    qRegisterMetaType<QTextCursor>("\n");
    pcEventHandler = addrEventHandler;
    pcEventHandler->set_chat(this, name);
    _destName = name;
}

chat::~chat()
{
    delete ui;
}

void chat::displayMsg(std::string message){
    std::cout << message << std::endl;
    QString const qmessage =  QString::fromStdString(message);
    ui->ui_messageStream->append(qmessage);
}


void chat::on_ui_messageSend_clicked()
{
    std::string message = ui->ui_messageEdit->text().toStdString();
    if(!message.empty()){
        ui->ui_messageEdit->clear();
        if (!_destName.empty()){ // Message prive
            std::cout << "message prive" << std::endl;
            pcEventHandler->SendingMessage("PRV " + _destName + " " + message);
            displayMsg("Vous : " + message);
        }
        /* Pas implemente ici dans cette version
        else {                  // Message public
             std::cout << "message public" << std::endl;
            pcEventHandler->SendingMessage("MSG " + message);
        }
        */
    }

}
