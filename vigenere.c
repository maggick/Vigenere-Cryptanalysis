/*
 * =====================================================================================
 *
 *       Filename:  vigenere.c
 *
 *    Description:  Program use to decrypt Vigenere cypher. 
 *
 *        Version:  1.0
 *        Created:  09/11/2012 10:45:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthieu Keller (keller.mdpa@gmail.com)
 *   Organization:  ENSTA-ParisTech
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 * =====================================================================================
 */

#include "vigenere.h"

/* Return the char string corresponding to the file size */
char* read_file (char* my_file, long* length)
{
	printf("Reading the file \n \n");
	/*  opening the file */
	FILE* file = fopen (my_file, "r"); 

	char* my_string = NULL;
	*length = 0;

	/*  variables for reading the file */
	int char_read = 0;
	int offset = 0;

	if (file != NULL)
	{
		/*  we get the file size  */
		fseek (file, 0, SEEK_END);
		*length = ftell (file);
		rewind(file);

		/*  we print the size of the file for the user */
		printf("the file is %li characters long. \n", *length);

		/*  allocation of the string size */
		my_string = (char*) malloc(*length);

		/*  read the file */
		while (!feof(file))
		{
			char_read = fread(&my_string[offset], sizeof(char), 100, file);
			offset += char_read;
		}
		/*  closing the file */
		fclose (file);
	}
	return my_string;
}

/*  method used to compute the coincidence of a substring */
double compute_coincidence (int *tab, int s_length)
{
	/* sum of the "frequency" of each alphabet letter */
	int k;		
	double sum = -1;
	for (k=0; k < ALPHABET_SIZE ; k++)
	{
		sum += tab[k]*(tab[k]-1);
	}

	/*  return the coincidence */
	return sum / ((s_length-1)*s_length);
}

/*  method used to compute the mutual coincidence of two substrings with an offset g */
double compute_mutual_coincidence(int *tab, int *tab2, int s_length, int g)
{
	/* sum of the "frequency" of each alphabet letter with the offset g */
	double sum = -1;
	int k;
	for (k=0; k < ALPHABET_SIZE; k++)
	{
		sum += tab[k]*tab2[(k+g)%26];
	}

	/*  return the  mutual coincidence */
	return sum / (s_length*s_length);
}

/*  method used to decrypt the original message */
int decrypt (char* my_string, int length, char* key, int key_length)
{
	/*  parse all the original message */
	int i;
	for (i=0; i < length; i ++)
	{
		/*  use the key to decrypt the original message based on the vigenere cipher */
		int cara = 	(my_string[i]-ASCII_MAJ_OFFSET)-(key[i%key_length]-ASCII_MAJ_OFFSET); 	
		if (cara < 0)
		{
			cara +=26;
		}
		/*  we just print out the decrypted message in the console */
		printf ("%c" ,cara  + ASCII_MIN_OFFSET);
	}
	printf ("\n");

	return EXIT_SUCCESS;
}

/*  method used to find the index of the maximum in a table of int */
int find_index_max_tab (int* tab, int tab_size)
{
	int max = -1;
	int ret = -1;
	int i;
	/*  parse all the tab to find the index of its maximum */
	for (i=0; i < tab_size; i++)
	{
		if (tab[i]> max)
		{
			max = tab[i];
			ret = i;
		}
	}

	return ret;
}

/*  method used to show the key to the user */
int print_key (char* key, int key_length)
{
	printf("the key is : ");

	int i;
	/*  parse all the key and print it in the console */
	for (i=0; i < key_length; i++)
	{
		printf ("%c", key[i]);
	}

	printf("\n \n");

	return EXIT_SUCCESS;
}

/*  method used to reset a all tab to 0 */
int rez_tab (int *tab, int tab_length)
{
	int i;
	/*  parse all the tab and asign 0 */
	for (i =0; i < tab_length; i++)
	{
		tab[i]=0;
	}
	
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	char* my_string; /* pointer to the string to decrypt */

	int** frequencies; /* pointer to frequencies tabs pointers  */

	long length;

	/*  if a file is passed by parameter we read it*/
	if (argc >1)
	{
		my_string = read_file(argv[1], &length);
	}
	else
	{
		my_string = read_file ("my_chiffre.txt", &length);
	}

	/*  the file is empty or unreadable */ 
	if(length == 0)
	{
		printf ("Unable to get content or empty file. \nUsage : \n ./vigenere [FILE]  \n");	
		return EXIT_FAILURE;
	}

	 
	frequencies = (int**) malloc (sizeof(int*)*length); /*  there would be as much tabs as there is char in the file */

	frequencies [0] = (int*) malloc(sizeof(int)*ALPHABET_SIZE); /*  initialize the tab [0] */

	 
	/*  compute the coincidence for all subsequences */
	int m = 1;
	double coincidence = 0.0;
	while (coincidence < FRENCH_COINCIDENCE && m < length)
	{
		frequencies [m] = (int*) malloc(sizeof(int)*ALPHABET_SIZE); /*  initialize the tab [0] */

		int i;
		for (i = 0; i < m; i++)
			 {
				rez_tab(frequencies[i], ALPHABET_SIZE); /*  reset all frequencies tabs */
			 }
		int j;
		for (j = 0; j < length; j++)
		{
			int index = my_string[j]-ASCII_MAJ_OFFSET;
			if ( index < ALPHABET_SIZE && index >=0) 
			{
				frequencies[j%(m)] [index]+=1; /*  increment the frequency of the letter */
			}
		}
		
		/*  compute the coincidence for the subsequences */
		coincidence = 0.0;
		for (j = 0; j < m; j++)
		{
			coincidence += compute_coincidence(frequencies[j%m], length/m) / m;
		}
		
		m++;
	}
	m--; /* undo the last m increment */

	/*  print the key length and the coincidence associated */
	printf("The key length is %i char with a coincidence of %f. \n \n", m, coincidence);

	/*  'offsets is the offset b/w the first letter and the letter i of the key */
	int* offsets = (int*) malloc(sizeof(int)*m);

	int i;
	/*  we compute this offset by computing the mutual coincidence of the first
	 *  subsequence and the others */
	for (i=0; i< m; i++)
	{
		double mutual_coincidence = 0;
		int g =0;
		while (mutual_coincidence < FRENCH_COINCIDENCE && g < ALPHABET_SIZE)
		{
			/*  compute the mutual coincidence according to its formula */
			mutual_coincidence = compute_mutual_coincidence (frequencies[0], frequencies[i], length/m, g);
			g++;
		}
		g--; /* undo the last g increment */

		offsets[i] = g;
	}	

	char* key = (char*) malloc(sizeof(char)*m);
	/*  the fist key letter is get by "moving" the most frequent letter in the first subsequence */
	key [0] = find_index_max_tab(frequencies[0], ALPHABET_SIZE)- MOST_USE_LETTER + ASCII_MAJ_OFFSET;

	/*  we know the first letter and the offset b/w it and the other letter
	 *  we compute the all key.*/
	for (i = 1; i < m; i++)
	{
		key[i] = ((key[0] - ASCII_MAJ_OFFSET)+ offsets[i]) %ALPHABET_SIZE + ASCII_MAJ_OFFSET;
	}

	/*  print the key for the user */
	print_key (key, m);

	printf ("Decrypting the file : \n");

	/*  we know the key, we decrypt the original file */
	decrypt (my_string, length, key, m);	
	 
	/*  free the used memory */
	for (i =0; i< m; i++)
	{
		free(frequencies[i]);
	}
	free(frequencies);
	free(key);
	free(offsets);
	free (my_string);


	return EXIT_SUCCESS;
}

