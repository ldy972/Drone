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
    m_mission_end = true ;
    m_navdata_init = false;
    m_wdg_started = false ;

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
    b_mission = new QPushButton("Mission") ;
    b_avant = new QPushButton("Avant") ;
    b_arriere = new QPushButton("Arrière") ;

    /***********************************************************************
     * Private Other Widgets
     * *********************************************************************/
    power_slider = new QSlider;
    power_slider->setTickInterval(100);
    power_slider->setMinimum(0);
    power_slider->setMaximum(100);
    power_slider->setValue(50);
    power_slider->setOrientation(Qt::Horizontal);

    e_num_times = new QSpinBox() ;
    e_num_times->setMinimum(0);
    e_num_times->setMaximum(100);
    e_num_times->setValue(2);

    cb_nav_data = new QCheckBox ;

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

    l_wdg = new QLabel;
    l_wdg->setText(QString::number(0));

    l_nav_altitude = new QLabel;
    l_nav_altitude->setText(QString::number(0));

    l_nav_phi = new QLabel;
    l_nav_phi->setText(QString::number(0));

    l_nav_psi = new QLabel;
    l_nav_psi->setText(QString::number(0));

    l_nav_theta = new QLabel;
    l_nav_theta->setText(QString::number(0));

    l_nav_vx = new QLabel;
    l_nav_vx->setText(QString::number(0));

    l_nav_vy = new QLabel;
    l_nav_vy->setText(QString::number(0));

    l_nav_vz = new QLabel;
    l_nav_vz->setText(QString::number(0));

    /***********************************************************************
     * Private Layout
     * *********************************************************************/
    layout = new QGridLayout ;
    v_layout = new QVBoxLayout;
    h_layout = new QHBoxLayout;
    f_layout = new QFormLayout;
    acceuil_layout = new QVBoxLayout;
    background_layout = new QGridLayout;
    nav_data_layout = new QFormLayout;


    /***********************************************************************
     * Organisation Layout
     * *********************************************************************/
    layout->addWidget(b_haut,4,0);
    layout->addWidget(b_gauche,3,1);
    layout->addWidget(b_droite,3,3);
    layout->addWidget(b_bas,5,0);
    layout->addWidget(b_take_off,4,4);
    layout->addWidget(b_land,5,4);
    layout->addWidget(b_translate_left,1,1);
    layout->addWidget(b_translate_right,1,3);
    layout->addWidget(b_avant,0,2);
    layout->addWidget(b_arriere,2,2);
    f_layout->addRow("Power Percent : ",power_slider);
    f_layout->addRow("Commande Duration : (X*35ms)",e_num_times);
    f_layout->addRow("Nav.Data : ", cb_nav_data);
    h_layout->addWidget(b_close);
    h_layout->addWidget(b_emergency_stop);
    v_layout->addWidget(l_image);
    v_layout->addLayout(layout);
    v_layout->addLayout(f_layout);
    v_layout->addWidget(b_mission);
    v_layout->addLayout(h_layout);
    v_layout->addWidget(b_back);
    acceuil_layout->addWidget(l_img_acceuil,0,0);
    acceuil_layout->addWidget(b_start,1,0);
    background_layout->addWidget(l_background,0,0);
    nav_data_layout->addRow("Altitude : ",l_nav_altitude);
    nav_data_layout->addRow("Phi : ",l_nav_phi);
    nav_data_layout->addRow("Psi : ",l_nav_psi);
    nav_data_layout->addRow("Theta",l_nav_theta);
    nav_data_layout->addRow("vx : ",l_nav_vx);
    nav_data_layout->addRow("vy : ",l_nav_vy);
    nav_data_layout->addRow("vz : ",l_nav_vz);
    background_layout->addLayout(nav_data_layout,1,0);
    background_layout->addWidget(l_wdg,2,1);


    /***********************************************************************
     * General Variable __CAREFUL__
     * *********************************************************************/
    t_gestion_commande = new CommandeGen;
    t_manage_wdg = new Managewdg;
    t_nav_data_receiver = new ReceivNavData;
    zoneAcceuil->setLayout(acceuil_layout);
    zoneCentrale->setLayout(v_layout);
    zone->setLayout(background_layout);
    setCentralWidget(zone);
    zoneAcceuil->show();
    s_navdata=NULL;

    /***********************************************************************
     * Private Connect
     * *********************************************************************/
    QObject::connect(b_start,SIGNAL(clicked()),this,SLOT(process_init()));
    QObject::connect(b_gauche,SIGNAL(clicked()),this,SLOT(process_gauche())) ;
    QObject::connect(b_droite,SIGNAL(clicked()),this,SLOT(process_droite())) ;
    QObject::connect(b_haut,SIGNAL(clicked()),this,SLOT(process_monter())) ;
    QObject::connect(b_bas,SIGNAL(clicked()),this,SLOT(process_descendre())) ;
    QObject::connect(b_take_off,SIGNAL(clicked()),this,SLOT(process_taking_off())) ;
    QObject::connect(b_land,SIGNAL(clicked()),this,SLOT(process_landing())) ;
    QObject::connect(b_translate_left,SIGNAL(clicked()),this,SLOT(process_trans_left())) ;
    QObject::connect(b_translate_right,SIGNAL(clicked()),this,SLOT(process_trans_right())) ;
    QObject::connect(b_avant,SIGNAL(clicked()),this,SLOT(process_avancer())) ;
    QObject::connect(b_arriere,SIGNAL(clicked()),this,SLOT(process_reculer())) ;
    QObject::connect(b_close,SIGNAL(clicked()),this,SLOT(process_close())) ;
    QObject::connect(b_emergency_stop,SIGNAL(clicked()),this,SLOT(process_emerg_stop())) ;
    QObject::connect(b_start,SIGNAL(clicked()),this,SLOT(process_layout())) ;
    QObject::connect(b_back,SIGNAL(clicked()),this,SLOT(process_layout())) ;
    QObject::connect(b_mission,SIGNAL(clicked()),this,SLOT(process_mission())) ;
    QObject::connect(cb_nav_data,SIGNAL(toggled(bool)),this,SLOT(process_nav_data(bool)))  ;
    QObject::connect(t_manage_wdg, SIGNAL(resultReady(int)), this, SLOT(handle_wdg(int)));
    //QObject::connect(t_nav_data_receiver,SIGNAL(copy_nav_data()),this,SLOT(handle_nav_data()));
    QObject::connect(t_gestion_commande,SIGNAL(end_of_mission()),this,SLOT(handle_mission()));
}

/***********************************************************************
 * Process definitions : SLOTS
 * *********************************************************************/

void MainWindow::process_gauche(){
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->go_gauche(m_times,m_percent);
}
void MainWindow::process_droite() {
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->go_droite(m_times,m_percent);
}

void MainWindow::process_taking_off(){
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->taking_off() ;
}

void MainWindow::process_landing(){
    set_m_percent() ;
    set_m_times() ;
   t_gestion_commande->landing();
}

void MainWindow::process_monter() {
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->monter(m_times,m_percent);
}

void MainWindow::process_descendre(){
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->descendre(m_times,m_percent);
}

void MainWindow::process_avancer(){
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->avancer(m_times,m_percent);
}

void MainWindow::process_reculer() {
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->reculer(m_times,m_percent);
}

void MainWindow::process_trans_right(){
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->trans_right(m_times,m_percent);
}

void MainWindow::process_trans_left(){
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->trans_left(m_times,m_percent);
}

void MainWindow::process_emerg_stop() {
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->emerg_stop();
}

void MainWindow::process_no_emerg_stop() {
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->no_emerg_stop();
}

void MainWindow::process_close() {
    set_m_percent() ;
    set_m_times() ;
    t_gestion_commande->close();
    t_nav_data_receiver->close_navdata();
}

void MainWindow::process_nav_data(bool checked){
    if(checked && !m_navdata_init){
        m_navdata_init=true ;
        t_nav_data_receiver->init_navdata();
    }

}

void MainWindow::process_mission(){
    if(m_mission_end){
        set_m_percent();
        set_m_times();
        m_mission_end=false;
        t_gestion_commande->start();
    }
}

void MainWindow::process_init(){
    t_gestion_commande->initialise();
    m_navdata_init=true ;
    t_nav_data_receiver->init_navdata();
    t_nav_data_receiver->start();
    m_wdg_started=true;
    t_manage_wdg->start();
}

/**
 * @brief MainWindow::process_layout
 * gere l'affichage et la fermeture automatique de connection
 * **/
void MainWindow::process_layout(){

    if(m_acceuil==0){
        zoneCentrale->show();
        zoneAcceuil->setHidden(true);
        m_acceuil=1;
    }else{
        zoneAcceuil->show();
        zoneCentrale->setHidden(true);
        t_gestion_commande->close();
        t_nav_data_receiver->close_navdata();
        m_acceuil=0;
    }
}


/************************************************************************
 * Handler
 * **********************************************************************/
void MainWindow::handle_wdg(int value){
    l_wdg->setText(QString::number(value));
    t_manage_wdg->start();
}

void MainWindow::handle_nav_data(){
    t_nav_data_receiver->duplicate_nav_data(s_navdata);
    t_nav_data_receiver->start();
    display_nav_data();
}

void MainWindow::handle_mission(){
    m_mission_end = true;
}

/***********************************************************************
 * Getters & (private) Setters
 * *********************************************************************/
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

void MainWindow::display_nav_data(){
    if(s_navdata!=NULL){
        l_nav_altitude->setNum(s_navdata->nav_data.altitude);
        l_nav_phi->setNum(s_navdata->nav_data.phi);
        l_nav_psi->setNum(s_navdata->nav_data.psi);
        l_nav_theta->setNum(s_navdata->nav_data.theta);

        l_nav_vx->setNum(s_navdata->nav_data.vx);
        l_nav_vy->setNum(s_navdata->nav_data.vy);
        l_nav_vz->setNum(s_navdata->nav_data.vz);
    }
}


/***********************************************************************
 * Destructor
 * *********************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
    t_manage_wdg->quit();
    t_manage_wdg->exit();
    t_nav_data_receiver->quit();
    t_nav_data_receiver->exit();
    t_gestion_commande->quit();
    //t_gestion_commande->emerg_stop();
    t_gestion_commande->wait();
    delete t_manage_wdg;
    delete t_nav_data_receiver;
    delete t_gestion_commande;
}
