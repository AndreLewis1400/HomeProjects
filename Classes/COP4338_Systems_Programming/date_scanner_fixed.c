#include <stdio.h>
#include <string.h>

char* tostr(int month) {
    switch(month) {
        case 1: return "Jan";
        case 2: return "Feb";
        case 3: return "Mar";
        case 4: return "Apr";
        case 5: return "May";
        case 6: return "Jun";  // Fixed: was "Jan"
        case 7: return "Jul";
        case 8: return "Aug";
        case 9: return "Sep";
        case 10: return "Oct";
        case 11: return "Nov";
        case 12: return "Dec";
        default: return "NaM";
    }
}

// Function to validate date
int isValidDate(int month, int day, int year) {
    if (month < 1 || month > 12) return 0;
    if (year < 1) return 0;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Leap year check
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }
    
    return (day >= 1 && day <= daysInMonth[month - 1]);
}

int main() {
    int day, year, month;
    char monthname[20];  // Increased buffer size
    char date[100];
    
    printf("Date Scanner - Enter dates in format: mm/dd/yyyy or day monthname year\n");
    printf("Press Ctrl+D to exit\n\n");
    
    while (1) {
        printf("Enter a date: ");
        
        if (!fgets(date, 100, stdin)) {
            printf("\nExiting...\n");
            break;
        }
        
        // Remove newline character
        date[strcspn(date, "\n")] = 0;
        
        if (sscanf(date, "%d/%d/%d", &month, &day, &year) == 3) {
            if (isValidDate(month, day, year)) {
                printf("Entered date is %dth of %s, %d.\n", day, tostr(month), year);
            } else {
                printf("Invalid date! Please enter a valid date.\n");
            }
        }
        else if (sscanf(date, "%d %s %d", &day, monthname, &year) == 3) {
            // For month name format, we'll assume it's valid for now
            printf("Entered date is %dth of %s, %d.\n", day, monthname, year);
        }
        else {
            printf("Invalid format! Please use mm/dd/yyyy or day monthname year\n");
        }
    }
    
    return 0;
} 