/*
 * Binárny vyhľadávací strom — iteratívna varianta
 *
 * S využitím dátových typov zo súboru btree.h, zásobníkov zo súborov stack.h a
 * stack.c a pripravených kostier funkcií implementujte binárny vyhľadávací
 * strom bez použitia rekurzie.
 */

#include "../btree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializácia stromu.
 *
 * Užívateľ musí zaistiť, že incializácia sa nebude opakovane volať nad
 * inicializovaným stromom. V opačnom prípade môže dôjsť k úniku pamäte (memory
 * leak). Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je
 * možné toto detegovať vo funkcii.
 */
void bst_init(bst_node_t **tree) 
{
  if (tree != NULL)
  {
  (*tree) = NULL;
  }
  else
  {
   return;
  }
}

/*
 * Nájdenie uzlu v strome.
 *
 * V prípade úspechu vráti funkcia hodnotu true a do premennej value zapíše
 * hodnotu daného uzlu. V opačnom prípade funckia vráti hodnotu false a premenná
 * value ostáva nezmenená.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
bool bst_search(bst_node_t *tree, char key, int *value) 
{
  while (tree != NULL)
  {
    if (tree->key < key)
    {
      tree = tree->right;
    }
    else if (tree->key > key)
    {
      tree = tree->left;
    }
    else if (tree->key == key)
    {
      *value = tree->value;
      return true;
    }
  }
  return false;
}

/*
 * Vloženie uzlu do stromu.
 *
 * Pokiaľ uzol so zadaným kľúčom v strome už existuje, nahraďte jeho hodnotu.
 * Inak vložte nový listový uzol.
 *
 * Výsledný strom musí spĺňať podmienku vyhľadávacieho stromu — ľavý podstrom
 * uzlu obsahuje iba menšie kľúče, pravý väčšie.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_insert(bst_node_t **tree, char key, int value) 
{
  
  if (*tree != NULL)
  {
    bst_node_t *insert_element = *tree;
  while (insert_element != NULL)
  {
    if (insert_element->key == key)
     {
       insert_element->value = value;
       return;
     }
    if (insert_element->key > key)
    {
      if (insert_element->left == NULL)
      {
        insert_element->left = malloc(sizeof(bst_node_t));
        insert_element->left->key = key;
        insert_element->left->value = value;
        insert_element->left->left = NULL;
        insert_element->left->right = NULL;
        return;
      }
      else
      {
        insert_element = insert_element->left;
      }
    }
    else 
    {
      if (insert_element->right == NULL)
      {
        insert_element->right = malloc(sizeof(bst_node_t));
        insert_element->right->key = key;
        insert_element->right->value = value;
        insert_element->right->left = NULL;
        insert_element->right->right = NULL;
        return;
      }
      else
      {
        insert_element = insert_element->right;
      }
    }
  }
  }
  else 
  {
    (*tree) = malloc(sizeof(bst_node_t));
    (*tree)->key = key;
    (*tree)->value = value;
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    return;
  }
  
}

/*
 * Pomocná funkcia ktorá nahradí uzol najpravejším potomkom.
 *
 * Kľúč a hodnota uzlu target budú nahradené kľúčom a hodnotou najpravejšieho
 * uzlu podstromu tree. Najpravejší potomok bude odstránený. Funkcia korektne
 * uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkcia predpokladá že hodnota tree nie je NULL.
 *
 * Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) 
{
  if(*tree == NULL) 
  {
    return;
  }
  else 
  {
    bst_node_t *right_tree = *tree;
    bst_node_t *help = NULL;
    if (right_tree->right == NULL)
    {
      return;
    }
     while(right_tree->right->right != NULL)
     {
       right_tree = right_tree->right;
     }
     target->key = right_tree->right->key;
     target->value = right_tree->right->value;
     help = right_tree->right->left;
     free(right_tree->right);
     right_tree->right = NULL;
     right_tree->right = help;
  }
}

/*
 * Odstránenie uzlu v strome.
 *
 * Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí.
 * Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla.
 * Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom
 * ľavého podstromu. Najpravejší uzol nemusí byť listom!
 * Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkciu implementujte iteratívne pomocou bst_replace_by_rightmost a bez
 * použitia vlastných pomocných funkcií.
 */
void bst_delete(bst_node_t **tree, char key) 
{
  if(*tree != NULL)
    {
        bool stop = false;
        bst_node_t *delete_element = (bst_node_t *) malloc(sizeof (bst_node_t));
        bst_node_t *prev_delet_element = (bst_node_t *) malloc(sizeof (bst_node_t));

        delete_element = *tree;
        while ((!stop) && (delete_element != NULL))
        {
          if(key < delete_element->key)
          {
            prev_delet_element = delete_element;
            delete_element = delete_element->left;
          }
          else if(key > delete_element->key)
            {
                prev_delet_element = delete_element;
                delete_element = delete_element->right;
            } else
            {
                stop = true;
                if((!delete_element->right) && (!delete_element->left)) 
                {
                  if(prev_delet_element == NULL)
                  {
                    (*tree) = NULL;
                  }

                  else  if(prev_delet_element->left == delete_element)
                    {
                        prev_delet_element->left = NULL;
                    } else
                    {
                        prev_delet_element->right = NULL;
                    }
                    free(delete_element);
                    delete_element = NULL;

                } else if((delete_element->right != NULL) && delete_element->left != NULL)    
                {
                    bst_replace_by_rightmost(delete_element, &(delete_element->left));
                } else
                {

                    if(delete_element->left == NULL)                             
                    {
                        if (delete_element == prev_delet_element->left)
                        {
                          prev_delet_element->left = delete_element->right;
                        }
                        else
                        {
                          prev_delet_element->right = delete_element->right;
                        }
                    } else                                                        
                    {
                        if (delete_element == prev_delet_element->left)
                        {
                          prev_delet_element->left = delete_element->left;
                        }
                        else
                        {
                          prev_delet_element->right = delete_element->left;
                        }
                    }

                    free(delete_element);

                    delete_element = NULL;

                }
            }
        }
    }
}

/*
 * Zrušenie celého stromu.
 *
 * Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po
 * inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených
 * uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_dispose(bst_node_t **tree) 
{

}

/*
 * Pomocná funkcia pre iteratívny preorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu.
 * Nad spracovanými uzlami zavola bst_print_node a uloží ich do zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit) 
{
  while (tree != NULL)
    {
        stack_bst_push(to_visit, tree);
        bst_print_node(tree);
        tree = tree->left;
    }
}

/*
 * Preorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_preorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_preorder(bst_node_t *tree) 
{
  stack_bst_t stack;
  stack_bst_init(&stack);
  bst_leftmost_preorder(tree, &stack);
  while (!stack_bst_empty(&stack))
  {
    tree = stack_bst_top(&stack);
    stack_bst_pop(&stack);
    bst_leftmost_preorder(tree->right, &stack);
  }
}

/*
 * Pomocná funkcia pre iteratívny inorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) 
{
  while (tree != NULL)
  {
    stack_bst_push(to_visit, tree);
    tree = tree->left;
  }
}

/*
 * Inorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_inorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_inorder(bst_node_t *tree) 
{
  stack_bst_t stack;
  stack_bst_init(&stack);
  bst_leftmost_inorder(tree, &stack);
  while (!stack_bst_empty(&stack))
  {
    tree = stack_bst_top(&stack);
    stack_bst_pop(&stack);
    bst_print_node(tree);
    bst_leftmost_inorder(tree->right, &stack);
  }
}

/*
 * Pomocná funkcia pre iteratívny postorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov. Do zásobníku bool hodnôt ukladá informáciu že uzol
 * bol navštívený prvý krát.
 *
 * Funkciu implementujte iteratívne pomocou zásobníkov uzlov a bool hodnôt a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit,stack_bool_t *first_visit) 
{
  while (tree != NULL)
  {
    stack_bst_push(to_visit, tree);
    stack_bool_push(first_visit, true);
    tree = tree->left;
  }
}

/*
 * Postorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_postorder a
 * zásobníkov uzlov a bool hodnôt bez použitia vlastných pomocných funkcií.
 */
void bst_postorder(bst_node_t *tree) 
{
  stack_bst_t stack;
  stack_bst_init(&stack);
  bool from_left;
  stack_bool_t stack_B;
  stack_bool_init(&stack_B);
  bst_leftmost_postorder(tree, &stack, &stack_B);
  while (!stack_bst_empty(&stack))
  {
    tree = stack_bst_top(&stack);
    from_left = stack_bool_top(&stack_B);
    stack_bool_pop(&stack_B);
    if (from_left)
    {
      stack_bool_push(&stack_B, false);
      bst_leftmost_postorder(tree->right, &stack, &stack_B);
    }
    else 
    {
      stack_bst_pop(&stack);
      bst_print_node(tree);
    }
  }
}
