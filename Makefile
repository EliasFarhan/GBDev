CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= main.gb

SOURCE = kwakwa.o title_screen.o kwakwa_screen.o main.o title.o game_screen.o music_output.o\
	 gbt_player.o gbt_player_bank1.o sound.o data/peanut.o data/guard.o data/environment.o data/background.o
LVLS = levels/level1.c
all:	$(SOURCE) $(BINS) 

%.o:	%.c
	$(CC) -c -o $@ $<

main.gb:
	$(CC) -Wl-yt2 -Wl-yo8 -Wl-ya4 -o $(BINS) $(SOURCE) $(LVLS)

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
	
data/peanut.o: data/peanut.c
	$(CC) -Wa-l -Wf-bo1 -c -o $@ $<
	
data/guard.o: data/guard.c
	$(CC) -Wa-l -Wf-bo1 -c -o $@ $<
	
data/background.o: data/background.c
	$(CC) -Wa-l -Wf-bo1 -c -o $@ $<

data/environment.o: data/environment.c
	$(CC) -Wa-l -Wf-bo1 -c -o $@ $<
	
music_output.c:
	./tools/mod2gbt/mod2gbt data/template.mod song -c 2

clean:
	rm -f *.o */*.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm
