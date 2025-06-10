#include <stdio.h>
#include <stdlib.h>
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

// Function to compare two records for sorting
int compare_records(const void *a, const void *b) {
  const Record *record_a = (const Record *)a;
  const Record *record_b = (const Record *)b;

  if (record_a->year != record_b->year) {
    return record_a->year - record_b->year;
  }
  if (record_a->month != record_b->month) {
    return record_a->month - record_b->month;
  }
  if (record_a->day != record_b->day) {
    return record_a->day - record_b->day;
  }
  if (record_a->hour != record_b->hour) {
    return record_a->hour - record_b->hour;
  }
  if (record_a->minute != record_b->minute) {
    return record_a->minute - record_b->minute;
  }
  return record_a->second - record_b->second;
}

// Function to print a record
void print_record(const Record *record) {
  printf("%d %d %d %d %d %d %d %d\n", record->year, record->month, record->day,
         record->hour, record->minute, record->second, record->status,
         record->code);
}

// Function to input a record from stdin
int input_record(Record *new_record) {
  if (scanf("%d %d %d %d %d %d %d %d", &new_record->year, &new_record->month,
            &new_record->day, &new_record->hour, &new_record->minute,
            &new_record->second, &new_record->status, &new_record->code) != 8) {
    return 1;  // Indicate input error
  }

  // Validate the record fields
  if (new_record->year > 2023 || new_record->month < 1 || new_record->month > 12 ||
      new_record->day < 1 || new_record->day > 31 || new_record->hour < 0 ||
      new_record->hour > 23 || new_record->minute < 0 || new_record->minute > 59 ||
      new_record->second < 0 || new_record->second > 59 || new_record->status < 0 ||
      new_record->status > 1) {
    return 1;  // Indicate invalid data
  }

  return 0;  // Indicate success
}

int main() {
  char file_path[100] = "../";
  char tmp_path[100];

  if (scanf("%99s", tmp_path) != 1) {
    printf("n/a\n");
    return 1;
  }
  strcat(file_path, tmp_path);

  FILE *file = fopen(file_path, "r+b");
  if (!file) {
    printf("n/a\n");
    return 1;
  }

  int choice;
  if (scanf("%d", &choice) != 1) {
    printf("n/a\n");
    fclose(file);
    return 1;
  }

  if (choice == 0) {
    Record record;
    while (fread(&record, sizeof(Record), 1, file) == 1) {
      print_record(&record);
    }
  } else if (choice == 1 || choice == 2) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    int num_records = file_size / sizeof(Record);
    Record *records = malloc(num_records * sizeof(Record));

    if (!records) {
      printf("n/a\n");
      fclose(file);
      return 1;
    }

    if (fread(records, sizeof(Record), num_records, file) !=
        (size_t)num_records) {
      printf("n/a\n");
      free(records);
      fclose(file);
      return 1;
    }

    qsort(records, num_records, sizeof(Record), compare_records);

    if (choice == 2) {
      Record new_record;
      if (input_record(&new_record) == 0) {
        // Resize records array to accommodate the new record
        records = realloc(records, (num_records + 1) * sizeof(Record));
        if (!records) {
          printf("n/a\n");
          free(records);
          fclose(file);
          return 1;
        }
        records[num_records] = new_record;
        num_records++;
        qsort(records, num_records, sizeof(Record), compare_records);
      } else {
        printf("n/a\n");
        free(records);
        fclose(file);
        return 1;
      }
    }

    // Write the sorted data back to the file
    fseek(file, 0, SEEK_SET);
    fwrite(records, sizeof(Record), num_records, file);
    fflush(file);  // Ensure data is written to disk

    // Print the sorted records
    for (int i = 0; i < num_records; i++) {
      print_record(&records[i]);
    }

    free(records);
  } else {
    printf("n/a\n");
  }

  fclose(file);
  return 0;
}
