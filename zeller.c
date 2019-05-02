
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<locale.h>
#include<stdlib.h>

//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
void showdatesanddays(void);
int zellergregorian(struct tm* date);

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main()
{
    puts("-----------------------");
    puts("| codedrome.com       |");
    puts("| Zeller's Congruence |");
    puts("-----------------------\n");

    showdatesanddays();

    return EXIT_SUCCESS;
}

//--------------------------------------------------------
// FUNCTION showdatesanddays
//--------------------------------------------------------
void showdatesanddays()
{
    // set of day names corresponding to Zeller's h value
    char* daynames[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    char datestring[64];
    char daystring[10];
    struct tm date = {};
    int h;

    srand(time(NULL));

    // generate 20 random dates
    for(int i = 0; i < 20; i++)
    {
        date.tm_year = (rand() % 2017) - 1900; // in tm, the year is based on 1900
        date.tm_mon = rand() % 11;
        date.tm_mday = rand() % 365; // mktime will sort out tm_mday, eg 32 January becomes 1 February

        // normalize date and set other fields
        mktime(&date);

        strftime(datestring, 64, "%d %B %Y", &date);
        strftime(daystring, 10, "%A", &date);
        h = zellergregorian(&date);

        printf("Date            %s\n", datestring);
        printf("Day (C library) %s\n", daystring);
        printf("Day (Zeller)    %s\n", daynames[h]);
    }
}

//--------------------------------------------------------
// FUNCTION zellergregorian
//--------------------------------------------------------
int zellergregorian(struct tm* pdate)
{
    int h = 0; // day of week, Saturday = 0

    int q = pdate->tm_mday; // day of month
    int m = pdate->tm_mon; // month, 3 to 14 = March to February
    int Y = 1900 + pdate->tm_year; // tm_year is 1900-based

    // adjust month to run from 3 to 14 for March to February
    if(m <= 1)
        m+= 13;
    else
        m+= 1;

    // and also adjust year if January or February
    if(pdate->tm_mon <= 1)
        Y--;

    // Calculate h as per Herr Zeller
    // No need to use floor() as these are all ints
    h = (q + ((13 * (m + 1)) / 5) + Y + (Y / 4) - (Y / 100) + (Y / 400)) % 7;

    return h;
}
