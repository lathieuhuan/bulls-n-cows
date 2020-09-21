#include"game_lib.h"

void Print_Rule()
{
	printf("\n\nRule:");
	printf("\n\t1. You will guess a random number which includes");
	printf(" from 3 to 5 different digits ranging from 0 to 9.");
	printf("\n\n\t2. Every time you guess wrong, we give you two hints:");
	printf("\n\n\t   a. For each right digit in the right position,");
	printf(" you get one Bull.");
	printf("\n\n\t   b. For each right digit in the wrong position,");
	printf(" you get one Cow.");
	printf("\n\n\t3. You win if you guess it right");
	printf(" within %d tries.\n\n", MAX_TRIES);
	system("pause");
}

void Main_Menu()
{
	char Choice[10];
	while (true)
	{
		system("cls");
		printf("\n==================================\n");
		printf("\n\t\tMENU\n");
		printf("\n\t1. New Game");
		printf("\n\t2. Rule");
		printf("\n\t3. Scoreboard");
		printf("\n\t0. Exit");

		rewind(stdin);
		printf("\n\nEnter your choice: ");
		gets(Choice);
		if (!_stricmp(Choice, "1"))
		{
			Difficulty_Menu();
		}
		else if (!_stricmp(Choice, "2"))
		{
			system("cls");
			Print_Rule();
		}
		else if (!_stricmp(Choice, "3"))
		{
			Print_Scoreboard();
		}
		else if (!_stricmp(Choice, "0"))
		{
			break;
		}
		else
		{
			printf("\nYour choice does not exist. Please choose again. ");
			system("pause");
		}
	}
}

void Difficulty_Menu()
{
	char Level[10];
	do
	{
		system("cls");
		printf("\n==================================================\n");
		printf("\n\t\tDIFFICULTY LEVEL\n");
		printf("\n\t1. Easy  : guess 3-digit number");
		printf("\n\t2. Normal: guess 4-digit nunber");
		printf("\n\t3. Hard  : guess 5-digit number");
		printf("\n\t0. Exit");

		rewind(stdin);
		printf("\n\nChoose your level: ");
		gets(Level);
		if (_stricmp(Level, "0") && _stricmp(Level, "1") &&
			_stricmp(Level, "2") && _stricmp(Level, "3"))
		{
			printf("\nYour choice does not exist. Please choose again. ");
			system("pause");
		}
	} while (_stricmp(Level, "0") && _stricmp(Level, "1") &&
			 _stricmp(Level, "2") && _stricmp(Level, "3"));
	if (!_stricmp(Level, "1"))
	{
		Game_Process(3);
	}
	else if (!_stricmp(Level, "2"))
	{
		Game_Process(4);
	}
	else if (!_stricmp(Level, "3"))
	{
		Game_Process(5);
	}
	else
	{
		// function ends
	}
}

void Game_Process(int Digits)
{
	char Target_Number[6];
	char Guess_Number[20];
	int Bulls, Cows;
	int Tries = 1;
	system("cls");
	Generate_Target_Number(Target_Number, Digits);
	do
	{
		if (Enter_Guess_Number(Guess_Number, Target_Number, Digits, Tries))
		{
			Compare_2_Numbers(Guess_Number, Target_Number, &Bulls, &Cows, Digits);
			Result(Bulls, Cows, Digits, Tries, Target_Number);
			Tries++;
		}
		else
			break;
	} while (Bulls != Digits && Tries <= MAX_TRIES);
}

void Generate_Target_Number(char Target_Number[], int Digits)
{
	srand(time(0));
	for (int i = 0; i < Digits; i++)
	{
		Target_Number[i] = (rand() % 9) + 48;
		if (i > 0)
		{
			for (int j = 0; j < i; j++)
			{
				if (Target_Number[i] == Target_Number[j])
				{
					i--;
					break;
				}
			}
		}
	}
	Target_Number[Digits] = '\0';
	printf("\nA random %d-digit number has been generated.", Digits);
	printf(" You win if you guess it right within %d tries.", MAX_TRIES);
	printf("\n\n\tType 'Esc' to quit. Type 'Give up' to see the number.");
	printf("%s", Target_Number);
}

bool Enter_Guess_Number(char Guess_Number[], char Target_Number[], int Digits, int Tries)
{
	do
	{
		rewind(stdin);
		printf("\n\n(%d) Enter your guess: ", Tries);
		gets(Guess_Number);
		if (!_stricmp(Guess_Number, "Esc"))
		{
			return false;
		}
		else if (!_stricmp(Guess_Number, "Give up"))
		{
			printf("\n\t\tThe number is: %s. ", Target_Number);
			system("pause");
			return false;
		}
	} while (!Check_Input(Guess_Number, Digits));
	return true;
}

bool Check_Input(char Guess_Number[], int Digits)
{
	if (strlen(Guess_Number) != Digits)
	{
		printf("\n\tPlease enter a number with %d digits.", Digits);
		return false;
	}
	for (int i = 0; i < Digits; i++)
	{
		if (Guess_Number[i] < 48 || Guess_Number[i] > 57)
		{
			printf("\n\tPlease enter a number.");
			return false;
		}
	}
	for (int i = 0; i < Digits - 1; i++)
	{
		for (int j = i + 1; j < Digits; j++)
		{
			if (Guess_Number[i] == Guess_Number[j])
			{
				printf("\n\tThe number must have different digits.");
				return false;
			}
		}
	}
	return true;
}

void Compare_2_Numbers(char Guess_Number[], char Target_Number[], int* Bulls, int* Cows, int Digits)
{
	*Bulls = 0; *Cows = 0;
	for (int i = 0; i < Digits; i++)
	{
		for (int j = 0; j < Digits; j++)
		{
			if (Guess_Number[i] == Target_Number[j])
			{
				if (i == j)
					(*Bulls)++;
				else
					(*Cows)++;
			}
		}
	}
}

void Result(int Bulls, int Cows, int Digits, int Tries, char Target_Number[])
{
	if (Tries == MAX_TRIES && Bulls != Digits)
	{
		printf("\n\t\tYou're wrong and you have used up your chance!");
		printf("\n\n\t\tThe right number is: %s. ", Target_Number);
		system("pause");
	}
	else if (Bulls == Digits)
	{
		printf("\n\t\tCongratulation! You guess it right! ");
		int Replace_Pos;
		Replace_Pos = STARTING_MEM;
		if (OK_to_Save(Tries, &Replace_Pos, Digits))
		{
			Saving(Tries, Replace_Pos, Digits);
		}
	}
	else
		printf("\n\t\tYou're wrong. You get %d BULLS %d COWS. Guess again!", Bulls, Cows);
}

bool OK_to_Save(int Tries, int* Pos, int Digits)
{
	FILE* fp;
	fopen_s(&fp, "Scores.txt", "r");
	if (fp == NULL)
	{
		fopen_s(&fp, "Scores.txt", "a");
		for (int i = 0; i < TOTAL_RECORDS; i++)
		{
			fprintf(fp, "99 ");
		}
		fclose(fp);
		goto Ask_for_Saving;
	}
	int Max;
	fseek(fp, *Pos * 3, 0);
	fscanf_s(fp, "%d", &Max);
	for (int i = 1; i < N_OF_RECORDS; i++)
	{
		int temp;
		fscanf_s(fp, "%d", &temp);
		if (Max < temp)
		{
			Max = temp;
			*Pos = STARTING_MEM + i;
		}
	}
	fclose(fp);
	if (Tries < Max)
	{
	Ask_for_Saving:
		printf("\n\n\tYour score is exceptional.");
		printf(" Do you want to save your achievement?");
		char Choice[10];
		do
		{
			rewind(stdin);
			printf("\n\n\tType 'Yes' or 'No': ");
			gets(Choice);
			if (!_stricmp(Choice, "No"))
			{
				return false;
			}
			else if (!_stricmp(Choice, "Yes"))
			{
				return true;
			}
			else
			{
				printf("\n\t\tYour choice does not exist. Please type again.");
			}
		} while (_stricmp(Choice, "Yes") && _stricmp(Choice, "No"));
	}
	system("pause");
	return false;
}

void Saving(int Tries, int Pos, int Digits)
{
	char Name[20];
	do
	{
		printf("\n\tEnter your name (max %d characters): ", MAX_NAME_LEN);
		gets(Name);
		if (strlen(Name) > MAX_NAME_LEN)
		{
			printf("\n\t\tYour name is too long. Please choose another one.\n");
		}
	} while (strlen(Name) > MAX_NAME_LEN);

	FILE* fp_name;
	fopen_s(&fp_name, "Names.txt", "r");
	if (fp_name == NULL)
	{
		fopen_s(&fp_name, "Names.txt", "a");
		for (int i = 0; i < TOTAL_RECORDS; i++)
		{
			for (int j = 0; j < MAX_NAME_LEN; j++)
			{
				fprintf(fp_name, "0");
			}
		}
	}
	fclose(fp_name);
	fopen_s(&fp_name, "Names.txt", "r+");
	fseek(fp_name, Pos * MAX_NAME_LEN, 0);
	fprintf(fp_name, "%s", Name);
	if (strlen(Name) < MAX_NAME_LEN)
	{
		for (int i = 0; i < MAX_NAME_LEN - strlen(Name); i++)
		{
			fprintf(fp_name, " ");
		}
	}
	fclose(fp_name);

	FILE* fp_score;
	fopen_s(&fp_score, "Scores.txt", "r+");
	fseek(fp_score, Pos * 3, 0);
	fprintf(fp_score, "%-3d", Tries);
	fclose(fp_score);

	Print_Scoreboard();
}

int Print_Scoreboard()
{
	struct Record
	{
		char Name[MAX_NAME_LEN + 1];
		int Score;
	} List[N_OF_RECORDS];

	FILE* fp_name;
	FILE* fp_score;
	fopen_s(&fp_name, "Names.txt", "r");
	if (fp_name == NULL)
	{
		printf("\n\tNo Scoreboard found! ");
		system("pause");
		return 0;
	}
	fopen_s(&fp_score, "Scores.txt", "r");
	
	system("cls");
	printf("\n\t\t     SCOREBOARD");
	printf("\n\n\t\t  PLAYER     TRIES");
	for (int i = 0; i < 3; i++)
	{
		for (int i = 0; i < N_OF_RECORDS; i++)
		{
			fgets(&List[i].Name, MAX_NAME_LEN + 1, fp_name);
			fscanf_s(fp_score, "%d", &List[i].Score);
		}
		for (int i = 0; i < N_OF_RECORDS; i++)
		{
			for (int j = i + 1; j < N_OF_RECORDS; j++)
			{
				if (List[i].Score > List[j].Score)
				{
					struct Record temp;
					temp.Score = List[i].Score;
					List[i].Score = List[j].Score;
					List[j].Score = temp.Score;
					strcpy_s(temp.Name, MAX_NAME_LEN + 1, List[i].Name);
					strcpy_s(List[i].Name, MAX_NAME_LEN + 1, List[j].Name);
					strcpy_s(List[j].Name, MAX_NAME_LEN + 1, temp.Name);
				}
			}
		}
		if (i == 0)
		{
			printf("\n\tEasy:");
		}
		else if (i == 1)
		{
			printf("\n\tNormal:");
		}
		else
		{
			printf("\n\tHard:");
		}
		for (int i = 0; i < N_OF_RECORDS; i++)
		{
			if (List[i].Score <= MAX_TRIES)
			{
				printf("\n\t\t  %-10s %3d", List[i].Name, List[i].Score);
			}
		}
	}
	fclose(fp_name);
	fclose(fp_score);
	printf("\n\n\t");
	system("pause");
	return 0;
}