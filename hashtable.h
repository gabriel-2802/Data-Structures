/* copyright Carauleanu Valentin Gabriel 311Cab 2023 */
#pragma once
#include "ll_lists.h"
#include "utils.h"
#define MAX_STRING_SIZE 256
#define HMAX 200

typedef struct {
	void *key;
	void *value;
} info_t;

typedef struct  {
	ll_list_t **buckets;
	/* Array de liste simplu-inlantuite. */
	/* Nr. total de noduri existente curent in toate bucket-urile */
	unsigned int size;
	unsigned int hmax; /* Nr. de bucket-uri. */
	/* (Pointer la) Functie pentru a calcula valoarea hash asociata cheilor */
	unsigned int (*hash_function)(void *);
	/* (Pointer la) Functie pentru a compara doua chei. */
	int (*compare_function)(void *, void *);
	/* (Pointer la) Functie pentru a elibera memoria ocupata de cheie si
	 	valoare. */
	void (*key_val_free_function)(void *);
} hashtable_t;

/* functia compara 2 int-uri */
int compare_function_ints(void *a, void *b);

/* functia compara 2 string-uri */
int compare_function_strings(void *a, void *b);

/* functie de hash pentru int data type */
unsigned int hash_function_int(void *a);

/* functie de hash pentru string-uri */
unsigned int hash_function_string(void *a);

/* functie de eliberare cheie - valoare */
void key_val_free_function(void *data);

/* functia creeaza un hashtable cu parametrii primiti */
hashtable_t *ht_create(unsigned int hmax, unsigned int (*hash_function)(void *),
			   int (*compare_function)(void *, void *),
			   void (*key_val_free_function)(void *));

/* functia verifica daca ht are cheia primita ca parametru */
int ht_has_key(hashtable_t *ht, void *key);

/* functia returneaza valoarea corespunzatoare cheii key */
void *ht_get(hashtable_t *ht, void *key);

/* functia adauga in ht perechea key - value */
void ht_put(hashtable_t *ht, void *key, unsigned int key_size, void *value,
		unsigned int value_size);

/* functia sterge din ht perechea key - value */
void ht_remove_entry(hashtable_t *ht, void *key);

/* functia elibereaza memoria alocata ht*/
void ht_free(hashtable_t *ht);

/* functia returneaza nr de perechi din ht */
unsigned int ht_get_size(hashtable_t *ht);

/* functia returneaza nr maxim de bucket-uri din ht*/
unsigned int ht_get_hmax(hashtable_t *ht);