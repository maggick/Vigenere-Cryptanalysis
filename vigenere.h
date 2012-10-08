/*
 * =====================================================================================
 *
 *       Filename:  vigenere.h
 *
 *    Description:  Header for vigenere.c
 *
 *        Version:  1.0
 *        Created:  09/11/2012 04:38:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: Matthieu Keller (keller.mdpa@gmail.com)
 *   Organization: ENSTA-ParisTech
 *
 * =====================================================================================
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26 			/*  french alphabet size */
#define ASCII_MAJ_OFFSET 65 		/*  ascii offset for maj letters */
#define ASCII_MIN_OFFSET 97 		/*  ascii offset for min letters */
#define FRENCH_COINCIDENCE 0.071 	/*  french coincidence */
#define MOST_USE_LETTER 4 			/*  the most french use letter is 'e' */

char* read_file (char* my_file, long* length);
double compute_coincidence (int *tab, int s_length);
double compute_mutual_coincidence(int *tab, int *tab2, int s_length, int g);
int decrypt (char* my_string, int length, char* key, int key_length);
int find_index_max_tab (int* tab, int tab_size);
int print_key (char* key, int key_length);
int rez_tab (int *tab, int tab_length);

#endif 

