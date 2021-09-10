#include <stdio.h> // standard input output
#include <string.h> // strcmp(,), strcpy(,)
#include <stdlib.h> //srand
#include <time.h> // time(0)
#include <conio.h> //press any key to continue - getch()

//global scope
char name[100];//nama pemain
int min_highscore = 0;
int player_highscore = 0;
int score = 0;
int soal_counter = 0;



struct Soal{//menampung pertanyaan
	char pertanyaan[1000];
	int tf; // true/false (1/2)
};

struct Leaderboard{
	char names[100];
	int highscores;
};


Leaderboard board[7];

void intro(); //logo + nama pemain
void logo(); //print LinkLunk logo
void menu(); //print menu & opsi
void mulai(); //start game
void rule(); // how to play - game rule
void printscore(); //score & high score
void finish();//play again?

void shuffle(int random_index[]);//mengacak urutan soal(index), bubble sort

void leaderboard_read();//baca dan masukkan ke array Leaderboard board global
void leaderboard_check();//cek 
void leaderboard_print();//print
void leaderboard_sort ();//bubble sort
void leaderboard_rewrite();//menulis ulang di file leaderboard



void enter(){
	printf("\n");
}

void clean(){
	system("@clear||cls");
}

void delay(){
	for(int b = 0; b < 200000000; b++){
		;
	}
}

void longdelay(){
	for(int c = 0; c < 1000000000; c++){
		;
	}
}



int main(){
	intro();
					
	return 0;
}



void intro (){
	logo();
	enter();
	
	printf("Welcome to LinkLunk Game!!!\n");
	delay();
	printf("Before we start, please type your name: ");
	scanf("%[^\n]", name);
	
	menu();
	
}


void logo(){
	char art_logo[15][150] = {"\n"};
	FILE *logo = fopen("linklunklogo.txt", "r");
	int count_logo = 0;
	while(fscanf(logo, "%[^\n]\n", &art_logo[count_logo]) != EOF){
		count_logo++;
	}
	
	for(int i = 0; i<count_logo; i++){
		printf(" %s\n", art_logo[i]);
		
	}
	
	fclose(logo);
}


void menu(){
	clean();
	int play;
	
	puts("\t=========================");
	puts("\t|\t MENU \t\t|");
	puts("\t|\t\t\t|");
	puts("\t|1. Play \t\t|");
	puts("\t|2. New Player \t\t|");
	puts("\t|3. How To Play \t|");
	puts("\t|4. Leaderboard \t|");
	puts("\t|5. Exit \t\t|");
	puts("\t-------------------------");


	enter();
	printf("Hello %s, please type a number from the list: ", name);
	scanf("%d", &play);
	
	switch(play){
		case 1:{//play
			clean();
			printf("Ok %s, let's start the game!!\n", name);
			enter();
			mulai();
			break;
		}
		case 2:{//new name/player
			name[0] = '\0';
			printf("New name: ");getchar();
			scanf("%[^\n]", name);
			player_highscore = 0; //reset high score to 0
			delay();
			menu();
			break;
		}
		case 3:{//rule
			rule();
			printf("Press any key to go back to menu\n");
			getch();
			menu();
			break;
		}
		case 4:{//leaderboard
			clean();
			leaderboard_read();
			leaderboard_print();
			enter;
			printf("Press any key to go back to menu\n");
			getch();
			menu();
			break;
		}
		case 5:{//exit
			clean();
			enter();
			logo();
			enter();
			printf("Thank you for playing with us, %s. See you next time.\n", name);
			break;
		}
		default:{
			printf("The number you type is not on the list.\n");
			longdelay();
			menu();
			break;
		}
	}
}


void mulai(){
	Soal soal[25];
	FILE *fp = fopen("soal.txt", "r");
	soal_counter = 0;
	
	
	
	while(fscanf(fp, "%[^#]#%d\n", soal[soal_counter].pertanyaan, &soal[soal_counter].tf) != EOF){
		soal_counter++;
	}
		
	
	printf("The minimun score you need to get into the leaderboard is %d\n", min_highscore);
	printf("Your high score is %d\n", player_highscore);
	delay();
	enter();
			
	int nyawa = 3;
	score = 0;
	int printsoal = 0;
	
	int random[soal_counter];//jumlah soal
	shuffle(random);//mengacak urutan soal dengan index
	
	while(nyawa != 0){ //gameplay
		delay();
		if(printsoal == soal_counter){ //jika pertanyaan habis, break/game selesai
			printf("You've reached the end of this game.\n");
			break;
		}
		
		int jawabanbenar;
		int jawabansalah;
		int jawaban;
		
		printf("statement number %d\n", printsoal+1);
		printf("%s\n", soal[random[printsoal]].pertanyaan);
		delay();
		enter();
		printf("1.True\n");
		printf("2.False\n");
		printf("Answer: ");
		scanf("%d", &jawaban);
				
		
		if(soal[random[printsoal]].tf == 1){
			jawabanbenar = 1;
			jawabansalah = 2;
		}
		else{
			jawabanbenar = 2;
			jawabansalah = 1;
		}
				
		
		while (jawaban != 1 && jawaban != 2){ //jika jawaban yang di input bukan TRUE/FALSE (1/2)
			enter();
			printf("The answer you type is not on the list\n");
			printf("Please re-type your answer: ");
			scanf("%d", &jawaban);
		}
				
				
		if (jawaban == jawabanbenar){
			score += 1;
			printsoal += 1;
			printf("Your answer is correct.\n");
			longdelay();
			clean();
			
		}
		else if(jawaban == jawabansalah){
			score += 0;
			nyawa -= 1;
			printsoal += 1;
			printf("Your answer is wrong.\n");
			printf("You have %d lives now.\n", nyawa);
			longdelay();
			clean();
		}
						
	}
	
	if(player_highscore < score){
		player_highscore = score;
	}
	
	printscore();
	enter();
	finish();
	
		
	fclose(fp);	
}


void rule(){
	clean();
	puts("\t=========================================================================================");
	puts("\t|\t\t\t\t\t HOW TO PLAY \t\t\t\t\t|");
	puts("\t|\t\t\t\t\t\t\t\t\t\t\t|");
	puts("\t|You'll be given a statement, you need to check whether it's true or false. \t\t|");
	puts("\t|To answer, Type '1' for True and '2' for false. \t\t\t\t\t|");
	puts("\t|You have 3 lives to begin with, it will decrease if you type the wrong answer. \t|");
	puts("\t|If your live reaches 0, the game ends. \t\t\t\t\t\t|");
	puts("\t-----------------------------------------------------------------------------------------");	
	
}


void shuffle(int random_index[]){
	srand(time(0));
	for(int i = 0; i < soal_counter; i++){// angka urut dari 0-14, sesuai jumlah soal
		random_index[i] = i;
	}
	
	for(int j = 0; j < soal_counter; j++){//shuffle dengan menggunakan bubble sort dan function random
		int rands = rand()%soal_counter;// angka yang di random tidak melebihi jumlah soal, misal counter: 15 -> 0-14
		int temp = random_index[j];
		random_index[j] = random_index[rands];
		random_index[rands] = temp;
	}
}


void printscore(){
	printf("Your score is %d\n", score);
	printf("your high score is %d\n", player_highscore);
	if (score > min_highscore){
		printf("Congratulations you beat the minimun high score!!\n");
		delay();
	}
	else {
		printf("Unfortunately you didn't beat the minimum high score.\n");
		printf("Minimum high score: %d\n", min_highscore);
		delay();
	}
}


void finish(){
	int yes_no;
	printf("Do you want to play again?\n");
	printf("if yes please type '1', if no type '0'.\n");
	scanf ("%d", &yes_no);
	
	
	while (yes_no != 1 && yes_no != 0){
		printf("That number is not on the list\n");
		printf("Please re-type the correct number: ");
		scanf("%d", &yes_no);
	}	
	
	if(yes_no == 1){
		longdelay();
		clean();
		mulai();
	}
	else{
		leaderboard_check();
		clean();
		enter();
		menu();
		return;
	}
	
}


//leaderboard

void leaderboard_read(){
	FILE *file = fopen ("leaderboard", "r");
	int namescore = 0;
	
	while(fscanf(file, "%[^#]#%d\n", board[namescore].names, &board[namescore].highscores) != EOF){
		namescore += 1;
	}
	
	fclose(file);
	
	min_highscore = board[4].highscores;//global scope minimum highscore leaderboard
	
}


void leaderboard_check(){
//	Leaderboard board[7];
	
	
	strcpy(board[5].names, name);//memasukan nama & high score ke array Leaderboard board
	board[5].highscores = player_highscore; 
	
	
	leaderboard_sort();//dari besar ke kecil
	
	leaderboard_rewrite();//menulis ulang di file leaderboard
	
	
}


void leaderboard_print(){
	printf("\t---------------------------------\n");
	printf("\t|\tTop 5 Leaderboard \t|\n");
	printf("\t---------------------------------\n");

	for (int i = 0; i<5 ; i++){
		printf("\t|%d. %s\t|\t%d\t|\n", i+1, board[i].names, board[i].highscores);
	}
	
	printf("\t---------------------------------\n");
}


void leaderboard_sort (){
	
	Leaderboard temp;
	
	for(int m = 0; m < 5; m++){
		for(int n = 0; n < 5 - m; n++){
			if (board[n].highscores < board[n+1].highscores){
				temp = board[n];
				board[n] = board[n+1];
				board[n+1] = temp;
			}
		}
	}
	
}


void leaderboard_rewrite(){
	FILE *fpp = fopen("leaderboard", "w");
	
	for(int i = 0; i<5; i++){
		fprintf(fpp, "%s#%d\n", board[i].names, board[i].highscores);
	}
	
	fclose(fpp);
}


