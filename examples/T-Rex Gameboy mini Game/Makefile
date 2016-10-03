CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= chrome.gb

SOURCE = background.o chrome.o portada.o portadamap.o sonido.o sprites.o

all:	$(SOURCE) $(BINS) 

%.o:	%.c
	$(CC) -c -o $@ $<

chrome.gb:
	$(CC) -Wl-yt2 -Wl-yo8 -Wl-ya4 -o $(BINS) $(SOURCE)



clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm
