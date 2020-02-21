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
#include <rembed.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines
#define _REMBED_RES_SCRIPT_INDEX_   1
#define _REMBED_EXPECTED_ARGS_      2

// Forward declarations
static const char* filename_ext(const char* filename);

/**
 * @brief Program entry point
 * 
 * @param argc  Number of arguments given
 * @param args  The arguments array
 * @return int  Returns 0 on success
 */
int main(int argc, char** args) {
  if (argc != _REMBED_EXPECTED_ARGS_) {
    fprintf(stderr, "rembed error: Expected 1 argument containing rembed script file (.rs), found %d arguments instead.\n", argc-1);
    exit(EXIT_FAILURE);
  }

  /**
   * @brief Grab the filepath from the arguments list and verify its file extension
   * 
   */
  const char* rs_filepath = args[_REMBED_RES_SCRIPT_INDEX_];
  if (strcmp(filename_ext(rs_filepath), ".rs") != 0) {
    fprintf(stderr, "rembed error: Invalid rembed script file given. File %s does not contain .rs extension.\n", rs_filepath);
    exit(EXIT_FAILURE);
  }

  /**
   * @brief Open the rembed script file
   * 
   */
  FILE* rs_file = fopen(rs_filepath, "r");
  if (!rs_file) {
    fprintf(stderr, "rembed error: Cannot locate rembed script %s on disk.\n", rs_filepath);
    exit(EXIT_FAILURE);
  }

  

  fclose(rs_file);
  
  return 0; // Indicate success
}

/**
 * @brief Gets the extension of a filepath
 * 
 * @param filename  The path to the file
 * @return const char* The file's extension
 */
static const char* filename_ext(const char* filename) {
  const char* dot = strrchr(filename, '.');
  if (!dot || dot == filename) return "";
  return dot;
}