
#!/bin/bash
#auteur Yann LABEL _ le 03.11.2015
#install gnuradio & rtl & osmosdr

#cd
pwd
#création du dossier d'installation
echo "voulez-vous installer les pré-requis? (y/n)"
read rep
if [ "$rep" = "yes" ] || [ "$rep" = "y" ] || [ "$rep" = "Y" ]; then
#if [ "$#" -gt "0" ]; then
echo "mise à jour système"
sudo apt-get update
sudo apt-get upgrade

echo "installation des pre-requis"
##RAJOUTER ICI LES PREREQUIS##
sudo apt-get install cmake
sudo apt-get install make
##fin

fi
#fin de l'install des prérequis

echo "Création du dossier d'installation à : "
mkdir gnuRadio/
cd gnuRadio/
pwd
#fetching gnu radio
echo "fetching gnu radio : 1 hour left"
sudo wget http://www.sbrac.org/files/build-gnuradio && chmod a+x ./build-gnuradio && ./build-gnuradio

#echo "almost done"
#sudo apt-get install rtl-sdr
#echo "barely done _ testing some features..."
#rtl_test -t 2> gnuTestInstall
#cat gnuTestInstall
#echo $?
#echo "continue with svn cgran? (y/N)"
#read rep
#if [ "$rep" = "y" ] || [ "$rep" = "Y" ]; then
#gqrx est peut-être une alternative
#svn co https://www.cgran.org/svn/projects/multimode
#fi
echo "making rtl-sdr.git"
git clone git://git.osmocom.org/rtl-sdr.git
cd rtl-sdr/
mkdir build
cd build
cmake ../
make
sudo make install
sudo ldconfig
cmake ../ -DINSTALL_UDEV_RULES=ON
echo "making gr-osmosdr"
cd ../../
git clone git://git.osmocom.org/gr-osmosdr
cd gr-osmosdr/
mkdir build
cd build
cmake ../
make
sudo make install
sudo ldconfig
echo "some test... almost done"


echo "blacklist rtl module?"
read blk

if [ "$blk" = "y" ] || [ "$blk" = "yes" ] || [ "$blk" = "Y" ]; then
cd /etc/modprobe.d/

sudo echo "#User Blacklist" >> ./blacklist.conf
sudo echo "blacklist dvb_usb_rtl28xxu" >> ./blacklist.conf
sudo echo "blacklist rtl2832" >> ./blacklist.conf
sudo echo "blacklist rtl2830" >> ./blacklist.conf
echo "testing rtl"
rtl_test -t
cd

else
echo "bloquage temporaire de rtl nécessaire. En cours..."
sudo rmmod dvb_usb_rtl28xxu rtl2832
cd ../../
fi
echo "finished"
echo "lancement de Rtone.grc"
gnome-open ./Rtone.grc
