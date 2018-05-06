CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= SRJailbreak.gb
BONUS =  data/kwakwa_logo.o src/kwakwa_screen.o data/press_start.o src/title_screen.o src/title.o src/credits.o data/staffroll.o data/title_screen_music.o
SOURCE =  src/main.o src/box_collision.o src/sound.o src/game_screen.o src/physics.o src/gbt_player.o src/gbt_player_bank1.o
ASSETS = data/peanut.o data/guard.o data/environment.o data/background.o data/whale_poster.o data/white_fur.o data/seagull.o data/music_output.o
LVLS = data/map/level1_map.o data/map/level2_map.o data/map/level3_map.o data/map/level4_map.o data/map/level5_map.o data/map/level6_map.o \
levels/level1.o levels/level2.o levels/level3.o levels/level4.o levels/level5.o levels/level6.o \
data/map/level7_map.o data/map/level8_map.o data/map/level9_map.o data/map/level10_map.o data/map/level11_map.o data/map/level12_map.o data/map/level13_map.o data/map/level14_map.o data/map/level15_map.o

all:	  $(LVLS) $(SOURCE) $(ASSETS) $(BONUS) $(BINS) 

SRJailbreak.gb:
	$(CC) -Wl-yt3 -Wl-yo16 -Wl-ya1 -o $(BINS) $(LVLS) $(SOURCE) $(BONUS) $(ASSETS) 


levels/%.o:	levels/%.c
	$(CC) -Wa-l -Wf-bo6 -c -o $@ $<

data/map/%.o: data/map/%.c
	$(CC) -Wa-l -Wf-bo6 -c -o $@ $<

%.o:	%.c
	$(CC) -c -o $@ $<

src/game_screen.o: src/game_screen.c
	$(CC) -Wa-l -Wf-bo7 -c -o $@ $<


src/credits.o: src/credits.c
	$(CC) -Wa-l -Wf-bo7 -c -o $@ $<
	
src/kwakwa_screen.o: src/kwakwa_screen.c
	$(CC) -Wa-l -Wf-bo7 -c -o $@ $<

src/title_screen.o: src/title_screen.c
	$(CC) -Wa-l -Wf-bo7 -c -o $@ $<
	
data/staffroll.o: data/staffroll.s
	$(CC) -Wa-l -Wf-bo8 -c -o data/staffroll.o data/staffroll.s
data/kwakwa_logo.o:
	$(CC) -Wa-l -Wf-bo3 -c -o data/kwakwa_logo.o data/kwakwa_logo.s

src/title.o:
	$(CC) -Wa-l -Wf-bo3 -c -o src/title.o data/title.s
	
data/title_screen_music.o:
	$(CC) -Wa-l -Wf-bo8 -c -o data/title_screen_music.o data/title_screen_music.c

data/press_start.o: data/press_start.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

src/gbt_player.o: src/gbt_player.s
	$(CC) -Wa-l -c -o src/gbt_player.o src/gbt_player.s

src/gbt_player_bank1.o: src/gbt_player_bank1.s
	$(CC) -Wa-l -Wf-bo4 -c -o src/gbt_player_bank1.o src/gbt_player_bank1.s
	
data/music_output.o:  data/music_output.c
	$(CC) -Wa-l -Wf-bo2 -c -o data/music_output.o data/music_output.c

src/sound.o: src/sound.c
	$(CC) -Wa-l -c -o $@ $<

src/physics.o: src/physics.c
	$(CC) -Wf-bo6 -c -o src/physics.o src/physics.c

data/peanut.o: data/peanut.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

data/white_fur.o: data/white_fur.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

data/seagull.o: data/seagull.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<
	
data/guard.o: data/guard.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<
	
data/background.o: data/background.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

data/environment.o: data/environment.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<
	
data/whale_poster.o: data/whale_poster.s
	$(CC) -Wa-l -Wf-bo5 -c -o $@ $<

	
#data/music_output.c:
#	./tools/mod2gbt/mod2gbt data/template.mod song -c 2

clean:
	rm -f *.o */*.o */*/*.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm
