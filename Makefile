CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= main.gb

SOURCE = kwakwa.o title_screen.o kwakwa_screen.o main.o title.o game_screen.o music_output.o\
	 gbt_player.o gbt_player_bank1.o sound.o physics.o

all:	$(SOURCE) $(BINS) 

%.o:	%.c
	$(CC) -c -o $@ $<

main.gb:
	$(CC) -Wl-yt2 -Wl-yo8 -Wl-ya4 -o $(BINS) $(SOURCE)

kwakwa.o:
	$(CC) -Wa-l -Wf-bo3 -c -o kwakwa.o data/kwakwa_logo.s

title.o:
	$(CC) -Wa-l -Wf-bo3 -c -o title.o data/title.s

gbt_player.o:
	$(CC) -Wa-l -Wl-m -Wl-j -c -o gbt_player.o gbt_player.s
	
gbt_player_bank1.o:
	$(CC) -Wa-l -Wl-m -Wl-j -c -o gbt_player_bank1.o gbt_player_bank1.s
	
music_output.o:
	$(CC) -Wa-l -Wf-bo2 -c -o music_output.o music_output.c
	
music_output.c:
	./tools/mod2gbt/mod2gbt data/template.mod song -c 2

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm
