#include "headers/httptime.h"

/* Helper method that returns the time passed in 
formatted in the http-date standard */

char * currentTimeFormatted(time_t rawtime){
    
        time(&rawtime);
        struct tm* tm = gmtime(&rawtime);
        char * formattedTime = (char *) malloc(HTTP_DATE_LEN);
        char * weekDay = (char *) malloc(sizeof(char) * 3);
        const char* months[12] = {"Jan", "Feb", "Mar", 
        "Apr", "May", "Jun", "Jul", "Aug", "Sep", 
        "Oct", "Nov", "Dec"};

        switch(tm->tm_wday){
            case 0:
                sprintf(weekDay, "Sun");
                break;
            case 1:
                sprintf(weekDay, "Mon");
                break;
            case 2:
                sprintf(weekDay, "Tue");
                break;
            case 3:
                sprintf(weekDay, "Wed");
                break;
            case 4:
                sprintf(weekDay, "Thu");
                break;
            case 5:
                sprintf(weekDay, "Fri");
                break;
            case 6:
                sprintf(weekDay, "Sat");
                break;
        }

        int year = GMT_EPOCH + tm->tm_year;

        sprintf(formattedTime, "%s, %02d %s %d %02d:%02d:%02d GMT", 
        weekDay, tm->tm_mday, months[tm->tm_mon], year, tm->tm_hour,
         tm->tm_min, tm->tm_sec);
        free(weekDay);
        return formattedTime;
    }