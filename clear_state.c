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

// Function to compare a record's date with a given date
int compareDates(const Record *record, const int year, const int month,
                 const int day) {
  if (record->year < year) {
    return -1;
  } else if (record->year > year) {
    return 1;
  } else {
    if (record->month < month) {
      return -1;
    } else if (record->month > month) {
      return 1;
    } else {
      if (record->day < day) {
        return -1;
      } else if (record->day > day) {
        return 1;
      } else {
        return 0;
      }
    }
  }
}

// Function to print a record
void print_record(const Record *record) {
  printf("%d %d %d %d %d %d %d %d\n", record->year, record->month, record->day,
         record->hour, record->minute, record->second, record->status,
         record->code);
}

int main() {
  char filename[100] = "../";
  char tmp_path[100];
  char tempFilename[] = "temp.dat";
  FILE *file = NULL, *tempFile = NULL;
  Record record;
  int startYear, startMonth, startDay;
  int endYear, endMonth, endDay;
  int found = 0;

  // Read filename from stdin
  if (scanf("%99s", tmp_path) != 1) {
    printf("n/a\n");
    return 1;
  }
  strcat(filename, tmp_path);

  // Open the input file
  file = fopen(filename, "rb");
  if (!file) {
    printf("n/a\n");
    return 1;
  }

  // Open the temporary file
  tempFile = fopen(tempFilename, "wb");
  if (!tempFile) {
    printf("n/a\n");
    fclose(file);
    return 1;
  }

  // Read start and end dates from stdin
  if (scanf("%d.%d.%d %d.%d.%d", &startDay, &startMonth, &startYear, &endDay,
            &endMonth, &endYear) != 6) {
    printf("n/a\n");
    fclose(file);
    fclose(tempFile);
    remove(tempFilename);
    return 1;
  }

  // Process each record in the input file
  while (fread(&record, sizeof(Record), 1, file) == 1) {
    if (compareDates(&record, startYear, startMonth, startDay) < 0 ||
        compareDates(&record, endYear, endMonth, endDay) > 0) {
      fwrite(&record, sizeof(Record), 1, tempFile);
    } else {
      found = 1;  // Mark that at least one record was skipped
    }
  }

  // Close the files
  fclose(file);
  fclose(tempFile);

  // If no records were skipped, print "n/a" and remove the temporary file
  if (!found) {
    printf("n/a\n");
    remove(tempFilename);
  } else {
    // Replace the original file with the temporary file
    if (remove(filename) != 0 || rename(tempFilename, filename) != 0) {
      printf("n/a\n");
      remove(tempFilename);
    } else {
      // Print the remaining records in the file
      file = fopen(filename, "rb");
      if (file) {
        while (fread(&record, sizeof(Record), 1, file) == 1) {
          print_record(&record);
        }
        fclose(file);
      } else {
        printf("n/a\n");
      }
    }
  }

  return 0;
}