// DO NOT USE THIS CODE!
// generated with ai, not verified yet, just serves as a placeholder
// just for some inspiration

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre2.h>

#define PCRE2_CODE_UNIT_WIDTH 8

// Callback type
typedef char* (*replace_callback)(const char *match, size_t len);

char* pcre2_replace_callback(
    const char *pattern,
    const char *subject,
    replace_callback callback
) {
    int errorcode;
    PCRE2_SIZE erroroffset;

    pcre2_code *re = pcre2_compile(
        (PCRE2_SPTR)pattern,
        PCRE2_ZERO_TERMINATED,
        0,
        &errorcode,
        &erroroffset,
        NULL
    );
    if (!re) {
        fprintf(stderr, "PCRE2 compile error at offset %zu\n", (size_t)erroroffset);
        return NULL;
    }

    pcre2_match_data *match = pcre2_match_data_create_from_pattern(re, NULL);

    size_t subject_len = strlen(subject);
    size_t outcap = subject_len * 2 + 128;
    char *output = malloc(outcap);
    size_t outlen = 0;

    size_t offset = 0;
    while (1) {
        int rc = pcre2_match(
            re,
            (PCRE2_SPTR8)subject,
            subject_len,
            offset,
            0,
            match,
            NULL
        );

        if (rc < 0) {
            // geen match meer → rest kopiëren
            size_t rest = subject_len - offset;
            if (outlen + rest + 1 > outcap) {
                outcap = outlen + rest + 1;
                output = realloc(output, outcap);
            }
            memcpy(output + outlen, subject + offset, rest);
            outlen += rest;
            break;
        }

        PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match);
        size_t start = ovector[0];
        size_t end   = ovector[1];

        // tekst vóór de match kopiëren
        if (start > offset) {
            size_t chunk = start - offset;
            if (outlen + chunk >= outcap) {
                outcap = outlen + chunk + 128;
                output = realloc(output, outcap);
            }
            memcpy(output + outlen, subject + offset, chunk);
            outlen += chunk;
        }

        // callback uitvoeren
        const char *mstr = subject + start;
        size_t mlen = end - start;
        char *replacement = callback(mstr, mlen);
        size_t replen = strlen(replacement);

        if (outlen + replen >= outcap) {
            outcap = outlen + replen + 128;
            output = realloc(output, outcap);
        }
        memcpy(output + outlen, replacement, replen);
        outlen += replen;

        free(replacement);

        offset = end;
    }

    output[outlen] = '\0';

    pcre2_match_data_free(match);
    pcre2_code_free(re);

    return output;
}

//example
char* uppercase_callback(const char *match, size_t len) {
    char *res = malloc(len + 1);
    for (size_t i = 0; i < len; i++)
        res[i] = (char)toupper(match[i]);
    res[len] = '\0';
    return res;
}

//usage
int main(void) {
    const char *subject = "Hello 123 world 456 test";
    const char *pattern = "\\d+";

    char *result = pcre2_replace_callback(pattern, subject, uppercase_callback);

    printf("input : %s\n", subject);
    printf("output: %s\n", result);

    free(result);
    return 0;
}
