#include "BigInteger.h"
#include <stdio.h>
#include <stdlib.h>

struct node *insert_head(struct node *head, int data) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->data = data;
  temp->next = head;
  return temp;
}

void add_node(struct BigInteger *n, int val) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->data = val;
  temp->next = NULL;
  n->length += 1;
  if (n->head == NULL) {
    n->head = temp;
    return;
  }
  struct node *itr = n->head;
  while (itr->next != NULL) {
    itr = itr->next;
  }
  itr->next = temp;
}

long int get_length(struct node *head) {
  long int count = 0;
  while (head) {
    head = head->next;
    count++;
  }
  return count;
}

void print_reverse(struct node *list) {
  if (!list)
    return;
  print_reverse(list->next);
  printf("%d", list->data);
}

void display(struct BigInteger bi) {
  if (bi.head == NULL) {
    printf("0");
    return;
  }
  print_reverse(bi.head);
}

struct BigInteger initialize(char *s) {
  struct BigInteger b;
  b.head = NULL;
  for (int i = 0; s[i] != '\0'; i++) {
    b.head = insert_head(b.head, s[i] - '0');
  }
  b.length = get_length(b.head);
  return b;
}

struct node *reverse_list(struct node *head) {
  struct node *back = NULL, *front = NULL, *current = head;
  while (current != NULL) {
    front = current->next;
    current->next = back;
    back = current;
    current = front;
  }
  return back;
}

int compare_big_integers(struct BigInteger num1, struct BigInteger num2) {
  if (num2.length > num1.length) {
    return -1;
  } else if (num2.length == num1.length) {
    int return_val = 0;
    num1.head = reverse_list(num1.head);
    num2.head = reverse_list(num2.head);
    struct node *head1 = num1.head, *head2 = num2.head;
    while (head1 != NULL && head2 != NULL) {
      if (head2->data > head1->data) {
        return_val = -1;
        break;
      } else if (head1->data > head2->data) {
        return_val = 1;
        break;
      }
      head1 = head1->next;
      head2 = head2->next;
    }
    num1.head = reverse_list(num1.head);
    num2.head = reverse_list(num2.head);
    return return_val;
  }
  return 1;
}
struct BigInteger add(struct BigInteger num1, struct BigInteger num2) {
  struct BigInteger sum;
  sum.head = NULL;
  sum.length = 0;

  struct node *l1 = num1.head, *l2 = num2.head;
  int result, carry = 0;

  while (l1 != NULL || l2 != NULL || carry != 0) {
    int d1 = (l1 != NULL) ? l1->data : 0;
    int d2 = (l2 != NULL) ? l2->data : 0;

    result = d1 + d2 + carry;
    carry = result / 10;
    add_node(&sum, result % 10);

    if (l1 != NULL)
      l1 = l1->next;
    if (l2 != NULL)
      l2 = l2->next;
  }
  sum.length = get_length(sum.head);
  return sum;
}
struct BigInteger sub(struct BigInteger num1, struct BigInteger num2) {
  struct BigInteger diff;
  diff.head = NULL;
  diff.length = 0;

  if (compare_big_integers(num1, num2) == -1) {
    struct BigInteger temp = num1;
    num1 = num2;
    num2 = temp;
  }

  struct node *l1 = num1.head, *l2 = num2.head;
  int difference, borrow = 0;

  while (l1 != NULL || l2 != NULL) {
    int d1 = (l1 != NULL) ? l1->data : 0;
    int d2 = (l2 != NULL) ? l2->data : 0;

    difference = d1 - d2 - borrow;

    if (difference < 0) {
      difference += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    add_node(&diff, difference);

    if (l1 != NULL)
      l1 = l1->next;
    if (l2 != NULL)
      l2 = l2->next;
  }
  diff.head = reverse_list(diff.head);
  while (diff.head != NULL && diff.head->data == 0) {
    struct node *temp = diff.head;
    diff.head = diff.head->next;
    free(temp);
  }
  diff.head = reverse_list(diff.head);
  diff.length = get_length(diff.head);
  return diff;
}
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2) {
  struct node *n1 = num1.head, *n2 = num2.head;
  struct BigInteger num3 = initialize("");
  num3.length = 0;
  if (n1 == NULL || n2 == NULL) {
    return num3;
  }
  struct BigInteger mid, result = initialize("");
  int carry = 0, product = 0, i = 0;
  while (n2 != NULL) {
    n1 = num1.head;
    carry = 0;
    mid = initialize("");
    for (int j = 0; j < i; j++) {
      add_node(&mid, 0);
    }
    while (n1 != NULL) {
      product = (n1->data) * (n2->data) + carry;
      add_node(&mid, product % 10);
      carry = product / 10;
      n1 = n1->next;
    }

    if (carry > 0) {
      add_node(&mid, carry);
    }

    result = add(mid, result);
    struct node *current = mid.head;
    while (current != NULL) {
      struct node *temp = current;
      current = current->next;
      free(temp);
    }

    n2 = n2->next;
    i++;
  }
  return result;
}

struct BigInteger div1(struct BigInteger num1, struct BigInteger num2) {
  struct BigInteger div = initialize("0");
  div.length = 0;
  int flag = 0;
  if (num2.length == 1 && num2.head->data == 0) {
    printf("Error division by zero");
    return div;
  }
  struct BigInteger sum = add(num2, initialize("0"));
  while (compare_big_integers(num1, sum) >= 0) {
    sum = add(sum, num2);
    div = add(div, initialize("1"));
    flag = 1;
  }
  return div;
}

struct BigInteger mod(struct BigInteger num1, struct BigInteger num2) {
  struct BigInteger modulus = initialize("0");
  modulus.length = 0;
  int flag = 0;
  if (num2.length == 1 && num2.head->data == 0) {
    printf("Error division by zero");
    return modulus;
  }
  struct BigInteger temp = add(num2, initialize("0"));
  while (compare_big_integers(num1, temp) >= 0) {
    temp = add(temp, num2);
    modulus = add(modulus, initialize("1"));
  }
  struct BigInteger temp2 = sub(temp, num2);
  struct BigInteger result = sub(num1, temp2);
  return result;
}
