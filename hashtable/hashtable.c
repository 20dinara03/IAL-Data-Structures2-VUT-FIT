/*
 * Tabuľka s rozptýlenými položkami
 *
 * S využitím dátových typov zo súboru hashtable.h a pripravených kostier
 * funkcií implementujte tabuľku s rozptýlenými položkami s explicitne
 * zreťazenými synonymami.
 *
 * Pri implementácii uvažujte veľkosť tabuľky HT_SIZE.
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptyľovacia funkcia ktorá pridelí zadanému kľúču index z intervalu
 * <0,HT_SIZE-1>. Ideálna rozptyľovacia funkcia by mala rozprestrieť kľúče
 * rovnomerne po všetkých indexoch. Zamyslite sa nad kvalitou zvolenej funkcie.
 */
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}

/*
 * Inicializácia tabuľky — zavolá sa pred prvým použitím tabuľky.
 */
void ht_init(ht_table_t *table) 
{
  if (table == NULL) return;
  for (int i = 0; i < HT_SIZE; i++)
  {
    (*table)[i] = NULL;
  }
}

/*
 * Vyhľadanie prvku v tabuľke.
 *
 * V prípade úspechu vráti ukazovateľ na nájdený prvok; v opačnom prípade vráti
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) 
{
  if (table == NULL) return NULL;
  int identifier  = get_hash(key);
  ht_item_t *search_element = (*table)[identifier];
  while (search_element != NULL)
  {
    if (search_element->key == key)
    {
      return search_element;
    }
    else
    {
      search_element = search_element->next;
    }
  }
  return NULL;
}

/*
 * Vloženie nového prvku do tabuľky.
 *
 * Pokiaľ prvok s daným kľúčom už v tabuľke existuje, nahraďte jeho hodnotu.
 *
 * Pri implementácii využite funkciu ht_search. Pri vkladaní prvku do zoznamu
 * synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) 
{
  if (table == NULL) return;
  ht_item_t *search_element = ht_search(table, key);
  if (search_element == NULL)
  {
    ht_item_t *insert_element = malloc(sizeof(ht_item_t));
    int identifier = get_hash(key);
    if (insert_element == NULL)
    {
     return;
    } 
    else 
    {
      insert_element->key = key;
      insert_element->next = (*table)[identifier];
      insert_element->value = value;
      (*table)[identifier] = insert_element;
    }
  }
  else
  {
    search_element->value = value;
  }
}

/*
 * Získanie hodnoty z tabuľky.
 *
 * V prípade úspechu vráti funkcia ukazovateľ na hodnotu prvku, v opačnom
 * prípade hodnotu NULL.
 *
 * Pri implementácii využite funkciu ht_search.
 */
float *ht_get(ht_table_t *table, char *key) 
{
  if (table == NULL) return NULL;
  ht_item_t *search_element = ht_search(table,key);
  if (search_element == NULL)
  {
    return NULL;
  }
  else
  {
    return &(search_element->value);
  }
}

/*
 * Zmazanie prvku z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje priradené k danému prvku.
 * Pokiaľ prvok neexistuje, nerobte nič.
 *
 * Pri implementácii NEVYUŽÍVAJTE funkciu ht_search.
 */
void ht_delete(ht_table_t *table, char *key) 
{
  if (table == NULL) return;
  int identifier = get_hash(key);
  ht_item_t *delete_element = (*table)[identifier];
  if (delete_element == NULL) return;
  ht_item_t *prev_delete_element = NULL;
  while (delete_element != NULL)
  {
    ht_item_t * next_delete_element = delete_element->next;
    if (delete_element->key == key)
    {
      free(delete_element);
      if (prev_delete_element == NULL)
      {
        (*table)[identifier] =next_delete_element;
        return;
      }
      prev_delete_element->next = next_delete_element;
    }
    prev_delete_element = delete_element;
    delete_element = next_delete_element;
  }
}

/*
 * Zmazanie všetkých prvkov z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje a uvedie tabuľku do stavu po
 * inicializácii.
 */
void ht_delete_all(ht_table_t *table) 
{
  if (table == NULL) return;
  for (int i = 0; i < HT_SIZE; i++) 
  {
     while ((*table)[i] != NULL) 
    {
      ht_delete(table, (*table)[i]->key);
    }
  }
}
