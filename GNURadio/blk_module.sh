#!/bin/bash
#Yann Label 
#Samedi 14 Novembre
#Obj : inhiber le module tnt pour utilisation de dongle usb via gnu radio

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
cd ../
fi
echo "finished"
