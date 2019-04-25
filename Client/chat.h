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
#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTextCursor>
#include <QPlainTextEdit>
class EventHandler;
namespace Ui {
class chat;
}

class chat : public QWidget
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr,  EventHandler * addrEventHandler = nullptr, std::string name = "");
    void displayMsg(std::string);
    ~chat();

private slots:
    void on_ui_messageSend_clicked();

private:
    Ui::chat *ui;
    std::string _destName;
    EventHandler * pcEventHandler; //privatechat
};

#endif // CHAT_H
