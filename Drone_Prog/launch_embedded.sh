#!/usr/bin/expect

# To run this script, you will need expect installed on your machine
# For Ubuntu and variants :
#   sudo apt-get install expect
# For the rest : I don't know !

# If you need to edit this, please copy it and do not add your copy to the
# repo as long as it doesn't invalidate this version

spawn telnet 192.168.1.1
#sleep 1
expect "#"
send "ls\r"
expect "#"
send "cd data/video\r"
expect "#"
send "ls\r"
expect "#"
send "./howard_cc.elf\r"
expect "#"
send "ls\r"
expect "#"
send "exit\r"

