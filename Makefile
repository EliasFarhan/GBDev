CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= EGJ2022.gb
BONUS =  data/egj2022/title_screen_gb.o data/egj2022/toni_screen.o data/egj2022/wuthrer_screen.o data/egj2022/box_close_screen.o data/egj2022/caro_screen.o data/egj2022/choice_screen.o data/egj2022/game_over_screen.o data/egj2022/box_open.o
SOURCE =  src/main.o src/title_screen.o src/game_screen.o src/gbt_player.o src/gbt_player_bank1.o
ASSETS = data/egj2022/alphabet.o data/egj2022/text.o data/egj2022/arrow.o data/egj2022/music_output.o 
LVLS = 

all:	  $(LVLS) $(SOURCE) $(ASSETS) $(BONUS) $(BINS)

EGJ2022.gb:
	$(CC) -Wl-yt1 -Wl-yo8 -Wl-ya0 -o $(BINS) $(LVLS) $(SOURCE) $(BONUS) $(ASSETS)


levels/%.o:	levels/%.c
	$(CC) -Wa-l -Wf-bo6 -c -o $@ $<

data/map/%.o: data/map/%.c
	$(CC) -Wa-l -Wf-bo6 -c -o $@ $<

%.o:	%.c
	$(CC) -c -o $@ $<

src/game_screen.o: src/game_screen.c
	$(CC) -Wa-l -c -o $@ $<


src/credits.o: src/credits.c
	$(CC) -Wa-l -Wf-bo7 -c -o $@ $<

src/kwakwa_screen.o: src/kwakwa_screen.c
	$(CC) -Wa-l -Wf-bo7 -c -o $@ $<

src/title_screen.o: src/title_screen.c
	$(CC) -Wa-l -c -o $@ $<

data/egj2022/title_screen_gb.o:
	$(CC) -Wa-l -Wf-bo1 -c -o $@ data/egj2022/title_screen_gb_merge.s

data/egj2022/toni_screen.o:
	$(CC) -Wa-l -Wf-bo1 -c -o $@ data/egj2022/toni_gb_wbox_merge.s

data/egj2022/wuthrer_screen.o:
	$(CC) -Wa-l -Wf-bo1 -c -o $@ data/egj2022/wuthrer_gb_wbox_merge.s
data/egj2022/box_close_screen.o:
	$(CC) -Wa-l -Wf-bo1 -c -o $@ data/egj2022/box_close_gb_wbox_merge.s
data/egj2022/alphabet.o:
	$(CC) -Wa-l -Wf-bo2 -c -o $@ data/egj2022/alphabet.c
data/egj2022/caro_screen.o:
	$(CC) -Wa-l -Wf-bo1 -c -o $@ data/egj2022/caro_gb_wbox_merge.s
data/egj2022/text.o:
	$(CC) -Wa-l -Wf-bo2 -c -o $@ data/egj2022/text.c
data/egj2022/arrow.o:
	$(CC) -Wa-l -Wf-bo2 -c -o $@ data/egj2022/arrow.c
data/egj2022/choice_screen.o:
	$(CC) -Wa-l -Wf-bo1 -c -o $@ data/egj2022/box_close_gb_wchoice_merge.s

data/egj2022/music_output.o:
	$(CC) -Wa-l -Wf-bo5 -c -o $@ data/egj2022/music_output.c
data/title_screen_music.o:
	$(CC) -Wa-l -Wf-bo8 -c -o data/title_screen_music.o data/title_screen_music.c
data/egj2022/game_over_screen.o:
	$(CC) -Wa-l -Wf-bo1 -c -o $@ data/egj2022/game_over_merge.s
data/egj2022/box_open.o:
	$(CC) -Wa-l -Wf-bo2 -c -o $@ data/egj2022/box_open_merge.s
src/gbt_player.o: src/gbt_player.s
	$(CC) -Wa-l -c -o src/gbt_player.o src/gbt_player.s

src/gbt_player_bank1.o: src/gbt_player_bank1.s
	$(CC) -Wa-l -Wf-bo4 -c -o src/gbt_player_bank1.o src/gbt_player_bank1.s

data/music_output.o:  data/music_output.c
	$(CC) -Wa-l -Wf-bo2 -c -o data/music_output.o data/music_output.c

src/sound.o: src/sound.c
	$(CC) -Wa-l -c -o $@ $<


#data/music_output.c:
#	./tools/mod2gbt/mod2gbt data/template.mod song -c 2

clean:
	rm -f *.o */*.o */*/*.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm
