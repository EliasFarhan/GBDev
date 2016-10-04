CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= main.gb
BONUS = kwakwa.o title_screen.o kwakwa_screen.o title.o
SOURCE =  main.o  box_collision.o sound.o game_screen.o #music_output.o gbt_player.o gbt_player_bank1.o
ASSETS = data/peanut.o data/guard.o data/environment.o data/background.o data/whale_poster.o
LVLS = levels/level1.o levels/level2.o

all:	  $(LVLS) $(SOURCE) $(ASSETS) $(BINS) 

%.o:	%.c
	$(CC) -c -o $@ $<

main.gb:
	$(CC) -Wl-yt2 -Wl-yo8 -Wl-ya4 -o $(BINS) $(LVLS) $(SOURCE) $(ASSETS)

kwakwa.o:
	$(CC) -Wa-l -Wf-bo3 -c -o kwakwa.o data/kwakwa_logo.s

title.o:
	$(CC) -Wa-l -Wf-bo3 -c -o title.o data/title.s

gbt_player.o:
	$(CC) -Wa-l -Wf-bo5 -c -o gbt_player.o gbt_player.s
	
gbt_player_bank1.o:
	$(CC) -Wa-l -Wf-bo5 -c -o gbt_player_bank1.o gbt_player_bank1.s
	
music_output.o:
	$(CC) -Wa-l -Wf-bo2  -c -o music_output.o music_output.c

levels/level1.o: levels/level1.c
	$(CC) -Wa-l  -c -o $@ $<
	
levels/level2.o: levels/level2.c
	$(CC) -Wa-l -c -o $@ $<

sound.o: sound.c
	$(CC) -Wa-l -c -o $@ $<

data/peanut.o: data/peanut.c
	$(CC) -Wa-l  -c -o $@ $<
	
data/guard.o: data/guard.c
	$(CC) -Wa-l -c -o $@ $<
	
data/background.o: data/background.c
	$(CC) -Wa-l -c -o $@ $<

data/environment.o: data/environment.c
	$(CC) -Wa-l -c -o $@ $<
	
data/whale_poster.o: data/whale_poster.c
	$(CC) -Wa-l -c -o $@ $<
	
music_output.c:
	./tools/mod2gbt/mod2gbt data/template.mod song -c 2

clean:
	rm -f *.o */*.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm
