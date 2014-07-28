CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= main.gb


all:	kwakwa.o title_screen.o kwakwa_screen.o main.o title.o game_screen.o $(BINS) 

%.o:	%.c
	$(CC) -c -o $@ $<

main.gb:
	$(CC) -Wl-yt3 -Wl-yo8 -Wl-ya4 -o main.gb main.o game_screen.o title.o title_screen.o kwakwa_screen.o kwakwa.o

kwakwa.o:
	/opt/gbdk/bin/lcc -Wa-l -Wf-bo3 -c -o kwakwa.o data/kwakwa.s

title.o:
	/opt/gbdk/bin/lcc -Wa-l -Wf-bo3 -c -o title.o data/title.s

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm
