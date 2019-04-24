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
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<QTextCursor>("\n");

    this->setFixedSize(this->width(),this->height());
     // bind SIGNAL & SLOT
    connect(ui->ui_userlist , SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onClientClicked(QListWidgetItem*)));
    // bind SIGNAL & SLOT
    connect(this, SIGNAL(CreateNewChat(std::string)), this , SLOT(CreatePrivateMessageTab(std::string)));

}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Tu pars ?", QMessageBox::Yes | QMessageBox::No))
    {

        wEventHandler->Disconnecting();
        event->accept();
    }

}

void MainWindow::displayMsg(std::string message){
    QString const qmessage =  QString::fromStdString(message);
    ui->ui_messageStream->append(qmessage);
}



void MainWindow::on_ui_sendButton_clicked(){
    std::string message = ui->ui_messageEditor->text().toStdString();
    if(!message.empty()){
        ui->ui_messageEditor->clear();
        wEventHandler->SendingMessage("MSG " + message);
    }

}

void MainWindow::onClientClicked(QListWidgetItem* item){
    std::cout << item->text().toStdString() << std::endl;
    // On recupere le nom de l'item
    std::string name = item->text().toStdString();

    // On cree un nouvel element dans le vector PrivateMessage
    CreateTab(name);
}


void MainWindow::CreateTab(std::string name){
    emit CreateNewChat(name);

}

void MainWindow::CreatePrivateMessageTab(std::string new_destName){
   wEventHandler->get_privateMessage()->NewTab(new_destName);
   wEventHandler->get_privateMessage()->show();
}

void MainWindow::AddClientToList(std::string newClient){
    QString const qnewClient =  QString::fromStdString(newClient);
    ui->ui_userlist->addItem(qnewClient);

}

void MainWindow::RemClientOfList(std::string newClient){
    QString const qnewClient =  QString::fromStdString(newClient);
    QList<QListWidgetItem*> items = ui->ui_userlist->findItems(qnewClient, Qt::MatchExactly);
    foreach(QListWidgetItem * item, items)
    {
        delete ui->ui_userlist->takeItem(ui->ui_userlist->row(item));
    }



}


