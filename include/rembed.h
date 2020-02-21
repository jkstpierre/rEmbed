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

// Structures
/**
 * @brief A resource_t is a simple wrapper struct for embedded data
 * 
 */
typedef struct {
  void* data;   // The byte stream
  unsigned long long size;  // The number of bytes
} resource_t;

#endif