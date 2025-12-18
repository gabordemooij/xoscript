#ifdef LIBSECRET
#include <libsecret/secret.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../citrine.h"
#include "vault.h"
#include "monocypher/src/monocypher.h"


#define SERVER_VAULT_TOKENCHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
#define SERVER_VAULT_TOKENCHARS_NUM 62

// either provided by libsecret or bsd
int random_buf(void *buf, size_t n) {
    arc4random_buf(buf, n);
    return 0;
}

static void print_hex(char* name, unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

/* base64 implementation written by WEI Zhicheng. */

#define BASE64_ENCODE_OUT_SIZE(s) ((unsigned int)((((s) + 2) / 3) * 4 + 1))
#define BASE64_DECODE_OUT_SIZE(s) ((unsigned int)(((s) / 4) * 3))

#define BASE64_PAD '='
#define BASE64DE_FIRST '+'
#define BASE64DE_LAST 'z'

/* BASE 64 encode table */
static const char base64en[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/',
};

/* ASCII order for BASE 64 decode, 255 in unused character */
static const unsigned char base64de[] = {
	/* nul, soh, stx, etx, eot, enq, ack, bel, */
	   255, 255, 255, 255, 255, 255, 255, 255,
	/*  bs,  ht,  nl,  vt,  np,  cr,  so,  si, */
	   255, 255, 255, 255, 255, 255, 255, 255,
	/* dle, dc1, dc2, dc3, dc4, nak, syn, etb, */
	   255, 255, 255, 255, 255, 255, 255, 255,
	/* can,  em, sub, esc,  fs,  gs,  rs,  us, */
	   255, 255, 255, 255, 255, 255, 255, 255,
	/*  sp, '!', '"', '#', '$', '%', '&', ''', */
	   255, 255, 255, 255, 255, 255, 255, 255,
	/* '(', ')', '*', '+', ',', '-', '.', '/', */
	   255, 255, 255,  62, 255, 255, 255,  63,
	/* '0', '1', '2', '3', '4', '5', '6', '7', */
	    52,  53,  54,  55,  56,  57,  58,  59,
	/* '8', '9', ':', ';', '<', '=', '>', '?', */
	    60,  61, 255, 255, 255, 255, 255, 255,
	/* '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', */
	   255,   0,   1,  2,   3,   4,   5,    6,
	/* 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', */
	     7,   8,   9,  10,  11,  12,  13,  14,
	/* 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', */
	    15,  16,  17,  18,  19,  20,  21,  22,
	/* 'X', 'Y', 'Z', '[', '\', ']', '^', '_', */
	    23,  24,  25, 255, 255, 255, 255, 255,
	/* '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', */
	   255,  26,  27,  28,  29,  30,  31,  32,
	/* 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', */
	    33,  34,  35,  36,  37,  38,  39,  40,
	/* 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', */
	    41,  42,  43,  44,  45,  46,  47,  48,
	/* 'x', 'y', 'z', '{', '|', '}', '~', del, */
	    49,  50,  51, 255, 255, 255, 255, 255
};

static unsigned int
base64_encode(const unsigned char *in, unsigned int inlen, char *out) {
	int s;
	unsigned int i;
	unsigned int j;
	unsigned char c;
	unsigned char l;
	s = 0;
	l = 0;
	for (i = j = 0; i < inlen; i++) {
		c = in[i];
		switch (s) {
		case 0:
			s = 1;
			out[j++] = base64en[(c >> 2) & 0x3F];
			break;
		case 1:
			s = 2;
			out[j++] = base64en[((l & 0x3) << 4) | ((c >> 4) & 0xF)];
			break;
		case 2:
			s = 0;
			out[j++] = base64en[((l & 0xF) << 2) | ((c >> 6) & 0x3)];
			out[j++] = base64en[c & 0x3F];
			break;
		}
		l = c;
	}
	switch (s) {
	case 1:
		out[j++] = base64en[(l & 0x3) << 4];
		out[j++] = BASE64_PAD;
		out[j++] = BASE64_PAD;
		break;
	case 2:
		out[j++] = base64en[(l & 0xF) << 2];
		out[j++] = BASE64_PAD;
		break;
	}
	out[j] = 0;
	return j;
}

static unsigned int
base64_decode(const char *in, unsigned int inlen, unsigned char *out)
{
	unsigned int i;
	unsigned int j;
	unsigned char c;
	if (inlen & 0x3) { return 0; }
	for (i = j = 0; i < inlen; i++) {
		if (in[i] == BASE64_PAD) { break; }
		if (in[i] < BASE64DE_FIRST || in[i] > BASE64DE_LAST) return 0;
		c = base64de[(unsigned char)in[i]];
		if (c == 255) return 0;
		switch (i & 0x3) {
		case 0:
			out[j] = (c << 2) & 0xFF;
			break;
		case 1:
			out[j++] |= (c >> 4) & 0x3;
			out[j] = (c & 0xF) << 4; 
			break;
		case 2:
			out[j++] |= (c >> 2) & 0xF;
			out[j] = (c & 0x3) << 6;
			break;
		case 3:
			out[j++] |= c;
			break;
		}
	}
	return j;
}

/* End of base64 code */




//@todo protect against using Vault itself, always make instance, need name

char* ctr_internal_gui_vault_name(ctr_object* myself) {
	return ctr_heap_allocate_cstring(
		ctr_internal_cast2string(
			ctr_internal_object_property(
				myself,
				"name",
				NULL
			)
		)
	);
}

ctr_object* ctr_gui_vault_new_set(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* inst = ctr_internal_create_object(CTR_OBJECT_TYPE_OTOBJECT);
	ctr_internal_object_property(
		inst,
		"name",
		ctr_internal_copy2string(argumentList->object)
	);
	inst->link = myself;
	return inst;
}

ctr_object* ctr_gui_vault_new(ctr_object* myself, ctr_argument* argumentList) {
	ctr_argument a;
	a.object = ctr_build_string_from_cstring("default");
	a.next = NULL;
	return ctr_gui_vault_new_set(myself, &a);
}

ctr_object* ctr_gui_vault_name(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_internal_object_property(
		myself,
		"name",
		NULL
	);
}


uint8_t* ctr_gui_vault_internal_derive_key(char* password, uint8_t* hash, uint8_t* salt) {
	crypto_argon2_config config = {
		.algorithm = CRYPTO_ARGON2_I,            /* Argon2i         */
		.nb_blocks = 100000,                     /* 100 megabytes   */
		.nb_passes = 3,                          /* 3 iterations    */
		.nb_lanes  = 1                           /* Single-threaded */
	};
	crypto_argon2_inputs inputs = {
		.pass      = password,                   /* User password */
		.salt      = salt,                 /* Salt for the password */
		.pass_size = strlen(password) - 1,       /* Password length */
		.salt_size = 16
	};
	crypto_argon2_extras extras = {0};   /* Extra parameters unused */
	void *work_area = malloc((size_t)config.nb_blocks * 1024);
	if (work_area == NULL) {
		exit(1); //@todo decent error handling
	} else {
		crypto_argon2(hash, 32, work_area,
					  config, inputs, extras);
		free(work_area);
	}
	return &hash;
}


ctr_object* ctr_gui_vault_encrypt(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* result;
	ctr_object* message = ctr_internal_cast2string(argumentList->object);
	ctr_object* password_obj = ctr_internal_cast2string(argumentList->next->object);
	if (message->value.svalue->vlen < 1) {
		ctr_error("Empty message string.", 0);
		return myself;
	}
	if (password_obj->value.svalue->vlen < 1) {
		ctr_error("Empty password string.", 0);
		return myself;
	}
	int len = message->value.svalue->vlen;
	int outlen = len + 16 + 16 + 24 + sizeof(int);
	int outlen64 = BASE64_ENCODE_OUT_SIZE(outlen);
	char*    in;
	char*    out;
	char*    out64;
	uint8_t* text;
	uint8_t key[32];
	uint8_t salt[16];
	uint8_t mac[16];
	uint8_t nonce[24];
	uint8_t* password;
	uint8_t* encrypted;
	if (random_buf(salt, 16) == -1 || random_buf(nonce, 24) == -1) {
		ctr_error("Unable to generate secure random buffer.",0);
		return myself;
	}
	text = ctr_heap_allocate_cstring( message );
	password = ctr_heap_allocate_cstring( ctr_internal_cast2string(argumentList->next->object) );
	encrypted = ctr_heap_allocate(len);
	in = ctr_heap_allocate_cstring(message);
	ctr_gui_vault_internal_derive_key(password, &key, &salt);
	crypto_aead_lock(encrypted, mac, key, nonce, NULL, 0, in, len);
	out = ctr_heap_allocate( outlen );
	memcpy(out, salt, 16);
	memcpy(out + 16, nonce, 24);
	memcpy(out + 16 + 24, mac, 16);
	memcpy(out + 16 + 24 + 16, &len, sizeof(uint32_t));
	memcpy(out + 16 + 24 + 16 + sizeof(uint32_t), encrypted, len);
	crypto_wipe(key, 32);
	out64 = ctr_heap_allocate(outlen64);
	base64_encode(out, outlen, out64);
	result = ctr_build_string_from_cstring(out64);
	ctr_heap_free(in);
	ctr_heap_free(out);
	ctr_heap_free(out64);
	ctr_heap_free(encrypted);
	ctr_heap_free(text);
	ctr_heap_free(password);
	return result;
}

ctr_object* ctr_gui_vault_decrypt(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* result;
	ctr_object* encrypted_message;
	uint8_t* password;
	char* in64;
	char* in;
	char* out;
	char* message;
	int inlen64;
	int inlen;
	int outlen;
	int mlen;
	uint8_t key[32];
	uint8_t salt[16];
	uint8_t mac[16];
	uint8_t nonce[24];
	encrypted_message = ctr_internal_cast2string( argumentList->object );
	ctr_object* password_obj = ctr_internal_cast2string(argumentList->next->object);
	if (encrypted_message->value.svalue->vlen < 1) {
		ctr_error("Empty message string.", 0);
		return myself;
	}
	if (password_obj->value.svalue->vlen < 1) {
		ctr_error("Empty password string.", 0);
		return myself;
	}
	password = ctr_heap_allocate_cstring( ctr_internal_cast2string(argumentList->next->object) );
	inlen64 = encrypted_message->value.svalue->vlen;
	in64 = ctr_heap_allocate_cstring(encrypted_message);
	inlen = BASE64_DECODE_OUT_SIZE(inlen64);
	outlen = inlen - 24 - 16 - 16 - sizeof(uint32_t);
	in = ctr_heap_allocate(inlen);
	base64_decode(in64, inlen64, in);
	memcpy(salt, in, 16);
	memcpy(nonce, in+16, 24);
	memcpy(mac, in+16+24, 16);
	memcpy(&mlen, in+16+24+16, sizeof(uint32_t));
	message = ctr_heap_allocate((int)mlen);
	memcpy(message, in+16+24+16+sizeof(uint32_t), (size_t)mlen);
	ctr_gui_vault_internal_derive_key(password, &key, &salt);
	out = ctr_heap_allocate((int)mlen + 1);
	if (crypto_aead_unlock(out, mac, key, nonce, NULL, 0, message, (int)mlen)) {
		ctr_error("Unable to decrypt string, invalid format, password or algorithm.", 0);
		return myself;
	}
	crypto_wipe(key, 32);
	result = ctr_build_string_from_cstring(out);
	ctr_heap_free(in64);
	ctr_heap_free(in);
	ctr_heap_free(out);
	ctr_heap_free(password);
	ctr_heap_free(message);
	return result;
}


/*
 * cryptographically secure random token
 */
ctr_object* ctr_server_vault_token_set(ctr_object* myself, ctr_argument* argumentList) {
	int length = ctr_tonum(argumentList->object);
	if (length < 20 || length > 400) {
		ctr_error("Token length must be between 20-400 to be secure.",0);
		return CtrStdNil;
	}
	size_t rnd_len = length + (length / 4) + 1;
	uint8_t* rnd = ctr_heap_allocate(rnd_len);
    char* out = ctr_heap_allocate(length + 1);
    if (random_buf(rnd, rnd_len) != 0) {
		ctr_error("Unable to generate random token", 0);
		ctr_heap_free(rnd);
		ctr_heap_free(out);
		return CtrStdNil;
	}
	size_t out_i = 0;
    size_t rnd_i = 0;
    while (out_i < length) {
        if (rnd_i >= rnd_len) {
            if (random_buf(rnd, rnd_len) != 0) { // extremely unlikely, but refill if needed
				ctr_error("Unable to generate random token", 0);
				ctr_heap_free(rnd);
				ctr_heap_free(out);
				return CtrStdNil;
			}
            rnd_i = 0;
        }
        uint8_t v = rnd[rnd_i++];
        if (v >= 248)  continue; // avoid modulo bias (256 % 62 = 8)
        out[out_i++] = SERVER_VAULT_TOKENCHARS[v % SERVER_VAULT_TOKENCHARS_NUM];
    }
    out[length] = '\0';
    ctr_object* answer = ctr_build_string_from_cstring(out);
    ctr_heap_free(rnd);
	ctr_heap_free(out);
    return answer;
}

ctr_object* vaultObject;
void begin_vault() {
	//ctr_gui_internal_vault_init();
	vaultObject = ctr_gui_vault_new(CtrStdObject, NULL);
	vaultObject->link = CtrStdObject;
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "new" ), &ctr_gui_vault_new );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "new:" ), &ctr_gui_vault_new_set );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "name" ), &ctr_gui_vault_name );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "encrypt:key:" ), &ctr_gui_vault_encrypt );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "decrypt:key:" ), &ctr_gui_vault_decrypt );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "token:" ), &ctr_server_vault_token_set );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Vault" ), vaultObject, CTR_CATEGORY_PUBLIC_PROPERTY);
}
