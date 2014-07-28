/* 
   High Score functions v1.0
   Shen Mansell  
   email: shenmansell@hotmail.com
   http://shen.mansell.tripod.com
*/

/* loads a set of highscores into memory 
   where x is the highscore set 
   (eg set 0 is for hard level, 1 is for easy or whatever) 
*/
void load_hiscore ( UBYTE x);

/* Saves a set of highscores to memory */
void save_hiscore ( UBYTE x);

/* adds a new score to the highscore table if it is good enough
   prompts the player for their name
*/
UBYTE add_new_score (unsigned long int);

/*  Show the high scores */
void show_scores (UBYTE row);

void wait_for_start (void);

