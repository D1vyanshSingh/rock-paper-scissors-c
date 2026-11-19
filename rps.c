#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rps.h"

void play_game(void)
{
    FILE *settings;
    FILE *history;
    int rounds, round;
    int player, computer;
    int player_score = 0, computer_score = 0;

    settings = fopen("settings.txt", "r");
    if (settings == NULL) {
        printf("Error: settings.txt not found.\n");
        return;
    }

    fscanf(settings, "%d", &rounds);
    fclose(settings);

    srand(time(NULL));

    history = fopen("game_history.txt", "a");
    if (history == NULL) {
        printf("Error: Could not save game history.\n");
        return;
    }

    printf("\n===== ROCK PAPER SCISSORS =====\n");
    printf("You will play %d rounds.\n", rounds);
    printf("1. Rock\n2. Paper\n3. Scissors\n");

    for (round = 1; round <= rounds; round++) {
        printf("\n--- Round %d ---\n", round);
        printf("Enter your choice (1-3): ");

        if (scanf("%d", &player) != 1) {
            int ch = getchar();

            if (ch == EOF) {
                printf("\nNo more input, so the game stops here.\n");
                break;
            }
            printf("Invalid input! Please enter a number.\n");
            while (ch != '\n' && ch != EOF)
                ch = getchar();
            round--;
            continue;
        }

        if (player < 1 || player > 3) {
            printf("Invalid choice! Please enter 1, 2, or 3.\n");
            round--;
            continue;
        }

        computer = rand() % 3 + 1;

        printf("You chose: ");
        if (player == 1) printf("Rock\n");
        else if (player == 2) printf("Paper\n");
        else printf("Scissors\n");

        printf("Computer chose: ");
        if (computer == 1) printf("Rock\n");
        else if (computer == 2) printf("Paper\n");
        else printf("Scissors\n");

        if (player == computer) {
            printf("Result: Draw!\n");
        }
        else if ((player == 1 && computer == 3) ||
                 (player == 2 && computer == 1) ||
                 (player == 3 && computer == 2)) {
            printf("Result: You win this round!\n");
            player_score++;
        }
        else {
            printf("Result: Computer wins this round!\n");
            computer_score++;
        }

        fprintf(history, "Round %d: Player=%d, Computer=%d\n",
                round, player, computer);
    }

    printf("\n===== FINAL SCORE =====\n");
    printf("Your score: %d\n", player_score);
    printf("Computer score: %d\n", computer_score);

    if (player_score > computer_score)
        printf("Congratulations! You are the overall winner!\n");
    else if (computer_score > player_score)
        printf("Computer is the overall winner. Better luck next time!\n");
    else
        printf("The game is a draw!\n");

    fprintf(history, "Final Score: Player=%d, Computer=%d\n\n",
            player_score, computer_score);
    fclose(history);
}
