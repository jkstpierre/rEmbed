/**
 * @file rEmbed.c
 * @author jkstpierre (jkstpierre@wpi.edu)
 * @brief 
 * @version 0.1
 * @date 2020-02-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

// Defines
#define _REMBED_ARGS_SOURCE_      1   // The resource to embed
#define _REMBED_ARGS_DEST_        2   // The embedded file name
#define _REMBED_ARGS_EXPECTED_    3   // The number of args expected

// Detect OS for platform independent directory creation
#if defined unix || defined __unix__ || defined __unix
#include <sys/stat.h>
#include <libgen.h>
#define mkdir(dir) mkdir(dir, S_IRWXU)
#define basename(path) basename(path)
#define DIR_SEPARATOR '/'
#endif

#if defined _WIN32 || defined _WIN64
#include <Windows.h>
#define mkdir(dir) _mkdir(dir)
#define basename(path) ([]() {  \
  const char* result = NULL;  \
  _splitpath(path, NULL, NULL, &result, NULL);  \
  return result;
})()
#define DIR_SEPARATOR '\\'
#endif

#define _REMBED_TRUE_   1
#define _REMBED_FALSE_  0

/**
 * @brief Function to generate complete directory path for a given filepath. Will not create file.
 * Based on: https://gist.github.com/JonathonReinhart/8c0d90191c38af2dcadb102c4e202950
 * 
 * @param path    The path to the file to create. 
 * @return int    Return _REMBED_TRUE_ on success, _REMBED_FALSE_ on failure
 */
int makeDirectories(const char* path) {
  // Terminate program if path is null
  assert(path && *path);

  /* Adapted from http://stackoverflow.com/a/2336245/119527 */
  const size_t len = strlen(path);
  char _path[4096];
  char *p; 

  errno = 0;

  /* Copy string so its mutable */
  if (len > sizeof(_path)-1) {
    errno = ENAMETOOLONG;
    return _REMBED_FALSE_; 
  }   
  strcpy(_path, path);

  /* Iterate the string */
  for (p = strchr(_path + 1, DIR_SEPARATOR); p; p = strchr(p+1, DIR_SEPARATOR)) {
    /* Temporarily truncate */
    *p = '\0';

    if (mkdir(_path) != 0) {
      if (errno != EEXIST)
          return _REMBED_FALSE_; 
    }

    // Restore
    *p = DIR_SEPARATOR;
  }   

  return _REMBED_TRUE_;
}

/**
 * @brief Create the resource name to be saved in the embedded .c file
 * 
 * @param rName     The name to save the resource as, must already be allocated
 * @param rPath     The path to the resource on disk
 */
void createResourceName(char* rName, const char* rPath) {
  const char* fileName = basename(rPath);

  
}


/**
 * @brief Main function serves as program entry point
 * 
 * @param argc    Number of arguments received
 * @param args    Array of C-strings containing each argument
 * @return int    Return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
int main(int argc, char** args) {
  if (argc != _REMBED_ARGS_EXPECTED_) {
    fprintf(stderr, "rEmbed error: Expected format is %s {resource} {destination}\n", args[0]);
    return EXIT_FAILURE;
  }

  const char* resourcePath = args[_REMBED_ARGS_SOURCE_];
  const char* resourceDest = args[_REMBED_ARGS_DEST_];

  FILE* resource = fopen(resourcePath, "rb");
  if (resource) {
    if (makeDirectories(resourceDest)) {
      FILE* embed = fopen(resourceDest, "wb");
      if (embed) {
        fprintf(embed, "#include<stdlib.h>\n");
        

        fclose(embed);
      }
      else {
        fprintf(stderr, "rEmbed error: Cannot create embedded resource %s\n", resourceDest);
        return EXIT_FAILURE;
      }
    }
    else {
      fprintf(stderr, "rEmbed error: Cannot create directories for destination %s\n", resourceDest);
      return EXIT_FAILURE;
    }

    fclose(resource);
  }
  else {
    fprintf(stderr, "rEmbed error: Cannot locate resource %s\n", resourcePath);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}