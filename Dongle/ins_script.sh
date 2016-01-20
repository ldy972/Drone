#!/bin/sh
#insertion de modules de gestion de dongle

insmod dvb-core.ko
insmod dvb-usb.ko
lsmod
