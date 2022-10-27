#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ATTEMPTS 15
#define TRUE 1
#define FALSE 0
#define MAX_WORDS 100
#define MAX_LENGTH 20
#define WIN 1
#define LOSE 0

int read_file(char* filename, char words[MAX_WORDS][MAX_LENGTH]){
    FILE *file;
	file = fopen(filename, "r");
    if(file == NULL){ // checks if file exists
        printf("Error with File"); 
    }else{
        char line[MAX_LENGTH]; // initilises the line array
        int numwords = 0;
        while(fscanf(file, "%s", line) != EOF){ // gets string from a single line in the txt file
            strcpy(words[numwords], line); // copys the line into the words array
            numwords++; // increments count
        } 

        fclose(file); // Closes file
        return numwords;
    }
    
}

int has_solved(char* answer, int solution_length){
    for(int i = 0; i <= solution_length; i++){ // loops over entire 'answer' array
        if(answer[i] == '_'){ // checks if it can find a single _ (not answered)
            return 0; // returns 0 to confirm it isn't finished
        }
    }
    return 1; // if it doesn't find an _, words found and as such returns 1
}

int get_random_index(int number);

int play_game(char* word, char* player_answer, int solution_length){
    // needs a while loop to loop until either out of turns or has_solved.
    // need a scanf (look at q4 lab 2 for this) // gives letter input
    char guess;
    int answer = 0;
    int turns = 1;
    while(turns <= ATTEMPTS && answer == 0){ // runs the game while player hasn't found the answer and they have attempts left
        printf("%d) Please enter a letter: ", turns);
        scanf("\n%c", &guess); // takes user input as 'guess'
        for(int i = 0; i < solution_length; i++){
            if(guess == word[i]){ // checks to see if the word guessed is in the answer
                player_answer[i] = guess; // sets guess to right position in player_answer array if it's right
            }
        }
        for(int x = 0; x < solution_length; x++){ // loops for length of solution
            printf("%c ", player_answer[x]); // prints either a letter or _ for
        }
        printf("\n"); // prints a new line
        turns++; // increments turns for turn counter
        
        answer = has_solved(player_answer, solution_length); // checks to see if they've found an answer
    }
    if(has_solved(player_answer, solution_length) == TRUE){ // checks at the end of all the attempts if they've found the answer
        return WIN;
    }else{
        return LOSE;
    }
}

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
    }
    else {
        char* filename = argv[1];
        char words[MAX_WORDS][MAX_LENGTH];
        int count = read_file(filename, words);
        int rand_index = get_random_index(count);
        char* solution = words[rand_index];
        int solution_length = strlen(solution);
        char player_answer[MAX_LENGTH];
        for (int i = 0; i < MAX_LENGTH; i++) {
            if (i < solution_length) {
                player_answer[i] = '_';
            }
            else {
                player_answer[i] = '\0';
            }
        }
        int outcome = play_game(solution, player_answer, solution_length);
        if (outcome == WIN) {
            printf("Congratulations! You have won!\n");
        }
        else {
            printf("You have not won! The solution is %s\n", solution);
            printf("Try again!\n");
        }
    }
    return 0;
}

int get_random_index(int number) {
    int rand_index = rand() % number;
    return rand_index;
}