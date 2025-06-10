#include <stdio.h>
#include <string.h>

// Structure representing a record
typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int status;
  int code;
} Record;

int main() {
  char file_path[100] = "../";
  char tmp_path[100];
  char search_date[11];

  if (scanf("%99s", tmp_path) != 1) {
    printf("n/a\n");
    return 1;
  }
  strcat(file_path, tmp_path);

  FILE *file = fopen(file_path, "rb");
  if (!file) {
    printf("n/a\n");
    return 1;
  }

  if (scanf("%10s", search_date) != 1) {
    printf("n/a\n");
    fclose(file);
    return 1;
  }

  Record record;
  int found = 0;
  while (fread(&record, sizeof(Record), 1, file) == 1) {
    char date[11];
    snprintf(date, sizeof(date), "%02d.%02d.%04d", record.day, record.month,
             record.year);
    if (strcmp(date, search_date) == 0) {
      printf("%d\n", record.code);
      found = 1;
      break;
    }
  }

  fclose(file);

  if (!found) {
    printf("n/a\n");
  }

  return 0;
}