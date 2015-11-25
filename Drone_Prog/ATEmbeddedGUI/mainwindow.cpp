#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zoneAcceuil = new QWidget;
    zoneCentrale = new QWidget;
    zone = new QWidget;
    this->setWindowTitle("HOWARD the Drone");

    /***********************************************************************
     * Private Attribute
     * *********************************************************************/
    m_acceuil = 0 ;

    /***********************************************************************
     * Private Button
     * *********************************************************************/
    b_haut = new QPushButton("Haut") ;
    b_bas = new QPushButton ("Bas") ;
    b_gauche = new QPushButton ("Gauche") ;
    b_droite = new QPushButton ("Droite") ;
    b_take_off = new QPushButton("Take Off") ;
    b_land = new QPushButton("Land") ;
    b_translate_left = new QPushButton("Translation Gauche");
    b_translate_right = new QPushButton("Translation Droite");
    b_close = new QPushButton("Close Connection") ;
    b_emergency_stop = new QPushButton("EMERGENCY");
    b_start = new QPushButton;
    b_back = new QPushButton("Back");

    /***********************************************************************
     * Private Other Widgets
     * *********************************************************************/
    power_slider = new QSlider;
    power_slider->setTickInterval(100);
    power_slider->setMinimum(0);
    power_slider->setMaximum(100);
    power_slider->setOrientation(Qt::Horizontal);

    e_num_times = new QSpinBox() ;
    e_num_times->setMinimum(0);
    e_num_times->setMaximum(100);

    l_image = new QLabel;
    p_image = new QPixmap("/home/yann/projets/QtDATA/ATEmbeddedGUI/wolowitz.jpg") ;
    l_image->setPixmap(*p_image);

    l_img_acceuil = new QLabel;
    p_img_acceuil = new QPixmap("/home/yann/projets/QtDATA/ATEmbeddedGUI/acceuil_bbt.jpg") ;
    l_img_acceuil->setPixmap(*p_img_acceuil);
    start_icon = new QIcon(*p_img_acceuil) ;
    b_start->setIcon(*start_icon);

    l_background = new QLabel;
    p_background = new QPixmap("/home/yann/projets/QtDATA/ATEmbeddedGUI/bazinga.jpg");
    l_background->setPixmap(*p_background);

    /***********************************************************************
     * Private Layout
     * *********************************************************************/
    layout = new QGridLayout ;
    v_layout = new QVBoxLayout;
    h_layout = new QHBoxLayout;
    f_layout = new QFormLayout;
    acceuil_layout = new QVBoxLayout;
    background_layout = new QGridLayout;


    /***********************************************************************
     * Organisation Layout
     * *********************************************************************/
    layout->addWidget(b_haut,0,1);
    layout->addWidget(b_gauche,1,0);
    layout->addWidget(b_droite,1,2);
    layout->addWidget(b_bas,2,1);
    layout->addWidget(b_take_off,4,1);
    layout->addWidget(b_land,5,1);
    layout->addWidget(b_translate_left,3,0);
    layout->addWidget(b_translate_right,3,2);
    f_layout->addRow("Power Percent : ",power_slider);
    f_layout->addRow("Commande Duration : (X*350ms)",e_num_times);
    h_layout->addWidget(b_close);
    h_layout->addWidget(b_emergency_stop);
    v_layout->addWidget(l_image);
    v_layout->addLayout(layout);
    v_layout->addLayout(f_layout);
    v_layout->addLayout(h_layout);
    v_layout->addWidget(b_back);
    acceuil_layout->addWidget(l_img_acceuil,0,0);
    acceuil_layout->addWidget(b_start,1,0);
    background_layout->addWidget(l_background,0,0);


    /***********************************************************************
     * General Variable __CAREFUL__
     * *********************************************************************/
    gestion_commande = new CommandeGen;
    zoneAcceuil->setLayout(acceuil_layout);
    zoneCentrale->setLayout(v_layout);
    zone->setLayout(background_layout);
    setCentralWidget(zone);
    zoneAcceuil->show();
    /***********************************************************************
     * Private Connect
     * *********************************************************************/
    QObject::connect(b_gauche,SIGNAL(clicked()),this,SLOT(process_gauche())) ;
    QObject::connect(b_droite,SIGNAL(clicked()),this,SLOT(process_droite())) ;
    QObject::connect(b_haut,SIGNAL(clicked()),this,SLOT(process_monter())) ;
    QObject::connect(b_bas,SIGNAL(clicked()),this,SLOT(process_descendre())) ;
    QObject::connect(b_take_off,SIGNAL(clicked()),this,SLOT(process_taking_off())) ;
    QObject::connect(b_land,SIGNAL(clicked()),this,SLOT(process_landing())) ;
    QObject::connect(b_translate_left,SIGNAL(clicked()),this,SLOT(process_trans_left())) ;
    QObject::connect(b_translate_right,SIGNAL(clicked()),this,SLOT(process_trans_right())) ;
    QObject::connect(b_close,SIGNAL(clicked()),this,SLOT(process_close())) ;
    QObject::connect(b_emergency_stop,SIGNAL(clicked()),this,SLOT(process_emerg_stop())) ;
    QObject::connect(b_start,SIGNAL(clicked()),this,SLOT(process_layout())) ;
    QObject::connect(b_back,SIGNAL(clicked()),this,SLOT(process_layout())) ;

}

void MainWindow::process_gauche(){
    set_m_percent() ;
    set_m_times() ;
    gestion_commande->go_gauche(m_times,m_percent);
}
void MainWindow::process_droite() {
    set_m_percent() ;
    set_m_times() ;
    gestion_commande->go_droite(m_times,m_percent);
}

void MainWindow::process_taking_off(){
    gestion_commande->taking_off() ;
}

void MainWindow::process_landing(){
    gestion_commande->landing();
}

void MainWindow::process_monter() {
    set_m_percent() ;
    set_m_times() ;
    gestion_commande->monter(m_times,m_percent);
}

void MainWindow::process_descendre(){
    set_m_percent() ;
    set_m_times() ;
    gestion_commande->descendre(m_times,m_percent);
}

void MainWindow::process_avancer(){
    set_m_percent() ;
    set_m_times() ;
    gestion_commande->avancer(m_times,m_percent);
}

void MainWindow::process_reculer() {
    set_m_percent() ;
    set_m_times() ;
    gestion_commande->reculer(m_times,m_percent);
}

void MainWindow::process_trans_right(){
    set_m_percent() ;
    set_m_times() ;
    gestion_commande->trans_right(m_times,m_percent);
}

void MainWindow::process_trans_left(){
    set_m_percent() ;
    set_m_times() ;
    gestion_commande->trans_left(m_times,m_percent);
}

void MainWindow::process_emerg_stop() {
    gestion_commande->emerg_stop();
}

void MainWindow::process_no_emerg_stop() {
    gestion_commande->no_emerg_stop();
}

void MainWindow::process_close() {
    gestion_commande->close();
}

int MainWindow::get_power_value(){
    return m_percent ;
}

int MainWindow::get_times_value() {
    return m_times ;
}

void MainWindow::set_m_percent(int percent){
    if(percent==-1)
        m_percent = power_slider->value();
    else
        m_percent = percent ;
}

void MainWindow::set_m_times(int times){
    if(times==-1)
        m_times = e_num_times->value() ;
    else
        m_times = times ;
}

int MainWindow::get_status_value(){
    return m_status ;
}

void MainWindow::process_layout(){

    if(m_acceuil==0){
        zoneCentrale->show();
        zoneAcceuil->setHidden(true);
        m_acceuil=1;
    }else{
        zoneAcceuil->show();
        zoneCentrale->setHidden(true);
        m_acceuil=0;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
