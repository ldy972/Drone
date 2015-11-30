#ifndef COMMANDEGEN_H
#define COMMANDEGEN_H

#include <QObject>
#include <QThread>
#include "com.h"


class CommandeGen : public QThread
{
    Q_OBJECT
   void run()  Q_DECL_OVERRIDE {
        this->do_mission(1,50);
    }
public:
    CommandeGen();
    int get_status() ;

    void go_gauche(int times, int percent) ;
    void go_droite(int times, int percent) ;

    void taking_off() ;
    void landing() ;

    void monter(int times,int percent) ;
    void descendre(int times,int percent);

    void avancer(int times,int percent) ;
    void reculer(int times,int percent) ;

    void trans_right(int times,int percent) ;
    void trans_left(int times,int percent) ;

    void emerg_stop() ;
    void no_emerg_stop() ;
    void close() ;

    void do_mission(int times,int percent);
    void initialise() ;
signals :
    void end_of_mission();
private:
    int m_status ;
    power_percent_type to_percent(int p) ;
    power_percent_type negate(power_percent_type p) ;
};

#endif // COMMANDEGEN_H
