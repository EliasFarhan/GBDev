
lcc -Wa-l -c -o samptest.o samptest.c
lcc -Wa-l -Wf-bo2 -c -o music.o music.c
lcc -Wa-l -Wf-bo3 -c -o music2.o music2.c
lcc -Wa-l -Wf-bo4 -c -o music3.o music3.c
lcc -Wa-l -Wf-bo5 -c -o music4.o music4.c
lcc -Wa-l -Wf-bo6 -c -o music5.o music5.c
lcc -Wa-l -Wf-bo7 -c -o music6.o music6.c
rem compiling
lcc -Wl-yt1 -Wl-yo8 -Wl-yp0x143=0x80 -o Wave_Player.gb samptest.o music.o music2.o music3.o music4.o music5.o music6.o
del *.o
del *.lst
del *.map
echo All done.