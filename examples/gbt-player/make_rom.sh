../../tools/mod2gbt/mod2gbt template3.mod song -c 2


/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o output.o output.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o gbt_player.o gbt_player.s
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o gbt_player_bank1.o gbt_player_bank1.s


/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wl-yt1 -Wl-yo16 -Wl-ya0 -o test.gb main.o output.o gbt_player.o gbt_player_bank1.o

rm *.o *.lst
