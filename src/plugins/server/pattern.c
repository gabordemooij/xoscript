#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include "../../citrine.h"
#include "pattern.h"

ctr_object* CtrServerPCRE2;

char* ctr_internal_server_pcre2_replace_callback(const char *pattern, const char *subject, ctr_object* callback) {
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
        char* err[120];
        sprintf(err, "Failed to compile PCRE2 pattern at offset: %zu.", (size_t)erroroffset);
        ctr_error(err,0);
        return NULL;
    }
	pcre2_match_data *match = pcre2_match_data_create_from_pattern(re, NULL);
	size_t subject_len = strlen(subject);
    size_t outcap = subject_len * 2 + 128;
    char *output = ctr_heap_allocate(outcap);
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
            size_t rest = subject_len - offset;
            if (outlen + rest + 1 > outcap) {
                outcap = outlen + rest + 1;
                output = ctr_heap_reallocate(output, outcap);
            }
            memcpy(output + outlen, subject + offset, rest);
            outlen += rest;
            break;
        }
		PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match);
        size_t start = ovector[0];
        size_t end   = ovector[1];
		if (start > offset) {
            size_t chunk = start - offset;
            if (outlen + chunk >= outcap) {
                outcap = outlen + chunk + 128;
                output = ctr_heap_reallocate(output, outcap);
            }
            memcpy(output + outlen, subject + offset, chunk);
            outlen += chunk;
        }
        const char *mstr = subject + start;
        size_t mlen = end - start;
        char *replacement;
        ctr_object* matchobj = ctr_build_string(mstr, mlen);
        ctr_argument arguments;
        ctr_argument argument2;
        arguments.object = matchobj;
        arguments.next = &argument2;
        ctr_object* matches = ctr_array_new(CtrStdArray, &arguments);
        uint32_t cnt;
        pcre2_pattern_info(re, PCRE2_INFO_CAPTURECOUNT, (void*) &cnt);
        //@todo fix memory usage
        for (int j = 0; j<=cnt; j++) {
			PCRE2_SIZE l;
			int q = pcre2_substring_length_bynumber(match, j, &l);
			size_t room = (l * 4 * sizeof(PCRE2_UCHAR)) + 1;
			PCRE2_UCHAR* pbuf = ctr_heap_allocate(room);
			int qq = pcre2_substring_copy_bynumber(match, j, pbuf, &room);
			if (qq) continue;
			ctr_object* subgroup = ctr_build_string_from_cstring(pbuf);
			subgroup->info.sticky = 1;
			ctr_argument pusharg;
			pusharg.object = subgroup;
			pusharg.next = NULL;
			ctr_array_push(matches, &pusharg);
			ctr_heap_free(pbuf);
		}
        matches->info.sticky = 1;
	    argument2.object = matches;
        argument2.next = NULL;
        matchobj->info.sticky = 1;
        ctr_object* result = ctr_block_run(callback, &arguments, callback);
        matchobj->info.sticky = 0;
        replacement = ctr_heap_allocate_cstring(result);
        size_t replen = strlen(replacement);
        if (outlen + replen >= outcap) {
            outcap = outlen + replen + 128;
            output = ctr_heap_reallocate(output, outcap);
        }
        memcpy(output + outlen, replacement, replen);
        outlen += replen;
        ctr_heap_free(replacement);
        offset = end;
    }
    output[outlen] = '\0';
    pcre2_match_data_free(match);
    pcre2_code_free(re);
    return output;
}

ctr_object* ctr_server_pcre2_new_set(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* pcre2Instance = ctr_internal_create_object(CTR_OBJECT_TYPE_OTOBJECT);
	pcre2Instance->link = myself;
	ctr_internal_object_property(pcre2Instance, "_pattern", ctr_internal_copy2string(argumentList->object));
	return pcre2Instance;
}

ctr_object* ctr_server_pcre2_new(ctr_object* myself, ctr_argument* argumentList) {
	ctr_argument a;
	a.object = ctr_build_empty_string();
	a.next = NULL;
	return ctr_server_pcre2_new_set(myself,&a);
}

ctr_object* ctr_server_pcre2_match_do(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* prop = ctr_internal_object_property(myself, "_pattern",NULL);
	if (!prop) return CtrStdNil;
	ctr_object* answer = CtrStdNil;
	char* pattern_str = ctr_heap_allocate_cstring(prop);
	char* subject_str = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	char* result = ctr_internal_server_pcre2_replace_callback(pattern_str, subject_str, argumentList->next->object);
	if (result) {
		answer = ctr_build_string_from_cstring(result);
		ctr_heap_free(result);
	}
	ctr_heap_free(subject_str);
	ctr_heap_free(pattern_str);
	return answer;
}

void begin_pcre2() {
	CtrServerPCRE2 = ctr_server_pcre2_new(CtrStdString, NULL);
	ctr_internal_create_func(CtrServerPCRE2, ctr_build_string_from_cstring( CTR_DICT_NEW_SET ), &ctr_server_pcre2_new_set );
	ctr_internal_create_func(CtrServerPCRE2, ctr_build_string_from_cstring( "match:do:" ), &ctr_server_pcre2_match_do );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Pattern" ), CtrServerPCRE2, CTR_CATEGORY_PUBLIC_PROPERTY);
}