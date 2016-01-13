#import <cstdio>
#import <cstdlib>
#import <random>

int main()
{
    // See the printf to understand these parameters
    float startingAmount = 1000;
    float desiredWinnings = 10;
    float bet = 1;
    float chanceOfSuccess = 0.49;
    int days = 10000;
    bool isAnAlcoholic = true;
    int numBetsBeforeGettingAFreeDrink = 5;
    float valueOfAFreeDrink = 3;
    float secondsPerRound = 30;

    printf("You walk into the casino every day for %d days. "
           "You bring $%2.0f with you each day, and walk away when you make $%2.0f or lose all your money. "
           "You bet %2.0f dollars each round, and your chance of success is %0.2f. "
           "You spend %.0f seconds each round. "
           "How much will you win? How much time will you spend?\n\n",
           days, startingAmount, desiredWinnings, bet, chanceOfSuccess, secondsPerRound);
    if(isAnAlcoholic)
    {
        printf(
           "You are an alcoholic. "
           "Alcoholics treat free drinks as winnings, and the longer you play, the more free drinks you get. "
           "You get one free drink every %d rounds, and drinks are worth $%0.2f to you.\n\n",
            numBetsBeforeGettingAFreeDrink, valueOfAFreeDrink);
    }

    srand(time(NULL));

    float totalWinnings = 0;
    long int totalFreeDrinks = 0;
    float totalTimeSpentInCasino = 0;
    for(int day = 0; day < days; ++day)
    {
        // Start each day with startingAmount, and play until success or failure.
        float todaysCash = startingAmount;
        long int numRounds;
        for(numRounds = 0; todaysCash > 0 && todaysCash < startingAmount+desiredWinnings; ++numRounds)
        {
            float success = rand() / float(RAND_MAX);

            if(success < chanceOfSuccess)
            {
                todaysCash += bet;
            }
            else
            {
                todaysCash -= bet;
            }

            if(isAnAlcoholic && numRounds % numBetsBeforeGettingAFreeDrink == 0)
            {
                totalFreeDrinks++;
            }
        }

        totalWinnings += todaysCash - startingAmount;
        totalTimeSpentInCasino += numRounds * secondsPerRound;
        printf("\rOn Day %5d, you walk away with %5.2f. Total winnings: %5.2f, total value of free drinks: %8.2f, time spent at casino: %5.2f",
               day, todaysCash, totalWinnings, totalFreeDrinks * valueOfAFreeDrink, totalTimeSpentInCasino);
    }

    float totalFreeDrinkWinnings = totalFreeDrinks*valueOfAFreeDrink;
    printf("\n\nTotal winnings: %.2f, total free drinks: %.2f, for a total of $%.2f. You spent %2.2f%% of your time in the casino.\n",
           totalWinnings, totalFreeDrinkWinnings, totalWinnings + totalFreeDrinkWinnings, 100*(totalTimeSpentInCasino / 60 / 60 / 24)/float(days));
}
