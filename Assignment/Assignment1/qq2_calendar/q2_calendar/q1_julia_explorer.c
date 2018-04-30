//
//  main.c
//  q1_julia_explorer
//
//  Created by Ziwen Wang on 2018-02-01.
//  Copyright © 2018 Ziwen Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    
    if(argc!=4){                                //command line argument condition checking
        printf("there should be three command line arguement\n");
        return 0;
    }
   
    
    
    FILE *fp;
    fp=fopen(argv[1], "r");

    if(access(argv[1], R_OK|W_OK) == -1){
        printf("Error:bad file\n");
        return -1;
    }
    // how to know the inputed string is float or not? does float take int? can I do if a=0 it's wrong?
    float a,b;
    a=atof(*(argv+2));
    b=atof(*(argv+3));
    //printf("%f\n",a);
    //printf("%f\n",b);
    char string[20];
    
    while(1){
        
        //char c;
        //c=fgetc(fp);
        if(fgets(string,sizeof(string),fp)==NULL)  break;
        
        else{
           
            if(strcmp(string,"a= #A#\n")==0) {
                printf("a=%f\n",a);
            }
            else if (strcmp(string,"b= #B#\n")==0) {
                printf("b=%f\n",b);
                }
            
            else{
                printf("%s",string);
                
            }
            
        }
    }
    fclose(fp);
    return 0;
}
