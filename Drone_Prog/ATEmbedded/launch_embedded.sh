#!/usr/bin/expect

# To run this script, you will need expect installed on your machine
# For Ubuntu and variants :
#   sudo apt-get install expect
# For the rest : I don't know !

# Connect to the drone via telnet
spawn telnet 192.168.1.1
#sleep 1
# The telnet prompt is the "#" character.
# When connected, move to /data/video and launch the program
expect "#"
send "cd data/video\r"
expect "#"
send "./howard.elf\r"
