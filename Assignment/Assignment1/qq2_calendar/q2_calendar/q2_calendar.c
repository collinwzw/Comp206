//
//  main.c
//  q2_calendar
//
//  Created by Ziwen Wang on 2018-01-30.
//  Copyright © 2018 Ziwen Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[]) {
    
    if(argc!=3){                                // condition checking
        printf("there should be two command line arguement\n");
        return 0;
    }
    
    int daysize = atoi(*(argv+1));
    int firstday = atoi(*(argv+2));

    if (daysize < 2){                            // condition checking
        
        printf("the day size can only be bigger or equal than 2\n");
        return 0;
    }
    
    if (firstday > 7 || firstday < 1 ){             // condition checking
        
        printf("the first day can only be 1 to 7, 1 is Sunday\n");
        return 0;
    }
    
    
    
  
    
    char *day_string[7];            //define a string that contains the name of each day of the week
    day_string[0]= "Sunday";
    day_string[1]= "Monday";
    day_string[2]= "Tuesday";
    day_string[3]= "Wednesday";
    day_string[4]= "Thursday";
    day_string[5]= "Friday";
    day_string[6]= "Saturday";
    
    char *month_string[12];
    month_string[0]="January";
    month_string[1]="February";
    month_string[2]="March";
    month_string[3]="April";
    month_string[4]="May";
    month_string[5]="June";
    month_string[6]="July";
    month_string[7]="August";
    month_string[8]="September";
    month_string[9]="October";
    month_string[10]="November";
    month_string[11]="December";
    
    //printf("the number of character will be shown is %d\n", daysize);
    //printf("the first day is %.*s\n",daysize,day_string[firstday-1]);
    
    
    // printing the calendar
    int linewidth = (daysize+3)*7+1;
    for(int m=1;m<=12;m++){
        
        //get length of the correspoding length of each month
        int month_length=strlen(month_string[m-1]);
        //printf("length of month is %d\n",length);
        
        //define # of space required for front and back space of the month and check if it's odd number or not
        
        int front, back;
        front=(linewidth-2-month_length)/2;
        back=front;
        if ((linewidth-2-month_length)%2 !=0){
            back=back+1;
        }
        //printf("back is %d\n",back);
        //printf("front is %d\n",front);
        
        int lastday;
        
        for(int i=1;i<12;i++){
            
        
        //print first line
        printf("|");
        
        if(i == 1 || i==3|| i==5){
            for (int j=1;j<=linewidth-2;j++){
                printf("-");
            }
            printf("|\n");
        }
        if(i == 2){
                for (int j=1;j<=front;j++){
                    printf(" ");
                }
                printf("%s",month_string[m-1]);
            
                for (int j=1;j<=back;j++){
                    printf(" ");
                }
            printf("|\n");
        }
        if(i==4){
            for (int j=1;j<=7;j++){
                
                int day_length =strlen(day_string[j-1]);
                printf(" %.*s",daysize,day_string[j-1]);
                
                int n;
                n=daysize-day_length;
              
                do {
        
                    printf(" ");
                    n--;
                }while(n>=0);
                
                if (j<=6) printf("|");
                }
            printf("|\n");
            }
        if(i>5){
            int d=1;
            int space=1;
            int row_number=5;
            
            if(firstday%7 == 0 ) row_number=row_number+1;
            
            
            while (d<=7*row_number){
                
                if (d<firstday || d >=(30+firstday)){
                    for (int j=1; j<=daysize+2; j++){
                    printf(" ");
                    }
                    space=space+daysize+3;
                    d++;
                }
                
                else{
                printf(" %d",d-firstday+1);
                    if (d-firstday+1<10) {
                        for (int j=1; j<=daysize; j++){
                            printf(" ");
                        }
                    }
                    else{
                        for (int j=1; j<=daysize-1; j++){
                            printf(" ");
                        }
                    }
                    space=space+daysize+3;
                    d++;
                    lastday=d;
                    
                }
                printf("|");
                
                if (space==linewidth){
                    
                    printf("\n");
                    space=1;
                    if (d<=(30+firstday-1)) printf("|");
                    
                }
                
                
            }
            
            i=12;
            if (lastday%7!=0) firstday = lastday%7;
            else firstday=7;
        }
            
        
    
        }
    }
    //print final separator of the year
    printf("|");
    for (int j=1;j<=linewidth-2;j++){
        printf("-");
    }
    printf("|\n");
    
}
