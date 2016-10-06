CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= SRJailbreak.gb
BONUS =  kwakwa.o kwakwa_screen.o data/press_start.o title_screen.o title.o 
SOURCE =  main.o box_collision.o sound.o game_screen.o physics.o gbt_player.o gbt_player_bank1.o
ASSETS = data/peanut.o data/guard.o data/environment.o data/background.o data/whale_poster.o data/white_fur.o data/seagull.o music_output.o
LVLS = levels/level1.o levels/level2.o levels/level3.o levels/level4.o levels/level5.o levels/level6.o

all:	  $(LVLS) $(SOURCE) $(ASSETS) $(BONUS) $(BINS) 

levels/%.o:	levels/%.c
	$(CC) -Wa-l -Wf-bo6 -c -o $@ $<
%.o:	%.c
	$(CC) -c -o $@ $<


SRJailbreak.gb:
	$(CC) -Wl-yt2 -Wl-yo16 -Wl-ya4 -o $(BINS) $(LVLS) $(SOURCE) $(BONUS) $(ASSETS) 

kwakwa_screen.o: kwakwa_screen.c
	$(CC) -Wa-l -Wf-bo7 -c -o $@ $<

title_screen.o: title_screen.c
	$(CC) -Wa-l -Wf-bo7 -c -o $@ $<

kwakwa.o:
	$(CC) -Wa-l -Wf-bo3 -c -o kwakwa.o data/kwakwa_logo.s

title.o:
	$(CC) -Wa-l -Wf-bo3 -c -o title.o data/title.s

data/press_start.o: data/press_start.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

gbt_player.o: gbt_player.s
	$(CC) -Wa-l -c -o gbt_player.o gbt_player.s

gbt_player_bank1.o: gbt_player_bank1.s
	$(CC) -Wa-l -Wf-bo4 -c -o gbt_player_bank1.o gbt_player_bank1.s
	
music_output.o:  music_output.c
	$(CC) -Wa-l -Wf-bo2 -c -o music_output.o music_output.c

sound.o: sound.c
	$(CC) -Wa-l -c -o $@ $<

physics.o: physics.c
	$(CC) -Wf-bo6 -Wf-ba6 -c -o physics.o physics.c

data/peanut.o: data/peanut.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

data/white_fur.o: data/white_fur.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

data/seagull.o: data/seagull.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<
	
data/guard.o: data/guard.c
	$(CC) -Wa-l -c -o $@ $<
	
data/background.o: data/background.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

data/environment.o: data/environment.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<
	
data/whale_poster.o: data/whale_poster.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

	
music_output.c:
	./tools/mod2gbt/mod2gbt data/template.mod song -c 2

clean:
	rm -f *.o */*.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm
