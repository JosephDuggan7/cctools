/*
Copyright (C) 2022 The University of Notre Dame
This software is distributed under the GNU General Public License.
See the file COPYING for details.
*/

#ifndef SHA1_H
#define SHA1_H

#include <stdint.h>
#include <stdlib.h>

/** @file sha1.h
Routines for computing SHA1 checksums.
*/

/* When linking with libcvmfs, we have a name clash with functions of similar purpose.  Redefine the names here to protect our namespace. */

#define sha1_init    dttools_sha1_init
#define sha1_update  dttools_sha1_update
#define sha1_final   dttools_sha1_final
#define sha1_buffer  dttools_sha1_buffer
#define sha1_file    dttools_sha1_file
#define sha1_string  dttools_sha1_string

#define SHA1_DIGEST_LENGTH 20
#define SHA1_DIGEST_ASCII_LENGTH 42

typedef struct {
	uint32_t digest[5];
	size_t countLo, countHi;
	uint32_t data[16];
	int Endianness;
} sha1_context_t;

void sha1_init(sha1_context_t * ctx);
void sha1_update(sha1_context_t * ctx, const void *, size_t);
void sha1_final(unsigned char digest[SHA1_DIGEST_LENGTH], sha1_context_t * ctx);

/** Checksum a memory buffer.
Note that this function produces a digest in binary form
which  must be converted to a human readable form with @ref sha1_string.
@param buffer Pointer to a memory buffer.
@param length Length of the buffer in bytes.
@param digest Pointer to a buffer to store the digest.
*/

void sha1_buffer(const void *buffer, size_t length, unsigned char digest[SHA1_DIGEST_LENGTH]);

/** Checksum a local file.
Note that this function produces a digest in binary form
which  must be converted to a human readable form with @ref sha1_string.
@param path Path to the file to checksum.
@param digest Pointer to a buffer to store the digest.
@return One on success, zero on failure.
*/

int sha1_file(const char *path, unsigned char digest[SHA1_DIGEST_LENGTH]);

int sha1_fd(int fd, unsigned char digest[SHA1_DIGEST_LENGTH]);

/** Convert an SHA1 digest into a printable string.
@param digest A binary digest returned from @ref sha1_file.
@returns A static pointer to a human readable form of the digest.
*/

const char *sha1_string(unsigned char digest[SHA1_DIGEST_LENGTH]);

#endif
