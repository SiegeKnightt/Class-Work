/*
Name: Reeves Farrell
Class: CPSC 3220
Assignment: Project 4
Due Date: Tue Dec 5, 2023 11:59pm
*/

#include "tfs.h"


/* implementation of assigned functions - skeleton for students */


/* tfs_seek()
 *
 * sets the byte offset in a directory entry
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is open
 *   (3) the specified offset is less than or equal to the
 *         file size (equal would occur in the case of
 *         writing a new record at the end of a file)
 *
 * postconditions:
 *   (1) the byte offset of the directory entry is set to the
 *         specified offset
 *   (2) the current block of the directory entry is set to the
 *         corresponding block (in the case of the offset being
 *         equal to the file size and just beyond the end of
 *         the last block of the file, the current block will
 *         be set to LAST_BLOCK)
 *
 * input parameters are a file descriptor and a byte offset
 *
 * return value is TRUE when successful or FALSE when failure
 */

unsigned int tfs_seek(unsigned int file_descriptor, unsigned int offset) {
    if (!tfs_is_fd_in_range(file_descriptor) || !tfs_is_fd_open(file_descriptor)) {
        return FALSE;  // Return FALSE for failure
    }

    struct directory_entry *entry = &directory[file_descriptor];
    entry->byte_offset = offset;

    // Traverse the FAT to find the correct block for the given offset
    entry->current_block = entry->first_block;
    unsigned int block_offset = offset;

    while (block_offset >= BLOCK_SIZE && entry->current_block != LAST_BLOCK) {
        entry->current_block = file_allocation_table[entry->current_block];
        block_offset -= BLOCK_SIZE;
    }

    return TRUE;
}



/* tfs_delete()
 *
 * deletes a closed directory entry having the given file descriptor
 *   (changes the status of the entry to unused) and releases all
 *   allocated storage blocks
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is closed
 *
 * postconditions:
 *   (1) the status of the directory entry is set to unused
           and all other fields are set to zero
 *   (2) all storage blocks have been set to free
 *
 * input parameter is a file descriptor
 *
 * return value is TRUE when successful or FALSE when failure
 */

unsigned int tfs_delete(unsigned int file_descriptor) {
  
  if (!tfs_is_fd_in_range(file_descriptor) || tfs_is_fd_open(file_descriptor)) {
      
    return FALSE;
  }

  struct directory_entry *entry = &directory[file_descriptor];
  unsigned int current_block = entry->first_block;

  while (current_block != LAST_BLOCK && current_block != FREE) {
    
    unsigned int next_block = file_allocation_table[current_block];
    file_allocation_table[current_block] = FREE;
    current_block = next_block;
  }

  entry->status = UNUSED;
  memset(entry, 0, sizeof(struct directory_entry));  // Zero out the entry

  return TRUE;
}



/* tfs_write()
 *
 *     ---- students: DO NOT access the storage[] array or ----
 *     ---- the blocks[] array directly in this function;  ----
 *     ---- use tfs_block_read() and tfs_block_write() to  ----
 *     ---- to access the blocks in the storage[] array    ----
 *
 * writes a specified number of bytes from a specified buffer
 *   into a file starting at the byte offset in the directory;
 *   the byte offset in the directory entry is incremented by
 *   the number of bytes transferred
 *
 * depending on the starting byte offset and the specified
 *   number of bytes to transfer, the transfer may cross two
 *   or more storage blocks
 *
 * this function does not directly access bytes in storage;
 *   instead, each block is first read into an internal
 *   buffer using the helper function tfs_read_block();
 *   this function then moves bytes from the user buffer
 *   to the internal buffer and then writes each updated
 *   block using the helper function tfs_write_block()
 *
 * the read-modify-write approach is used since a write
 *   may only change part of the content of a block and
 *   the bytes at the unaffected start and or end of a
 *   block must be preserved (a possible optimization is
 *   to omit a read when all bytes of a block will be
 *   overwritten; however, that optimization is not
 *   required, and students should aim for correctness
 *   over eliminating block reads)
 *
 * note that this function can extend the file size by
 *   writing bytes beyond the current end of the file;
 *   this depends on:
 *   (1) the starting byte offset
 *   (2) the specified number of bytes to transfer
 *   (3) the availability of additional storage blocks
 *   (4) the maximum file size
 *
 * extra bytes may fit into the last allocated storage
 *   block, or additional storage blocks, if available,
 *   may be added to the file to hold the extra bytes
 *
 * notable special cases that this function should handle:
 *   - writing to an empty file, which has no storage
 *       blocks allocated (current block will be 0)
 *   - writing past the end of a file that originally
 *       ended at the end of a storage block (current
 *       block will be equal to LAST_BLOCK)
 *   - writing that ends at the end of a storage block
 *       (current block must be set to the correct
 *       value so that a subsequent read or write is
 *       handled correctly)
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is open
 *   (3) the requested block count is non-zero
 *
 * postconditions:
 *   (1) the file contains bytes transferred from the user
 *         buffer to the extent possible
 *   (2) the specified number of bytes has been transferred
 *         except in the cases that
 *       (a) storage blocks needed to complete the transfer
 *             are not available
 *       (b) bytes to be written would exceed the maximum
 *             file size
 *       (c) a call to tfs_block_write() fails
 *   (3) the byte offset and current block are updated to
 *         point to the next byte to read or write
 *   (4) the file size has been updated if bytes are added
 *         past the original end of the file
 *
 * input parameters are a file descriptor, the address of a
 *   buffer of bytes to transfer, and the count of bytes to
 *   transfer
 *
 * return value is the number of bytes transferred
 */

unsigned int tfs_write(unsigned int file_descriptor, char *user_buffer, unsigned int byte_count) {
    if (!tfs_is_fd_in_range(file_descriptor) || !tfs_is_fd_open(file_descriptor)) {
        return 0;
    }

    struct directory_entry *entry = &directory[file_descriptor];
    unsigned int bytes_written = 0;
    char block_buffer[BLOCK_SIZE];

    while (bytes_written < byte_count) {
        unsigned int offset_in_block = entry->byte_offset % BLOCK_SIZE;

        // Determine if a new block needs to be allocated
        if (entry->first_block == FREE || offset_in_block == 0) {
            if (entry->byte_offset >= entry->size) {
                // Allocate new block
                unsigned int new_block = tfs_new_block();
                if (new_block == FREE) {
                    break;  // No more blocks available
                }

                if (entry->first_block == FREE) {
                    entry->first_block = new_block;
                } else {
                    file_allocation_table[entry->current_block] = new_block;
                }

                entry->current_block = new_block;
                file_allocation_table[new_block] = LAST_BLOCK;
            }
        }

        // Read the current block into the buffer
        if (!tfs_block_read(entry->current_block, block_buffer)) {
            return bytes_written;  // Failed to read the block
        }

        // Write data into the block buffer
        while (offset_in_block < BLOCK_SIZE && bytes_written < byte_count) {
            block_buffer[offset_in_block++] = user_buffer[bytes_written++];
            entry->byte_offset++;

            if (entry->byte_offset > entry->size) {
                entry->size = entry->byte_offset;  // Update file size
            }
        }

        // Write the modified block back to storage
        if (!tfs_block_write(entry->current_block, block_buffer)) {
            return bytes_written;  // Failed to write the block
        }

        // Update the current block for the next iteration
        if (offset_in_block >= BLOCK_SIZE) {
            entry->current_block = file_allocation_table[entry->current_block];
        }
    }

    return bytes_written;
}




/* tfs_copy()
 *
 *     ---- students: DO NOT access the storage[] array or ----
 *     ---- the blocks[] array directly in this function;  ----
 *     ---- use tfs_block_read() and tfs_block_write() or  ----
 *     ---- tfs_read() and tfs_write() to access storage   ----
 *
 * copies one file to another
 *
 * note that if the destination file was originally larger
 *   than the source file then any unneeded storage blocks
 *   must be freed; one possible way to accomplish this is
 *   to delete an existing destination file and create it
 *   again as an empty file
 *
 * preconditions:
 *   (1) the source file exists, has size greater than 0,
 *         and is not currently open
 *   (2) the destination file either
 *       (a) does not exist yet and name is valid, or
 *       (b) does exist and is not currently open
 *
 * postcondition:
 *   (1) the source file is unchanged and is closed
 *   (1) the destination file exists, is a copy of the
 *         source file, and is closed except in these cases:
 *       (a) a source file precondition was not met - result
 *             is that either there is no destination file
 *             or the destination file remains unchanged
 *       (b) the destination file does not exist and the
 *             name is invalid - result is that there is no
 *             destination file
 *       (c) there were not enough directory entries
 *             available to create a new file - the result
 *             is that there is no destination file
 *       (d) there were not enough storage blocks available
 *             to completely copy the source file - the
 *             result is an incomplete copy
 *       (e) there were failures in tfs_read() and/or
 *             tfs_write() - the result is an incomplete
 *             copy
 *
 * input parameters are two file names
 *
 * return value is the number of bytes copied (0 in error cases)
 */

unsigned int tfs_copy(char *from_name, char *to_name) {
  
  unsigned int src_fd = tfs_open(from_name);
  
  if (!src_fd) {
    
    return 0;
  }

  unsigned int dest_fd = tfs_create(to_name);
  
  if (!dest_fd) {
    
    tfs_close(src_fd);
    
    return 0;
  }

  struct directory_entry *src_entry = &directory[src_fd];
  unsigned int file_size = src_entry->size;
  unsigned int total_bytes_copied = 0;
  char buffer[BLOCK_SIZE];
  unsigned int bytes_read, bytes_written;

  tfs_seek(src_fd, 0);
  tfs_seek(dest_fd, 0);

  while (file_size > 0) {
    
    bytes_read = tfs_read(src_fd, buffer, BLOCK_SIZE);
    bytes_written = tfs_write(dest_fd, buffer, bytes_read);
    
    if (bytes_written < bytes_read) {
      
      tfs_close(src_fd);
      tfs_close(dest_fd);
      
      return total_bytes_copied;
    }
    
    total_bytes_copied += bytes_written;
    file_size -= bytes_read;
  }

  tfs_close(src_fd);
  tfs_close(dest_fd);
  
  return total_bytes_copied;
}