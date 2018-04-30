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
    
    if(argc!=4){                                //command line argument condition checking
        printf("there should be three command line arguement\n");
        return 0;
    }
    
    FILE *fp;
    fp=fopen(argv[1], "r");
    if(fp == NULL){
        printf("Error:bad file\n");
        return -1;
    }
    
    float a,b;
    char check='0';
    
    //int f2 = strcmp(argv[3], &check);
    
    if (strcmp(argv[2], &check)==0){
        a=0;
    }
    else {
        a=atof(*(argv+2));
        if(a==0.000000){
            printf("Error:bad float arg\n");
            return -1;
        }
    }
    
    if (strcmp(argv[3], &check)==0){
        b=0;
    }
    else{
        b=atof(*(argv+3));
        if(b==0.000000){
            printf("Error:bad float arg\n");
            return -1;
        }
    }
    

    char string[3];
    char cmpstring[2000];
    int c;
    int count=0;
    while(feof(fp)!=1){
        
        int i=0;
        
        while(1){
            c= fgetc (fp);
            if (c==EOF) break;
            
            if (c==' '){
                /*
                if(strcmp(string,"#A#")==0){
                    
                    cmpstring[count-sizeof(string)]=a;
                    count=count+sizeof(a);
                }
                if(strcmp(string,"#B#")==0){
                    
                    cmpstring[count-sizeof(string)]=b;
                    count=count+sizeof(b);
                }
             */
                for(int j=0;j<3;j++){
                    string[j]='\0';
                }
                cmpstring[count]=c;
                count=count+1;
                break;
            }
             
            if (c=='\n'){
         
                    
                    //printf("%s", string);
                    
                
                    //printf(" ");
                
                if(strcmp(string,"#A#0")==0){
                    printf("size of string %lu", sizeof(a));
                    cmpstring[count-3]= *argv[2];
                    //printf("test:%c", cmpstring[count-sizeof(string)]);
                    
                    count=count-2;
                }
                if(strcmp(string,"#B#0")==0){
                    
                    cmpstring[count-3]= *argv[3];
                    //printf("test:%c", cmpstring[count-sizeof(string)]);
                    
                    count=count-2;
                }
                //reset
                for(int j=0;j<3;j++){
                    string[j]='\0';
                }
                cmpstring[count]=c;
                count=count+1;
                break;
            }
            
            else{
                if (i>2){
                    string[0]=string[1];
                    string[1]=string[2];
                    string[2]=c;
                    i=i-1;
                }
                else{
                    
                string[i]=c;
                    i++;
                }
                for (int j=0; j <3; j++){
                    
                    //printf("%c", string[j]);
                }
                
                cmpstring[count]=c;
                count=count+1;
                
            }

        }
        //printf("%d ",i);

        
    }
  
        printf("%s",cmpstring);
    
    fclose(fp);
    return 0;
}


/*
 if(fgets(string,strlen(string),fp)==NULL){
 printf("end");
 break;
 }
 else{
 
 if(strcmp(string,"#A#\n")==0) {
 printf(" %.6f\n",a);
 }
 else if (strcmp(string,"#B#\n")==0) {
 printf(" %.6f\n",b);
 }
 
 else{
 // printf("%s",string);
 
 }
 
 }
 
 
 */

/*
 int i=0;
 while (i<29){
 c= fgetc (fp);
 
 if(feof(fp)) break;
 if (c=='#'){
 
 }
 i++;
 printf("%c",c);
 }
 */
/*
 for(int j=0;j<=i;j++){
 
 if(strcmp(string,"#A#\n")==0||strcmp(string,"#B#\n")==0) {
 
 break;
 }
 else if(strcmp(string,"#A# ")==0||strcmp(string,"#B# ")==0) {
 
 break;
 }
 else{
 printf("%c",string[j]);
 }
 
 }
 */
