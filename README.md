# FlowSniffer
My Experiment for University Work, anyway, is a rough project, but it may help you.

### My Config
1. Operation System: Ubuntu 22.04 as an attacker, Kali/Win11 as a target

2. IDE: QT 5.12.12

3. programming language: C, C++, bash

### Please see the following things:
1. You need two virtual machines on your PC, in my config: they are Ubuntu 22.04 and Kali the latest one (I forgot, sorry, but never mind)

2. You need QT 5.12.12 or higher on your attack host and set the target host can receive the arp reply without requesting it.

3. You need some C or C++ basic knowledge about libpcap library and socket.

4. You need to install servers on your virtual machines before running the application. Ubuntu--vsftpd Kali--apache

5. You need bash knowledge to use the function of sniffing because I use the bash scripts to make C and QT suitable.

There may have some Chinese words because I use English and Chinese at the same time, but you can search for them.

Or you can go to the website to see more details: https://blog.csdn.net/daxuanzi515?spm=1011.2266.3001.5343

### Function Design
1. Sniffer part: almost of this part is made by codes which called ipdump_source.c. How I use it in QT with signal.h? My answer is the bash file behind. They are in the Building folder.
2. Attack part: they are written in C++ and use the socket and libpcap. With the notes in the codes, I hope it is clear now. This part includes arp attack and syn flood attack. The Arp attack, includes two different methods, one is through the fake ip and real mac to pretend the attacker is the net gateway, so the target can not receive the data immediately, just like it disconnected the network. Another is through sending flood fake ip and mac to the target, and its arp cache maybe overflow so that it cannot connect to the network. In the Syn part, you must install a server on your target if not the attack is useless. The syn attack will make the target spend much of the resource because the attacker uses fake ip and port to send the syn signal to it and it is impossible to receive the ack and syn from the target. So the target still sends these messages, which takes part in many resources in the CPU.
3. Log and table: they are UI or Log.
4. ???
