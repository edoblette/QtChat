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
#ifndef PRIVATEMESSAGETAB_H
#define PRIVATEMESSAGETAB_H

#include <QWidget>
#include <QString>
#include <QObject>

class EventHandler;
namespace Ui {
class PrivateMessageTab;
}

class PrivateMessageTab : public QWidget
{
    Q_OBJECT

    public:
        explicit PrivateMessageTab(QWidget *parent = nullptr);
        ~PrivateMessageTab();
        void NewTab(std::string);
        //getter
        std::string get_nameByIndex(int index){
            return _destName[index];
        }
        bool is_registed(std::string name){
            if(std::find(_destName.begin(), _destName.end(), name) != _destName.end())
               return 1;
            else
               return 0;
        }
        int position(std::string name){
            std::vector<std::string>::iterator it = std::find (_destName.begin(), _destName.end(), name);
            if (it != _destName.end())
                return( it - _destName.begin() + 1) ;
            else
                return -1;
       }
        //setter

        void set_addrEvent(EventHandler * eventHandler){
               pEventHandler = eventHandler;
        }

    private:
        Ui::PrivateMessageTab *ui;
        std::vector<std::string> _destName;
        EventHandler * pEventHandler;

};

#endif // PRIVATEMESSAGETAB_H
