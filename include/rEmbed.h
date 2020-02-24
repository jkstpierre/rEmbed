/**
 * @file rEmbed.h
 * @author jkstpierre (jkstpierre@wpi.edu)
 * @brief 
 * @version 0.1
 * @date 2020-02-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __REMBED_H__
#define __REMBED_H__

// Includes
#include <stdlib.h>

// Structs
/**
 * @brief An rEmbedResource_t contains a pointer to an embedded resource.
 * 
 */
typedef struct {
  const void*   data;   // Pointer to the embedded data
  const size_t  size;   // The number of bytes in data
} rEmbedResource_t;

// Functions
/**
 * @brief Load an embedded resource by its name. Will cause linker errors if not found.
 * 
 */
#define rEmbedLoadResource(RNAME) ([]() {  \
  extern const void rEmbedResource_##RNAME[];  \
  extern const size_t rEmbedResource_##RNAME##_size; \
  return (rEmbedResource_t){rEmbedResource_##RNAME, rEmbedResource_##RNAME##_size}; \
})()

#endif