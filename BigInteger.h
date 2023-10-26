#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include <stdio.h>
#include <stdlib.h>
struct node {
  int data;
  struct node *next;
};
struct BigInteger {
  struct node *head;
  long int length;
};
struct node *insert_head(struct node *head, int data);
void add_node(struct BigInteger *n, int val);
long int get_length(struct node *head);
void print_reverse(struct node *list);
void display(struct BigInteger bi);
struct BigInteger initialize(char *s);
struct node *reverse_list(struct node *head);
int compare_big_integers(struct BigInteger num1, struct BigInteger num2);
struct BigInteger add(struct BigInteger num1, struct BigInteger num2);
struct BigInteger sub(struct BigInteger num1, struct BigInteger num2);
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2);
struct BigInteger div1(struct BigInteger num1, struct BigInteger num2);
struct BigInteger mod(struct BigInteger num1, struct BigInteger num2);
void freeList(struct BigInteger *num);

#endif // BIG_INTEGER_H
