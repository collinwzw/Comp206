/* FILE: A2_bmp_helpers.c is where you will code your answers for Assignment 2.
 * 
 * Each of the functions below can be considered a start for you. 
 *
 * You should leave all of the code as is, except for what's surrounded
 * in comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A2_bmp_headers.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int bmp_open( char* bmp_filename,        unsigned int *width, 
              unsigned int *height,      unsigned int *bits_per_pixel, 
              unsigned int *padding,     unsigned int *data_size, 
              unsigned int *data_offset, unsigned char** img_data ){

              
    // YOUR CODE FOR Q1 SHOULD REPLACE EVERYTHING FROM HERE
    
    FILE *fp;
    fp=fopen(bmp_filename, "rb");
    
    char b, m;
    fread (&b,1,1,fp);
    fread (&m,1,1,fp);
    if(b=='B'&& m=='M'){
        //printf("it's bm file\n");
        fread( data_size, sizeof(unsigned int), 1, fp );
        printf( "in info: The size was: %d \n", *data_size );
        fclose(fp);
        fp=fopen(bmp_filename, "rb");
        unsigned char * data = (unsigned char *) malloc((*data_size)*sizeof(unsigned char));
        fread(data, 1, *data_size, fp);
        
        unsigned int* offsetp = (unsigned int*)(data+10); //recasting
        *data_offset = *offsetp;  //assigning
        unsigned int* wp = (unsigned int*)(data+18);
        *width = *wp;
        unsigned int* hp = (unsigned int*)(data+22);
        *height = *hp;
        unsigned int* bppp = (unsigned int*)(data+28);
        *bits_per_pixel = *bppp;
        *padding = (*width)*(*bits_per_pixel/8) % (4);
        if (*padding != 0) *padding= 4-*padding;
        //printf("%d",*padding);
        *img_data=data;
        //printf("%c",*data);
        
    }
    else return -1;
    // TO HERE
  
  return 0;  
}

// We've implemented bmp_close for you. No need to modify this function
void bmp_close( unsigned char **img_data ){

  if( *img_data != NULL ){
    free( *img_data );
    *img_data = NULL;
  }
}

int bmp_mask( char* input_bmp_filename, char* output_bmp_filename, 
              unsigned int x_min, unsigned int y_min, unsigned int x_max, unsigned int y_max,
              unsigned char red, unsigned char green, unsigned char blue )
{
  unsigned int img_width;
  unsigned int img_height;
  unsigned int bits_per_pixel;
  unsigned int data_size;
  unsigned int padding;
  unsigned int data_offset;
  unsigned char* img_data    = NULL;
  
  int open_return_code = bmp_open( input_bmp_filename, &img_width, &img_height, &bits_per_pixel, &padding, &data_size, &data_offset, &img_data ); 
  
  if( open_return_code ){ printf( "bmp_open failed. Returning from bmp_mask without attempting changes.\n" ); return -1; }
 
    // YOUR CODE FOR Q2 SHOULD REPLACE EVERYTHING FROM HERE
    //unsigned char * data= (unsigned char *)malloc((data_size)*sizeof(unsigned char));
    unsigned char data_array[img_height][img_width*(bits_per_pixel/8)+padding];
    //memcpy(data_array, img_data, data_size);
    
    
    int index=0;
    for(int i=img_height-1; i>=0;i--){ //row
        //printf("%d th row:",i);
        for (int j=0; j<(img_width) * (bits_per_pixel/8)+padding;j++){   //coloum
                data_array[i][j]=(unsigned int)*(img_data+data_offset+index);
            if(j>=x_min*(bits_per_pixel/8) && j<=x_max* (bits_per_pixel/8) && i>=img_height-y_max  && i<= img_height-y_min){
                if (j%3==0)  data_array[i][j]=red;
                if (j%3==1) data_array[i][j]=green;
                if (j%3==2) data_array[i][j]=blue;
            }
            index=index+1;
        }
    }
    unsigned char * output_data= (unsigned char *)malloc((data_size)*sizeof(unsigned char));
    
    index=0;
    for(int i=img_height-1; i>=0;i--){ //row
        for (int j=0; j<(img_width) * (bits_per_pixel/8)+padding;j++){   //coloum
            *(output_data+index) =(unsigned char) data_array[i][j];
            index=index+1;
        }
    }

    FILE* fop;
    fop = fopen(output_bmp_filename,"w");
    fwrite(img_data,1,data_offset,fop);
    fwrite(output_data,1,data_size,fop);
    fclose(fop);
    free(output_data);
    // TO HERE!
  
  bmp_close( &img_data );
  
  return 0;
}         

int bmp_collage( char* bmp_input1, char* bmp_input2, char* bmp_result, int x_offset, int y_offset ){

  unsigned int img_width1;
  unsigned int img_height1;
  unsigned int bits_per_pixel1;
  unsigned int data_size1;
  unsigned int padding1;
  unsigned int data_offset1;
  unsigned char* img_data1    = NULL;
  
  int open_return_code = bmp_open( bmp_input1, &img_width1, &img_height1, &bits_per_pixel1, &padding1, &data_size1, &data_offset1, &img_data1 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input1 ); return -1; }
  
  unsigned int img_width2;
  unsigned int img_height2;
  unsigned int bits_per_pixel2;
  unsigned int data_size2;
  unsigned int padding2;
  unsigned int data_offset2;
  unsigned char* img_data2    = NULL;
  
  open_return_code = bmp_open( bmp_input2, &img_width2, &img_height2, &bits_per_pixel2, &padding2, &data_size2, &data_offset2, &img_data2 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input2 ); return -1; }
  
  // YOUR CODE FOR Q3 SHOULD REPLACE EVERYTHING FROM HERE
 
       // creating new data header size and copy the old value
    int new_offset;
    if (data_offset1<=data_offset2) {
        new_offset = data_offset2;
    }
    else {
        new_offset = data_offset1;
    }
     // header memory for new bmp file (only header)
    unsigned char * output_header= (unsigned char *)malloc(new_offset*sizeof(unsigned char));
    if (data_offset1<=data_offset2) {
        memcpy(output_header, img_data2, data_offset2); // copy the header of input 2 to new bmp file header
    }
    else {
        memcpy(output_header, img_data1, data_offset1); // copy the header of input 1 to new bmp file header
    }
    

    
    // reassign every variable for new bmp file header
    unsigned int new_width;
    if (x_offset>=img_width1&& x_offset>=0){        // the img 2 will be right out side of the img 1 in terms of width
        new_width = (int) (x_offset - img_width2) + img_width2 + img_width1 ;
        
    }
    else if (x_offset <img_width1 && x_offset >=0)  {
        if (x_offset+img_width2>=img_width1)         new_width = (int) x_offset+(img_width2 ) ; // the img 2 is partially in side of the img 1 but will go right out side of img 1 in terms of width
        else    new_width = (int) img_width1  ;     // the img 2 is in side of the img 1  in terms of width
    }
    else if (x_offset <0){
        if (img_width2>= img_width1-x_offset)         new_width = (int) img_width2  ;   // the img 1 is in side of the img 2 in term of width

        else     new_width = (int) img_width1 -x_offset ;       // the img 1 is partially in side of the img 2 but will go right out side of img 2 in terms of width
        
    }
    unsigned int* new_width_p= (unsigned int *)(& output_header[18]);
    * new_width_p =   new_width;

    
    unsigned int new_height;
    if (y_offset>=img_height1 && y_offset>=0 ){     // the new img is top out side of the img 1 in terms of height

        new_height = (int) img_height1 + img_height2 + (y_offset - img_height1);
    }
    
    else if (y_offset <img_height1 && y_offset >=0)  {
        if (y_offset+img_height2>=img_height1)         new_height = (int) y_offset+(img_height2 ) ;// the img 2 is partially in side of the img 1 but will go top out side of img 1 in terms of height
        else    new_height = (int) img_height1  ;   // the img 2 is partially in side of the img 1  in terms of height
    }
    else if (y_offset <0){
        if (img_height2>= img_height1-y_offset)         new_height = ( int) img_height2 ;   // the img 1 is  in side of the img 2 in term of width
        else if (img_height2 < img_height1-y_offset)    new_height = ( int) img_height1 - y_offset  ;// the img 1 is partially in side of the img 2 but will go top out side of img 2 in terms of height

    }
    unsigned int* new_height_p= (unsigned int *)(&output_header[22] );
    * new_height_p=  new_height;
    
    unsigned int new_bpp;
    if(bits_per_pixel1!=bits_per_pixel2){
        printf("the two files have different bpp");
    }
    else new_bpp = bits_per_pixel1;
    //printf("new bit per pixel is %d\n",new_bpp);

    int newpadding;             // new paddings
    newpadding = new_width*(new_bpp/8)%4;
    if (newpadding != 0) newpadding= 4-newpadding;
    
    unsigned int new_image_data_size;       // new bmp file data size (exclude the header)
    new_image_data_size= new_height*newpadding + new_height * new_width * (new_bpp/8);
    
    unsigned int new_data_size;
    new_data_size = new_image_data_size + new_offset;
   
    unsigned int* new_datasize_p= (unsigned int *)(& output_header[2]);
    *new_datasize_p=  new_data_size;
    //printf("data size is %d\n", new_data_size);
    
    // reading data to array from two original files.

    unsigned char data_array1[img_height1][img_width1*(bits_per_pixel1/8)];

    int index1=0;
    for(int i=img_height1-1; i>=0;i--){ //row
        for (int j=0; j<(img_width1) * (bits_per_pixel1/8);j++){   //coloum
            data_array1[i][j]=(unsigned char)*(img_data1+data_offset1+index1);
           // if((img_data1+data_offset1+index1) = )
            if (j==((img_width1) * (bits_per_pixel1/8)-1)&& padding1 !=0) index1=index1 +padding1+1;
            else index1=index1+1;
        }
        //printf("the original %d th row's first element is  %d \n", i,data_array1[i][0]);
    }
 
    unsigned int data_array2[img_height2][img_width2*(bits_per_pixel2/8)];
    
    int index2=0;
    for(int i=img_height2-1; i>=0;i--){ //row
        for (int j=0; j<(img_width2) * (bits_per_pixel2/8);j++){   //coloum
            data_array2[i][j]=(unsigned char)*(img_data2+data_offset2+index2);
            if (j==((img_width2) * (bits_per_pixel2/8)-1)&& padding2 !=0) index2=index2 +padding2+1;
            else index2=index2+1;
        }
    }
    printf("height of new img is %d \n",new_height);
    printf("width of new img is %d \n",new_width);
    printf("padding of new img is %d \n",newpadding);
    printf("new bit per pixel is %d\n",new_bpp);
    
    // creating new data array and read the new data into it.
    /*
    for (int i=img_height2-1; i>=0; i--) {
        for (int j=0; j<img_width2*3; j++) {
            printf("%u ",data_array2[i][j]);
            printf("j is %d\t",j);
            count1++;
        }
        printf("%d'th row is checked\n", i);
    }
    printf("count1 is %d", count1);
     */
    unsigned int data_array[new_height][new_width*(new_bpp/8)+newpadding];
    
    int itwo;     //row
    int jtwo;                 //coloum
    int ione;
    int jone;
    int i=0;
    int j=0;
    int itwocount=0;
    int paddingcount=0;
    int caseindex=0;
    int spacecounting=0;
    
    // caseindex assign
    if (x_offset+img_width2 <= img_width1 && y_offset+img_height2 <= img_height1) caseindex = 1;  // image2 is inside of image 1
   
    if(x_offset+img_width2>img_width1 || y_offset+img_height2>img_height1) caseindex = 2;   // image 2 is width outside and height outside in postive offset direction.
    //if (x_offset+img_width2>=img_width1 && y_offset+img_height2>=img_height1) caseindex = ;
    if (x_offset <img_width1 && x_offset >=0 && img_height2 < img_height1-y_offset && y_offset <0) caseindex = 3;   // img 2 is below and inside of img 1
    //printf("caseindex is %d",caseindex);
    if (x_offset <0 && y_offset<0) caseindex = 4;
    switch(caseindex){
        case 0:  printf("this piece of code can't deal with these two bmp files." );    // case 0 means nothing matched
        break;
   
        case 1:         // image2 is inside of image 1
            printf("case 1 \n");
            itwo=img_height2-1;
            jtwo=0;
            for(i=new_height-1; i>=0;i--){ //row
                //printf("checking %d th row", i);
                    for (j=0; j< ((new_width)*(new_bpp/8)+newpadding);j++){   //coloum
                    if (j>=((new_width) * (new_bpp/8))){            // if the array reaches the padding space if any.
                        data_array[i][j] = 0;
                        paddingcount++;
                    }
                        
                    else{
                   
                        if (i< (new_height-y_offset) && i > (new_height - y_offset -img_height2) && j >= ((x_offset)*(new_bpp/8)) && j< ((x_offset + img_width2))*(new_bpp/8) ) {   // if array reaches img 2 area.
                            data_array[i][j] = data_array2[itwo][jtwo];
                            jtwo++;
                            itwocount++;
                        }
                        else{
                            data_array[i][j] = data_array1[i][j];
                        }
                    }
                }
                if (jtwo != 0 ){
                    itwo--;
                    jtwo=0;
                }
        //printf("the outputfile %d th row's first element is  %d \n", i,data_array[i][0]);
            }
        break;
    
        case 2:
            
            printf("case 2 \n");
            //printf("checking %d th row", i);
            itwo=img_height2-1;
            jtwo=0;
            ione=img_height1-1;
            jone=0;
            for(i=new_height-1; i>=0;i--){ //row
                //printf("checking %d th row", i);

                for (j=0; j<(new_width) * (new_bpp/8)+newpadding;j++){   //coloum
                    
                    if (j>=((new_width) * (new_bpp/8))){        // if the array reaches the padding space if any.
                        data_array[i][j] =  0;
                        paddingcount++;
                    }
                    else{
                        if (i<new_height-y_offset && i >=new_height-img_height2 && j >= ((x_offset-1)*(new_bpp/8)) && j< ((new_width))*(new_bpp/8) ) {
                            data_array[i][j] = data_array2[itwo][jtwo];
                            jtwo++;
                            itwocount++;
                        }
                        else if (i >= new_height - y_offset && j < img_width1 * (bits_per_pixel1/8) ){
                            data_array[i][j] = data_array1[ione][jone];
                            jone++;
                            
                        }
                        else if (i < new_height - y_offset  && ione>=0 &&j < img_width1 * (bits_per_pixel1/8)){
                            data_array[i][j] = data_array1[ione][jone];
                            jone++;
                            
                        }
                        else if (i < new_height - y_offset && j < (x_offset-1) * (bits_per_pixel1/8) ){
                            if(ione>=0){
                            data_array[i][j] = data_array1[ione][jone];
                            jone++;
                            }
                            
                            else{
                                data_array[i][j] = (unsigned int) 0;
                                spacecounting++;
                            }
                        }
                        else if(i>=new_height-y_offset && j >=img_width1*(bits_per_pixel1/8)){
                            data_array[i][j] = (unsigned int) 0;
                            spacecounting++;
                        }
                    }
                }
                if (jtwo != 0 ){
                    itwo--;
                    jtwo=0;
                }
                if (jone != 0 ){
                    ione--;
                    jone=0;
                }
                //printf("the outputfile %d th row's first element is  %d \n", i,data_array1[i][0]);
            }
            break;
        case 3:
            printf("case 3\n");
            itwo=img_height2-1;
            jtwo=0;
            ione=img_height1-1;
            jone=0;
            for(i=new_height-1; i>=0;i--){ //row
                //printf("checking %d th row", i);

                for (j=0; j<(new_width) * (new_bpp/8)+newpadding;j++){   //coloum
                    
                    if (j>=((new_width) * (new_bpp/8))){
                        data_array[i][j] =  0;
                        paddingcount++;
                    }
                    else{
                        if (i >= new_height-img_height2 && j< (img_width2)*(new_bpp/8) ) {  // save the data2 to data
                            if (i < img_height1 ){      // if the data didn't reach the data 1 area yet
                                jone++;
                            }
                            
                            data_array[i][j] = data_array2[itwo][jtwo];
                            jtwo++;
                            itwocount++;
                        }
                    
                    else if (i >= new_height-img_height2 && j> (img_width2)*(new_bpp/8)  ){
                        if (i <img_height1){
                                data_array[i][j] = data_array1[ione][jone];
                                jone++;
                            }
                        else{
                            data_array[i][j] = (unsigned int) 255;
                            spacecounting++;
                        }
                        }
                    else if (  i < img_height1 ){
                            
                            data_array[i][j] = data_array1[ione][jone];
                            jone++;
                        }
                    }
                }
                if (jtwo != 0 ){
                    itwo--;
                    jtwo=0;
                }
                if (jone != 0 ){
                    ione--;
                    jone=0;
                }
                //printf("the outputfile %d th row's first element is  %d \n", i,data_array1[i][0]);
            }
            break;
            
        case 4:
            printf("case 4\n");
           
            //printf("checking %d th row", i);
            itwo=img_height2-1;
            jtwo=0;
            ione=img_height1-1;
            jone=0;
            for(i=new_height-1; i>=0;i--){ //row
                //printf("checking %d th row", i);
                
                for (j=0; j<(new_width) * (new_bpp/8)+newpadding;j++){   //coloum
                    
                    if (j>=((new_width) * (new_bpp/8))){        // if the array reaches the padding space if any.
                        data_array[i][j] =  0;
                        paddingcount++;
                    }
                    else{
                        if ( i >=new_height-img_height2 && j < ((img_width2)*(new_bpp/8))) {   // print img 2
                                data_array[i][j] = data_array2[itwo][jtwo];
                                jtwo++;
                                itwocount++;
                            if(i<=new_height+y_offset && j >= (-x_offset)*(new_bpp/8)){         // reaches the area of both image are present
                                jone++;
                            }
                        }
                        else if (i > (new_height+y_offset)  && j >= ((img_width2)*(new_bpp/8)) ){     // blank area right side of img 2 if any
                            data_array[i][j] = (unsigned int) 0;
                            spacecounting++;
                        }
                        else if (i < new_height - img_height2  && j < (-x_offset) * (bits_per_pixel1/8)){   // blank area top side of img 2 if any
                            data_array[i][j] = (unsigned int) 0;
                            spacecounting++;
                        }
                        else {
                            data_array[i][j] = data_array1[ione][jone];
                            jone++;
                        }
                    }
                }
                if (jtwo != 0 ){
                    itwo--;
                    jtwo=0;
                }
                if (jone != 0 ){
                    ione--;
                    jone=0;
                }
                //printf("the outputfile %d th row's first element is  %d \n", i,data_array1[i][0]);
            }
            break;

    }
    

    printf("i is %d\t", i);
    printf("j is %d\t\n", j);
    printf("itwo is %d\t", itwo);
    printf("itwo count is %d\t", itwocount);
    printf("space count is %d\t", spacecounting);
    printf("paddingcount is %d\n", paddingcount);


   
    unsigned char * output_data= (unsigned char *)malloc((new_image_data_size)*sizeof(unsigned char));  // data memory for new bmp file (only data)

    int index=0;
    for(int i=new_height-1; i>=0;i--){ //row
        for (int j=0; j<(new_width) * (new_bpp/8)+newpadding;j++){   //coloum
            *(output_data+index) =(unsigned char) data_array[i][j];
            index=index+1;
        }
    }
    //printf("data index is %d\t", index);

    
    //unsigned int temp = (unsigned int) *(output_header+2);
    //printf("final write in data size is %d\t", temp);
    FILE* fop;
    fop = fopen(bmp_result,"w");
    fwrite(output_header,1,new_offset,fop);
    fwrite(output_data,1,new_image_data_size,fop);
    fclose(fop);
    free(output_header);
    free(output_data);
  // TO HERE!

  bmp_close( &img_data1 );
  bmp_close( &img_data2 );
  
  return 0;
}                  
