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
#include "ui_connectpage.h"


ConnectPage::ConnectPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectPage)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}

ConnectPage::~ConnectPage()
{
    delete ui;
}

void ConnectPage::on_pushButton_clicked()
{
    bool valid_form = TRUE;

    _host = ui->ui_host->text().toStdString();
    _host.erase(remove( _host.begin(),  _host.end(), ' '),  _host.end());
    if(_host.empty())
        valid_form = FALSE;

    _port = ui->ui_port->text().toInt();
    if((_port <= 0) || (_port >= 9999))
        valid_form = FALSE;

    _name = ui->ui_name->text().toStdString();
    _name.erase(remove( _name.begin(),  _name.end(), ' '),  _name.end());
    if(_name.size() < 2 )
        valid_form = FALSE;

    if(valid_form){
        cEventHandler->ConnectPageSetting(this);
        std::cout<< "localhost:" << _host <<"  port:" << _port << "  name:" << _name << std::endl;
    }else{
         ui->ui_error->setStyleSheet("QLabel { background-color : red; color : white; }");
         ui->ui_error->setText("Verifiez les parametres!");
    }

}
