/**
 * @file      list_sort.c
 * @brief     List example in C
 *
 * MIT License
 *
 * Copyright joelguittet and c-list contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/******************************************************************************/
/* Includes                                                                   */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#if !defined(WIN32) && !defined(WIN64) && !defined(_MSC_VER) && !defined(_WIN32)
#include <unistd.h>
#endif
#include <string.h>
#include <assert.h>
#include <signal.h>

#include "list.h"

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

/**
 * Sort element of the list
 * @param curr Current element in the list
 * @param e New element to be added in the list
 * @return true if the new element should be added before the current element, false otherwise
 */
static bool sort(list_t *l, void *curr, void *e);

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/**
 * @brief Main function
 * @param argc Number of arguments
 * @param argv Arguments
 * @return Always returns 0
 */
int
main(int argc, char **argv) {

    list_t *list;

    /* Create list instance */
    if (NULL == (list = list_create(false, sort))) {
        printf("unable to create list instance\n");
        exit(EXIT_FAILURE);
    }

    /* Add elements to the list */
    list_add(list, "element2", sizeof(char *));
    list_add(list, "element3", sizeof(char *));
    list_add(list, "element1", sizeof(char *));

    /* Print elements of the list */
    char *str = list_get_head(list);
    while (NULL != str) {
        printf("%s\n", str);
        str = list_get_next(list);
    }

    /* Release memory */
    list_release(list);

    return 0;
}

/**
 * Sort element of the list
 * @param curr Current element in the list
 * @param e New element to be added in the list
 * @return true if the new element should be added before the current element, false otherwise
 */
static bool
sort(list_t *l, void *curr, void *e) {

    /* Elements are ordered alphabetically by name */
    return (strcmp((char *)curr, (char *)e) < 0) ? true : false;
}
