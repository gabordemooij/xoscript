#include "xo.h"

/**
 * UTF8Size
 *
 * measures the size of character
 */
int ctr_utf8size(char c) {
	if ((c & CTR_UTF8_BYTE3) == CTR_UTF8_BYTE3) return 4;
	if ((c & CTR_UTF8_BYTE2) == CTR_UTF8_BYTE2) return 3;
	if ((c & CTR_UTF8_BYTE1) == CTR_UTF8_BYTE1) return 2;
	return 1;
}

/**
 * GetUTF8Length
 *
 * measures the length of an utf8 string in utf8 chars
 */
ctr_size ctr_getutf8len(char* strval, ctr_size max) {
	ctr_size i;
	ctr_size j = 0;
	ctr_size s = 0;
	for(i = 0; i < max; i++) {
		s = ctr_utf8size(strval[i]);
		j += (s - 1);
	}
	return (i-j);
}

/**
 * GetBytesForUTF8String
 */
ctr_size getBytesUtf8(char* strval, long startByte, ctr_size lenUChar) {
	long i = 0;
	long bytes = 0;
	int s = 0;
	ctr_size x = 0;
	long index = 0;
	char c;
	while(x < lenUChar) {
		index = startByte + i;
		c = strval[index];
		s = ctr_utf8size(c);
		bytes = bytes + s;
		i = i + s;
		x ++;
	}
	return bytes;
}

// DFA utf8
// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
// Slightly adjusted version

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

static const uint8_t utf8d[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 00..1f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 20..3f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 40..5f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 60..7f
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, // 80..9f
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, // a0..bf
  8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, // c0..df
  0xa,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x4,0x3,0x3, // e0..ef
  0xb,0x6,0x6,0x6,0x5,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8, // f0..ff
  0x0,0x1,0x2,0x3,0x5,0x8,0x7,0x1,0x1,0x1,0x4,0x6,0x1,0x1,0x1,0x1, // s0..s0
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1, // s1..s2
  1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1, // s3..s4
  1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1, // s5..s6
  1,3,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // s7..s8
};

static inline uint32_t ctr_utf8decode(uint32_t* state, uint32_t* codep, uint32_t byte) {
  uint32_t type = utf8d[byte];

  *codep = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*codep << 6) :
    (0xff >> type) & (byte);

  *state = utf8d[256 + *state*16 + type];
  return *state;
}

// End DFA utf8

// not conform rfc but this is for performance reasons (no realloc).
// input bytes and length (does not have to be a c-string)
// new length is returned
size_t ctr_utf8sanitize_fast(char *s, size_t n) {
	uint32_t state = UTF8_ACCEPT;
    uint32_t codepoint;
    unsigned char *src = (unsigned char *)s;
    unsigned char *dst = (unsigned char *)s;
    size_t ps = 0;      // pointer src
    size_t pd = 0; // pointer dst
    size_t o  = 0;  // offset
    int    sl;      // length of sequence 
	while(ps < n) {
		if (ctr_utf8decode(&state, &codepoint, src[ps++]) == UTF8_ACCEPT) { // found sequence
            sl = ps - o; // calculate length
            for(int j = 0; j < sl; j++) { // copy sequence
				dst[pd++] = src[o + j];
			}
			o = ps; // sync offset
        } else if (state == UTF8_REJECT) {
            dst[pd++] = '?';
            // skip contin. bytes belonging to this error
            while (ps < n && (src[ps] & 0xC0) == 0x80) ps++;
			o = ps;
            state = UTF8_ACCEPT;
        }
    }
    if (state != UTF8_ACCEPT) {
        dst[pd++] = '?';
    }
    return pd; // new length
}