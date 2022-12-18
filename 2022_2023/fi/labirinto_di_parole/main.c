#define FILE_NAME_LEN 50
#define QUIT "0"
#define LOW_MIN 'a'
#define LOW_MAX 'z'
#define MENU_EXIT '0'
#define MENU_VIS '1'
#define MENU_SOL '2'
#define MENU_NEW '3'
#define MENU_FIND '4'
#define MIN_WORD 4
#define LEN_ALP ('z' - 'a' + 1)
#define CHAR_CHANGE_MAX 1
#define CHAR_ADD_MAX 1

#define ARE_SIMILAR(w1, w2)                                                           \
  (is_anagram((w1), (w2)) || is_char_change((w1), (w2)) || is_char_add((w1), (w2)) || \
   is_char_del((w1), (w2)))

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "wlist.h"

char new_game(void);
wlist_t *make_list(FILE *);
char is_valid(char[]);
char load_game(wlist_t *);
void print_menu(void);
char check_solution(wlist_t *, wlist_t *);
char is_anagram(char[], char[]);
char is_char_change(char[], char[]);
char is_char_add(char[], char[]);
char is_char_del(char[], char[]);
void clean_buffer(void);
void print_solution(wlist_t *);
char find_solution_recursive(wlist_t *, wlist_t *, wlist_t *);

int main(void) {
  char exit;

  do {
    exit = new_game();
  } while (!exit);

  return 0;
}

char new_game(void) {
  char file_name[FILE_NAME_LEN + 1];
  char exit, opened;
  FILE *input;
  wlist_t *original;

  printf("\nEnter file name, or %s to exit\n>> ", QUIT);
  scanf("%s", file_name);
  clean_buffer();

  opened = 0;
  while (!opened && !(exit = !strcmp(file_name, QUIT))) {
    if ((input = fopen(file_name, "r")))
      if ((original = make_list(input)))
        opened = 1;
      else
        printf("File %s contains invalid characters\n", file_name);
    else
      printf("File %s not found.\n", file_name);

    if (!opened) {
      printf("\nEnter file name, or %s to exit\n>> ", QUIT);
      scanf("%s", file_name);
      clean_buffer();
    }
  }

  if (!exit) {
    exit = load_game(original);
    list_free(original);
  }

  return exit;
}

wlist_t *make_list(FILE *file) {
  wlist_t *list = NULL;
  int count;
  char s[WORD_LEN + 1];

  count = 0;
  while (fscanf(file, "%s", s) > 0 && is_valid(s)) {
    list = list_append(list, s);
    count++;
  }

  if (!feof(file)) {
    printf("%s is not a valid word\n", s);
    list_free(list);
  } else if (count < MIN_WORD)
    printf("%d words: insert at least %d\n", count, MIN_WORD);

  return list;
}

char is_valid(char s[]) {
  char res, low;
  int i;

  res = 1;
  for (i = 0; s[i] && res; i++) {
    low = tolower(s[i]);
    if (low < LOW_MIN || low > LOW_MAX) res = 0;
  }

  return res;
}

char load_game(wlist_t *original) {
  char exit, choice, restart;
  char file_name[FILE_NAME_LEN];
  FILE *file;
  wlist_t *solution;

  exit = 0;
  restart = 0;
  do {
    print_menu();
    scanf("%c", &choice);
    clean_buffer();
    switch (choice) {
      case MENU_VIS:
        list_printf(original);
        break;
      case MENU_SOL:
        printf("Insert file name\n>> ");
        scanf("%s", file_name);
        clean_buffer();
        if ((file = fopen(file_name, "r"))) {
          if ((solution = make_list(file))) {
            if (check_solution(original, solution)) {
              printf("\nCorrect solution!\n");
              restart = 1;
            } else
              printf("\nWrong solution!\n");
            list_free(solution);
          }
        } else
          printf("\nFile %s not found.\n", file_name);
        break;
      case MENU_NEW:
        restart = 1;
        break;
      case MENU_EXIT:
        exit = 1;
        break;
      case MENU_FIND:
        print_solution(original);
        restart = 1;
        break;
      default:
        printf("\nNot a valid input!\n");
    }
  } while (!exit && !restart);

  return exit;
}

void print_menu(void) {
  printf("\n");
  printf("%c. view word list\n", MENU_VIS);
  printf("%c. check a solution\n", MENU_SOL);
  printf("%c. insert new sequence\n", MENU_NEW);
  printf("%c. find the solution\n", MENU_FIND);
  printf("%c. exit\n", MENU_EXIT);
  printf(">> ");
}

char check_solution(wlist_t *original, wlist_t *solution) {
  char res;
  wlist_t *copy;

  if (strcmp(solution->word, original->word) ||
      strcmp(list_tail(solution)->word, list_tail(original)->word)) {
    res = 0;
  } else {
    res = 1;
    copy = list_copy(original);
    while (solution->next && res) {
      res = (ARE_SIMILAR(solution->word, solution->next->word));
      if (res) {
        res = list_del(&copy, solution->word);
      }
      solution = solution->next;
    }
    if (res) {
      res = list_del(&copy, original->word);
      if (copy) res = 0;
    }

    list_free(copy);
  }

  return res;
}

char is_anagram(char s[], char t[]) {
  char map1[LEN_ALP], map2[LEN_ALP];
  char res;
  int i;

  memset(map1, 0, LEN_ALP);
  memset(map2, 0, LEN_ALP);

  for (i = 0; s[i] && t[i]; i++) {
    map1[tolower(s[i]) - LOW_MIN]++;
    map2[tolower(t[i]) - LOW_MIN]++;
  }

  res = !(s[i] || t[i]);
  for (i = 0; i < LEN_ALP && res; i++) res = (map1[i] == map2[i]);

  return res;
}

char is_char_change(char s[], char t[]) {
  int i, count;

  count = 0;
  for (i = 0; s[i] && t[i] && count <= CHAR_CHANGE_MAX; i++) {
    count += (tolower(s[i]) != tolower(t[i]));
  }

  return (count <= CHAR_CHANGE_MAX && !s[i] && !t[i]);
}

char is_char_add(char s[], char t[]) {
  int i, delta;

  delta = 0;
  for (i = 0; s[i] && t[i + delta] && delta <= CHAR_ADD_MAX; i++) {
    if (tolower(s[i]) != tolower(t[i + delta])) {
      delta++;
      i--;
    }
  }

  while (t[i + delta] && delta <= CHAR_ADD_MAX) {
    delta++;
  }
  return (delta <= CHAR_ADD_MAX && !(s[i] || t[i + delta]));
}

char is_char_del(char s[], char t[]) { return is_char_add(t, s); }

void clean_buffer(void) {
  while (getchar() != '\n')
    ;
}

void print_solution(wlist_t *original) {
  wlist_t *start = NULL, *end = NULL, *remaning = NULL;

  remaning = list_copy(original);
  start = list_pop_head(&remaning);
  start->next = NULL;
  end = list_pop_tail(&remaning);
  end->next = NULL;
  if ((find_solution_recursive(start, end, remaning))) {
    list_printf(start);
    list_free(start);
  } else {
    printf("\nSolution does not exists\n");
    list_free(start);
    list_free(end);
    list_free(remaning);
  }
}

char find_solution_recursive(wlist_t *start, wlist_t *end, wlist_t *remaning) {
  char ris;
  wlist_t *elem, *prev;

  ris = 0;
  if (!remaning) {
    if (ARE_SIMILAR(start->word, end->word)) {
      start->next = end;
      ris = 1;
    }
  } else {
    if (ARE_SIMILAR(start->word, remaning->word)) {
      elem = list_pop_head(&remaning);
      elem->next = NULL;
      ris = find_solution_recursive(elem, end, remaning);
      if (ris) {
        start->next = elem;
      } else {
        elem->next = remaning;
        remaning = elem;
      }
    }
    prev = remaning;
    while (!ris && (elem = prev->next)) {
      if (ARE_SIMILAR(start->word, elem->word)) {
        prev->next = elem->next;
        elem->next = NULL;
        ris = find_solution_recursive(elem, end, remaning);
        if (ris) {
          start->next = elem;
        } else {
          elem->next = prev->next;
          prev->next = elem;
        }
      }
      prev = elem;
    }
  }

  return ris;
}
