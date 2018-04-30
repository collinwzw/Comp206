//
//  main.c
//  q1_julia_explorer
//
//  Created by Ziwen Wang on 2018-02-01.
//  Copyright © 2018 Ziwen Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
    
    if(argc!=4){                         //command line argument condition checking
        printf("there should be three command line arguement\n");
        return 0;
    }
    
    FILE *fp;
    fp=fopen(argv[1], "r");
    
    if(fp == NULL){         // checking file exist
        printf("Error:bad file\n");
        return -1;
    }
    
    float a,b;
    char check='0';
    
    if (strcmp(argv[2], &check)==0){     // checking command line arguement is zero or not
        a=0;
    }
    else {
        a=atof(*(argv+2));
        if(a==0.000000){
            printf("Error:bad float arg\n");
            return -1;
        }
    }
    
    if (strcmp(argv[3], &check)==0){    // checking command line arguement is zero or not
        b=0;
    }
    else{                   // convert char to float
        b=atof(*(argv+3));
        if(b==0.000000){
            printf("Error:bad float arg\n");
            return -1;
        }
    }
    
// read the file and check if #A# and #B# exist. if not return bad file.
    char string[2000];
    int c;
    int Acount=0;
    int Bcount=0;
    int i;
    
    while(feof(fp)!=1){
        
        for(i=0;i<20;i++){
            c= fgetc (fp);
            if (c==EOF) break;
            if (c==' '){
                if(strcmp(string,"#A#")==0){
                    Acount++;
                }
                if(strcmp(string,"#B#")==0){
                    Bcount++;
                }
                string[i]=c;
                break;
            }
            else if (c=='\n'){
                if(strcmp(string,"#A#")==0){
                    Acount++;
                }
                if(strcmp(string,"#B#")==0){
                    Bcount++;
                }
                string[i]=c;
                break;
            }
            else{
                string[i]=c;
            }
        }
        //reset
        for(int j=0;j<=i;j++){
            string[j]='\0';
        }
    } // end while
  //checking existance of #A# and #B#;
    if (Acount<1 || Bcount<1){
        printf("Error:bad file\n");
        return -1;
    }
    fclose(fp);   //finishing checking and close the file
    
    //reopen the file for read this time
    fp=fopen(argv[1], "r");
    
    //read
    while(feof(fp)!=1){
        for(i=0;i<20;i++){
            c= fgetc (fp);
            if (c==EOF) break;
            if (c==' '){
                if(strcmp(string,"#A#")==0){
                    printf("%.6f " ,a);
                }
                if(strcmp(string,"#B#")==0){
                    printf("%.6f ",b);
                }
                string[i]=c;
                break;
            }
            else if (c=='\n'){
                if(strcmp(string,"#A#")==0){
                    printf("%.6f\n" ,a);
                }
                if(strcmp(string,"#B#")==0){
                    printf("%.6f\n",b);
                }
                string[i]=c;
                break;
            }
            else{
                string[i]=c;
            }
        }
        //print
        for(int j=0;j<=i;j++){
            
            if(strcmp(string,"#A#\n")==0||strcmp(string,"#B#\n")==0)  break;
            else if(strcmp(string,"#A# ")==0||strcmp(string,"#B# ")==0) break;
            else        printf("%c",string[j]);
        }
        //reset
        for(int j=0;j<=i;j++){
            string[j]='\0';
        }
    }
    fclose(fp);
    return 0;
}

