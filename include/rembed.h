/**
 * @file rembed.h
 * @author jkstpierre (jkstpierre@wpi.edu)
 * @brief 
 * @version 0.1
 * @date 2020-02-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __REMBED_H__
#define __REMBED_H__

// Structs
/**
 * @brief An EmbeddedResource_t is a struct for referencing data embedded in the running binary
 * 
 */
typedef struct {
  void* data;   // Pointer to the embedded data
  unsigned long long size;  // Size of the data in bytes
} EmbeddedResource_t;

// Macros
/**
 * @brief Loads an embedded resource from the calling executable's binary. Compilation error will occur if resource not found.
 * 
 */
#define LoadEmbeddedResource(resource) ([]() { \
  extern const void resource_##resource[]; \
  extern const unsigned long long resource_##resource##__size; \
  return (EmbeddedResource_t){resource_##resource, resource_##resource##_size}; \
})()

#endif