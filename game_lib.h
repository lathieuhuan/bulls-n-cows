#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAX_TRIES	7
#define	MAX_NAME_LEN	7 // cannot exceed 10
#define	N_OF_RECORDS	3
#define	TOTAL_RECORDS	(N_OF_RECORDS * 3)
#define	STARTING_MEM	((Digits - 3) * N_OF_RECORDS)

void Main_Menu();
void Print_Rule();
void Difficulty_Menu();
int Print_Scoreboard();

void Game_Process(int Digits);
void Generate_Target_Number(char Target_Number[], int Digits);
bool Enter_Guess_Number(char Guess_Number[], char Target_Number[], int Digits, int Tries);
bool Check_Input(char Guess_Number[], int Digits);
void Compare_2_Numbers(char Guess_Number[], char Target_Number[], int* Bulls, int* Cows, int Digits);
void Result(int Bulls, int Cows, int Digits, int Tries, char Target_Number[]);
bool OK_to_Save(int Tries, int* Pos, int Digits);
void Saving(int Tries, int Pos, int Digits);