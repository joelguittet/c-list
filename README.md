# c-list

[![CI Badge](https://github.com/joelguittet/c-list/workflows/ci/badge.svg)](https://github.com/joelguittet/c-list/actions)
[![Issues Badge](https://img.shields.io/github/issues/joelguittet/c-list)](https://github.com/joelguittet/c-list/issues)
[![License Badge](https://img.shields.io/github/license/joelguittet/c-list)](https://github.com/joelguittet/c-list/blob/master/LICENSE)

[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=joelguittet_c-list&metric=bugs)](https://sonarcloud.io/dashboard?id=joelguittet_c-list)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=joelguittet_c-list&metric=code_smells)](https://sonarcloud.io/dashboard?id=joelguittet_c-list)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=joelguittet_c-list&metric=duplicated_lines_density)](https://sonarcloud.io/dashboard?id=joelguittet_c-list)
[![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=joelguittet_c-list&metric=ncloc)](https://sonarcloud.io/dashboard?id=joelguittet_c-list)
[![Vulnerabilities](https://sonarcloud.io/api/project_badges/measure?project=joelguittet_c-list&metric=vulnerabilities)](https://sonarcloud.io/dashboard?id=joelguittet_c-list)

[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=joelguittet_c-list&metric=sqale_rating)](https://sonarcloud.io/dashboard?id=joelguittet_c-list)
[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=joelguittet_c-list&metric=reliability_rating)](https://sonarcloud.io/dashboard?id=joelguittet_c-list)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=joelguittet_c-list&metric=security_rating)](https://sonarcloud.io/dashboard?id=joelguittet_c-list)

Provide lists support in C.

## Features

*   add and remove elements of any type at head or tail of the list
*   elements of the list as a copy or reference
*   optionally sort elements of the list using custom rules

## Building

On Linux/Windows build `liblist.so`/`list.dll` with the following commands:

``` bash
cmake -B build .
cmake --build build
```

## Installing

On Linux install `liblist.so` with the following commands:

``` bash
make install
```

## Examples

Build examples with the following commands:

``` bash
cmake -B build -DENABLE_LIST_EXAMPLES=ON .
cmake --build build
```

### list_sort

Add string elements to a list and sort them alphabetically.

## Performances

Performances have not been evaluated yet.

## What's it good for?

This goal of this library is to provide a C implementation to provide list support. This can be used in replacement of arrays in various contexts.

## API

### list_t *list_create(bool alloc, bool (*sort)(list_t *, void *, void *))

Create a new list. Set `alloc` to create copies of the values when `list_add_head` and `list_add_tail` are called.

The optional `sort` callback should be defined to perform ordering of the elements in the list when `list_add` is called. `sort` callback should returns true if the new element should be added before the current element, false otherwise.

### int list_add(list_t *list, void *e, size_t size)

Add element `e` of size `size` to the `list`. Element is added by default at the end of the list, except if the `sort` callback is used.

### int list_add_head(list_t *list, void *e, size_t size)

Add element `e` of size `size` to the head of the `list`.

### int list_add_tail(list_t *list, void *e, size_t size)

Add element `e` of size `size` to the tail of the `list`.

### size_t list_get_count(list_t *list)

Return the number of elements in the `list`.

### void *list_get_head(list_t *list)

Get head element of the `list`.

### void *list_get_tail(list_t *list)

Get tail element of the `list`.

### void *list_get_next(list_t *list)

Get next element of the `list`.

### void *list_get_prev(list_t *list)

Get previous element of the `list`.

### void *list_remove(list_t *list, void *e)

Remove element `e` of the `list`.

### void *list_remove_head(list_t *list)

Remove head element of the `list`.

### void *list_remove_tail(list_t *list)

Remove tail element of the `list`.

### void list_release(list_t *list)

Release the list. Must be called to free ressources.

## License

MIT
