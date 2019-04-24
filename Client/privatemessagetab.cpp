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
#include "eventshandler.hpp"
#include "ui_privatemessagetab.h"
#include "chat.h"

PrivateMessageTab::PrivateMessageTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrivateMessageTab)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}

PrivateMessageTab::~PrivateMessageTab()
{
    delete ui;
}

void PrivateMessageTab::NewTab(std::string name){
     if(pEventHandler->get_privateMessage()->is_registed(name) == TRUE ){
         ui->tabWidget->setCurrentIndex(pEventHandler->get_privateMessage()->position(name) - 1);
          // marche pas
    }else {
        _destName.emplace_back(name);
        ui->tabWidget->addTab(new chat(this, pEventHandler, name), QString::fromStdString(name));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    }


}

