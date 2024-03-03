#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* replace_file_extension(const char* original_path,
                                   const char* new_extension) {
  // Find the last dot in the original path
  const char* last_dot = strrchr(original_path, '.');

  // Calculate the length of the extension
  size_t extension_length = strlen(new_extension);

  // Calculate the length of the original path without the extension
  size_t path_length =
      last_dot ? (size_t)(last_dot - original_path) : strlen(original_path);

  // Allocate memory for the new path, new extension and null character
  char* new_path = (char*)malloc(path_length + extension_length + 1);
  if (new_path == NULL) {
    fputs("Memory allocation failed.\n", stderr);
    return NULL;
  }

  // Copy the original path up to the last dot (if it exists)
  if (last_dot) {
    strncpy(new_path, original_path, path_length);
  } else {
    strcpy(new_path, original_path);
  }

  // Append the new extension
  strcpy(new_path + path_length, new_extension);

  return new_path;
}