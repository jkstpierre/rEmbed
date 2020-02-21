/**
 * @file rembed.c
 * @author jkstpierre (jkstpierre@wpi.edu)
 * @brief 
 * @version 0.1
 * @date 2020-02-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defines
#define _REMBED_DESTINATION_PATH_     1   // Path to the destination .c
#define _REMBED_RESOURCE_PATH_        2   // Path to the resource
#define _REMBED_EXPECTED_ARGUMENTS_   3   // Number of expected arguments

char *prepareResourceName(char *path) {
    char* retVal = path;
    char* p;
    for (p = path; *p; p++) {
        if (*p == '/' || *p == '\\' || *p == ':') {
            retVal = p;
        }
        else {
          char c = toupper(*p);
          if (c != *p)
            *p = c;
          else if (*p == '.' || *p == '-')
            *p = '_';
        }
    }
    return retVal;
}

// Main
/**
 * @brief Program entry point
 * 
 * @param argc  Number of arguments given
 * @param args  The arguments array
 * @return int  Returns 0 on success
 */
int main(int argc, char** args) {
  if (argc != _REMBED_EXPECTED_ARGUMENTS_) {
    fprintf(stderr, "rembed error: Expected {dest} {resource}. Creates {dest}.c from {resource}\n");
    exit(EXIT_FAILURE);
  }

  char* dest = args[1];
  char* resource = args[2];

  FILE* resourceFile = fopen(resource, "rb");
  if (resourceFile) {
    FILE* destFile = fopen(dest, "wb");
    if (destFile) {
      char* destResourceName = prepareResourceName(dest);

      fprintf(destFile, "#include <stdlib.h>\n\n");
      fprintf(destFile, "const void resource_%s[] = {\n", destResourceName);

      size_t n = 0;
      

      fclose(destFile);
    }
    else {
      fprintf(stderr, "rembed error: Failed to create destination file %s.\n", dest);
      exit(EXIT_FAILURE);
    }
    fclose(resourceFile);
  }
  else {
    fprintf(stderr, "rembed error: Failed to open resource file %s.\n", resource);
  }

  return 0; // Indicate success
}