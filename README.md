# Vigenere

This program was write during my studies in ENSTA a French engineering school.
It consist in a cryptanalysis of a Vigenere cypher.
It was first write in septembrer 2012.

## Use

In order to use the programme for decrypt FILE :
	-make
	-./vigenere [FILE]
In the case that there is no argument, we decrypt "my_chiffre.txt".
The file must have a particular format :  
	-The file must have no blank beetween letter
	-each letter must be Upper letter

## Present files

Chiffre.txt :
	It is an extract of "Deux cavalier de l'orage" from Jean Giono encrypted with the key 'JEANG'.

Chiffre_Pr.txt :
	It a text encrypt with the key 'PROUST'. It is an extract of "Du coté de chez Swann, A la Recherche du temps perdu" from Marcel Proust.

Chiffre_Sw.txt :
	It is the same text but encrypt with the key 'MARCO'.

my_chiffre.txt :
	It is an extract of "Toast Funebre" from Stephane Mallarme encrypted with the key 'MALLARME'

Vigenere_Singh.txt :
	It is "L'albatros, Spleen et idéal, les Fleurs du mal " a poem from Charles Baudelaire encrypted with the key 'SCUBA'

## Inside the code (see commentary for more informations) : 

- First of all we read the text and load it in memory.
- Then we compute the coincidence for i substrings incrementing i until the compute coincidence correspond to the French one. That give us the key length.
- Then we seek the offset between each key's letter by computing the mutual coincidence.
- Then we seek the first key letter by "moving" the most frequent letter in the first substring to the MOST_USE_LETTER. That give us the all key.
- Finally we just decrypt the initial encrypted text with the key and print it in the console.

