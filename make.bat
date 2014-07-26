C:\gbdk\bin\lcc -Wa-l -Wf-bo3 -c -o kwakwa.o data/kwakwa.s
C:\gbdk\bin\lcc -Wa-l -Wf-bo4 -c -o title.o data/title.s
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o kwakwa_screen.o kwakwa_screen.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o title_screen.o title_screen.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
C:\gbdk\bin\lcc -Wl-yt3 -Wl-yo8 -Wl-ya4 -o main.gb main.o title_screen.o kwakwa_screen.o title.o kwakwa.o


