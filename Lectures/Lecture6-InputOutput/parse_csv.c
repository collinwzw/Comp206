/* 
 * FILE: parse_csv.c Is an overly simplified csv parser just to show
 *                   the main concepts. We open a file, read it 
 *                   line-by-line, and scan until we find the tokens
 *                   to extract individual words.
 *
 * Shown in class on Jan 25th, 2018
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv ){

	if( argc != 2 ){
		printf( "Usage: %s csv_path.\n", argv[0] );
		exit(-1);
	}

	char *word_list[3];

	FILE* csv_file = fopen( argv[1], "r" );

	if( csv_file == NULL ){
		printf( "Unable to open file %s.\n", argv[1] );
		exit(-1);
	}

	char line_buffer[1000];

	while(fgets(line_buffer,1000,csv_file)){

		char* line_ptr = line_buffer;
		word_list[0] = line_ptr;
		int curr_word = 1;

		while(*line_ptr && *line_ptr != '\n' ){

			while(*line_ptr != ',' && *line_ptr && *line_ptr != '\n' ){ 
				line_ptr++;
			}

			if( *line_ptr == ',' ){
				*line_ptr = '\0';
				word_list[curr_word] = line_ptr+1;
				curr_word++;
				line_ptr++;
			}
			if( *line_ptr == '\n' ){
				*line_ptr = '\0';
			}
		}

		for( int word_idx=0; word_idx<curr_word; word_idx++ ){
			printf( "Word %d: <%s> ", word_idx, word_list[word_idx] );
		}
		printf("\n");
	}
}
