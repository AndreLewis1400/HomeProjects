/*
 * Author: Andre Lewis
 * Location: Home
 * Date: 04/26/2024
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define YEARS_5 5
#define MONTHS_12 12

    int main()
    {
    int year; // yearly rain fall
    int month; // monthly rain fall
    int year_1 = 2020; // begining year of rain fall
    float totalYearlyRain = 0.0; // total yearly rain fall
    float averageYearlyRain = 0.0; // average yearly rain fall
    float raindata[YEARS_5][MONTHS_12]; // 2D array wit fixed dimensions
    float subtot; // total rain fall

    printf("YEAR\t\tRAINFALL(inches)\n"); // display heading
/*
iterate through each row looking at each column.
*/
    for (year = 0; year < YEARS_5; ++year) // outer loop
    {
        for (month = 0; month < MONTHS_12; ++month) // inner loop
        {
            raindata[year][month] = 4.5; // add value to each array for test case
            totalYearlyRain += raindata[year][month]; // // add total yearly rain fall for each row
        } // end of inner loop

        printf("%d\t\t\t%.2f\n", year_1, totalYearlyRain); // display total rain fall each year
        subtot += totalYearlyRain; // subtotal rain fall for all years
		averageYearlyRain = subtot / 5; // average rain fall for 5 years
        ++year_1; // increment the years
    } // end of outer loop

    printf("\nThe yearly average is: %.2f inches.\n\n", averageYearlyRain); // display yearly average for 5 years
    printf("MONTHLY AVERAGES\n\n"); // display heading

    printf("Jan     Feb     Mar     Apr     May     Jun     Jul     Aug     Sep     Oct     Nov     Dec\n"); // display heading
/*
iterate through each column looking at each row
to calculate monthly averages.
*/
    for (month = 0; month < MONTHS_12; ++month) // outer loop, iterate through each column
    {
        for (year = 0, subtot = 0; year < YEARS_5; ++year) // inner loop, iterate through each row
            subtot += raindata[year][month]; // add up rain fall for each column
            printf("%.2f    ", subtot/YEARS_5); // display total rain fall for each column
    }
    printf("\n");
return 0;
    }
