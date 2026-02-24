#ifdef LIBSECRET
#include <libsecret/secret.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../xo.h"
#include "vault.h"
#include "monocypher/src/monocypher.h"


#define SERVER_VAULT_TOKENCHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
#define SERVER_VAULT_TOKENCHARS_NUM 62

/* Set crypto version = Argon2i 100mb 3lanes 16byte salt */
#define SERVER_VAULT_CRYPTO_ID_20262 "C20262$"

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

unsigned int
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

unsigned int
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

int ctr_gui_vault_internal_derive_key(unsigned char* password, uint8_t* hash, uint8_t* salt) {
	crypto_argon2_config config = {
		.algorithm = CRYPTO_ARGON2_ID,           /* Argon2id         */
		.nb_blocks = 100000,                     /* 100 megabytes   */
		.nb_passes = 3,                          /* 3 iterations    */
		.nb_lanes  = 1                           /* Single-threaded */
	};
	//password MUST be UTF-8 text without NUL bytes
	crypto_argon2_inputs inputs = {
		.pass      = password,                   /* User password */
		.salt      = salt,                 /* Salt for the password */
		.pass_size = strlen((char*)password),       /* Password length */
		.salt_size = 16
	};
	crypto_argon2_extras extras = {0};   /* Extra parameters unused */
	void *work_area = malloc((size_t)config.nb_blocks * 1024);
	if (work_area == NULL) {
		crypto_wipe(password, strlen((char*)password));
		return -1;
	} else {
		crypto_argon2(hash, 32, work_area,
					  config, inputs, extras);
		crypto_wipe(password, strlen((char*)password));
		free(work_area);
	}
	return 0;
}

// This function is not Endiann-safe.
ctr_object* ctr_gui_vault_encrypt(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* result;
	char*    in;
	char*    out;
	char*    out64;
	uint8_t key[32];
	uint8_t salt[16];
	uint8_t mac[16];
	uint8_t nonce[24];
	uint8_t* password;
	uint8_t* encrypted;
	password = (unsigned char*) ctr_heap_allocate_cstring( ctr_internal_cast2string(argumentList->next->object) );
	in = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	int len = strlen(in);
	if (len < 1) {
		ctr_error("Empty message string.", 0);
		ctr_heap_free(in);
		ctr_heap_free(password);
		return myself;
	}
	if (strlen((char*)password) < 1) {
		ctr_error("Empty password string.", 0);
		ctr_heap_free(in);
		ctr_heap_free(password);
		return myself;
	}
	int outlen = len + 16 + 16 + 24 + sizeof(uint32_t);
	int outlen64 = BASE64_ENCODE_OUT_SIZE(outlen);
	if (random_buf(salt, 16) == -1 || random_buf(nonce, 24) == -1) {
		ctr_error("Unable to generate secure random buffer.",0);
		ctr_heap_free(in);
		ctr_heap_free(password);
		return myself;
	}
	encrypted = ctr_heap_allocate(len);
	if (ctr_gui_vault_internal_derive_key(password, key, salt)==-1) {
		ctr_error("Unable to derive key.", 0);
		result = CtrStdNil;
		goto clean;
	}
	crypto_aead_lock((unsigned char*)encrypted, mac, key, nonce, NULL, 0, (unsigned char*)in, len);
	out = ctr_heap_allocate( outlen );
	memcpy(out, salt, 16);
	memcpy(out + 16, nonce, 24);
	memcpy(out + 16 + 24, mac, 16);
	memcpy(out + 16 + 24 + 16, &len, sizeof(uint32_t));
	memcpy(out + 16 + 24 + 16 + sizeof(uint32_t), encrypted, len);
	crypto_wipe(key, 32);
	out64 = ctr_heap_allocate(outlen64);
	unsigned int bytes_encoded = base64_encode((unsigned char*)out, outlen, out64);
	if (bytes_encoded == 0) {
		// should not be possible but then again, better safe then sorry
		ctr_error("Invalid base64 encoding, internal error.", 0);
		result = CtrStdNil;
	} else {
		result = ctr_build_string_from_cstring(out64);
	}
	ctr_heap_free(out);
	ctr_heap_free(out64);
	clean:
	ctr_heap_free(in);
	ctr_heap_free(encrypted);
	ctr_heap_free(password);
	return result;
}

ctr_object* ctr_gui_vault_decrypt(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* result;
	ctr_object* encrypted_message;
	char* password;
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
	password = ctr_heap_allocate_cstring( ctr_internal_cast2string(argumentList->next->object) );
	in64 = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	inlen64 = strlen(in64);
	if (encrypted_message->value.svalue->vlen < 1) {
		ctr_error("Empty message string.", 0);
		ctr_heap_free(password);
		ctr_heap_free(in64);
		return myself;
	}
	if (password_obj->value.svalue->vlen < 1) {
		ctr_error("Empty password string.", 0);
		ctr_heap_free(password);
		ctr_heap_free(in64);
		return myself;
	}
	inlen = BASE64_DECODE_OUT_SIZE(inlen64);
	if (inlen < (16 + 24 + 16 + sizeof(uint32_t))) {
		ctr_error("Encrypted message is too short.", 0);
		ctr_heap_free(in64);
		crypto_wipe((unsigned char*)password, strlen(password));
		ctr_heap_free(password);
		return CtrStdNil;
	}
	in = ctr_heap_allocate(inlen);
	unsigned int bytes_decoded = base64_decode(in64, inlen64, (unsigned char*)in);
	if (bytes_decoded == 0) {
		ctr_error("Invalid base64 input.", 0);
		ctr_heap_free(in);
		ctr_heap_free(in64);
		crypto_wipe((unsigned char*)password, strlen(password));
		ctr_heap_free(password);
		return CtrStdNil;
	}
	inlen = bytes_decoded;
	outlen = inlen - 24 - 16 - 16 - sizeof(uint32_t);
	memcpy(salt, in, 16);
	memcpy(nonce, in+16, 24);
	memcpy(mac, in+16+24, 16);
	memcpy(&mlen, in+16+24+16, sizeof(uint32_t));
	if (mlen < 0 || (size_t)mlen != outlen) {
		ctr_error("Invalid encrypted message length.", 0);
		ctr_heap_free(in);
		ctr_heap_free(in64);
		crypto_wipe((unsigned char*)password, strlen(password));
		ctr_heap_free(password);
		return CtrStdNil;
	}
	message = ctr_heap_allocate((int)mlen);
	memcpy(message, in+16+24+16+sizeof(uint32_t), (size_t)mlen);
	if (ctr_gui_vault_internal_derive_key((unsigned char*)password, key, salt)==-1) {
		ctr_error("Unable to derive key.", 0);
		crypto_wipe(message, mlen);
		result = CtrStdNil;
		goto clean;
	}
	out = ctr_heap_allocate((int)mlen + 1);
	out[(int)mlen] = '\0';
	if (crypto_aead_unlock((unsigned char*)out, mac, key, nonce, NULL, 0, (unsigned char*) message, (int)mlen)) {
		ctr_error("Unable to decrypt string, invalid format, password or algorithm.", 0);
		crypto_wipe(message, mlen);
		result = CtrStdNil;
		goto clean;
	}
	crypto_wipe(key, 32);
	result = ctr_build_string_from_cstring((char*)out);
	crypto_wipe(out, mlen);
	ctr_heap_free(out);
	clean:
	ctr_heap_free(in64);
	ctr_heap_free(in);
	crypto_wipe((unsigned char*)password, strlen(password)); // cast away unsignedness for strlen
	ctr_heap_free(password);
	crypto_wipe(message, mlen);
	ctr_heap_free(message);
	return result;
}

/**
 * @def
 * [ Vault ] password-hash: [ String ]
 *
 * @test669
 */
ctr_object* ctr_server_vault_password_hash(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* result = CtrStdNil;
	uint8_t hash[32];
	uint8_t salt[16];
	uint8_t* password;
	char* out64 = NULL;
	password = (unsigned char*) ctr_heap_allocate_cstring( ctr_internal_cast2string(argumentList->object) );
	if (strlen((char*)password) < 1) {
		ctr_error("Empty password string.", 0);
		goto cleanup;
	}
	if (random_buf(salt, 16) == -1) {
		ctr_error("Unable to generate secure random buffer.",0);
		goto cleanup;
	}
	if (ctr_gui_vault_internal_derive_key(password, hash, salt)==-1) {
		ctr_error("Unable to hash password.", 0);
		goto cleanup;
	}
	uint8_t buf[48];
	memcpy(buf, hash, 32);
	memcpy(buf+32, salt, 16);
	size_t outlen64 = BASE64_ENCODE_OUT_SIZE(48);
	out64 = ctr_heap_allocate(outlen64 + 7 + 1);
	unsigned int bytes_encoded;
	bytes_encoded = base64_encode((unsigned char*)buf, 48, out64+7);
	if (bytes_encoded == 0) {
		ctr_error("base64 encoding failed", 0);
		goto cleanup;
	}
	out64[outlen64+7] = 0;
	memcpy(out64, SERVER_VAULT_CRYPTO_ID_20262, 7); //prefix
	result = ctr_build_string_from_cstring(out64);
	cleanup:
		if (out64) ctr_heap_free(out64);
		crypto_wipe((unsigned char*)password, strlen((char*)password));
		ctr_heap_free(password);
	
	return result;
}

/**
 * @def
 * [ Vault ] password-hash: [ String ] verify: [ String ]
 *
 * @test669
 */
ctr_object* ctr_server_vault_password_verify(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* result = CtrStdBoolFalse;
	uint8_t* salt;
	uint8_t* hash;
	uint8_t  hash2[32];
	uint8_t* phash64;
	char* pxphash64 = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	char* verify = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->object));
	uint8_t* phash = ctr_heap_allocate(48);
	if (strncmp(pxphash64,SERVER_VAULT_CRYPTO_ID_20262,7)!=0){
		ctr_error("Unknown password type", 0);
		goto cleanup;
	}
	phash64 = (uint8_t*) pxphash64 + 7;
	if (base64_decode((char*)phash64, strlen((char*)phash64), (unsigned char*)phash)!=48) {
		ctr_error("Decoding error",0);
		goto cleanup;
	}
	hash = phash;
	salt = phash + 32;
	if (ctr_gui_vault_internal_derive_key((unsigned char*)verify, hash2, salt)!=0) {
		ctr_error("Unable to derive key",0);
		goto cleanup;
	}
	result = ctr_build_bool( !crypto_verify32(hash, hash2) );
	cleanup:
	
	ctr_heap_free(pxphash64);
	crypto_wipe(verify, strlen((char*)verify));
	ctr_heap_free(verify);
	ctr_heap_free(phash);
	return result;
}

ctr_object* ctr_server_vault_pki_create(ctr_object* myself, ctr_argument* argumentList) {
	uint8_t seed[32];
	uint8_t sk  [64];
	uint8_t pk  [32];
	char* sk64;
	char* pk64;
	ctr_object* karr = CtrStdNil;
	arc4random_buf(seed, 32);
	crypto_eddsa_key_pair(sk, pk, seed);
	size_t sk64len = BASE64_ENCODE_OUT_SIZE(64);
	sk64 = ctr_heap_allocate(sk64len + 1);
	size_t pk64len = BASE64_ENCODE_OUT_SIZE(32);
	pk64 = ctr_heap_allocate(pk64len + 1);
	if (base64_encode((unsigned char*)sk, 64, sk64)!=sk64len-1 ||
	base64_encode((unsigned char*)pk, 32, pk64)!=pk64len-1) {
		ctr_error("base64 encoding failed", 0);
		goto cleanup;
	}
	ctr_argument a;
	a.object = CtrStdNil;
	a.next = NULL;
	karr = ctr_array_new(CtrStdArray, &a);
	ctr_object* sko = ctr_build_string_from_cstring(sk64);
	a.object = sko;
	ctr_array_push(karr,&a);
	ctr_object* pko = ctr_build_string_from_cstring(pk64);
	a.object = pko;
	ctr_array_push(karr,&a);
	cleanup:
		crypto_wipe(sk,64);
		crypto_wipe(pk,32);
		crypto_wipe(sk64,sk64len);
		crypto_wipe(pk64,pk64len);
		ctr_heap_free(sk64);
		ctr_heap_free(pk64);
	return karr;
}

ctr_object* ctr_server_vault_pki_sign(ctr_object* myself, ctr_argument* argumentList) {
	uint8_t       signature[65];
	char* sig64 = NULL;
	ctr_object* sig = CtrStdNil;
	char* sk64  = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->object));
	uint8_t* msg = (uint8_t*) ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	uint8_t sk[64];
	if (base64_decode(sk64, strlen(sk64), &sk)!=64) {
		ctr_error("base64 decoding failed", 0);
		goto cleanup;
	}
	crypto_eddsa_sign(signature, sk, msg, strlen(msg));
	signature[64] = 0;
	size_t sig64len = BASE64_ENCODE_OUT_SIZE(64);
	sig64 = ctr_heap_allocate(sig64len + 1);
	if (base64_encode(signature, 64, sig64)!=sig64len-1) {
		ctr_error("base64 encoding failed", 0);
		goto cleanup;
	}
	sig = ctr_build_string_from_cstring(sig64);
	cleanup:
		crypto_wipe(sk, 64);
		ctr_heap_free(sk64);
		ctr_heap_free(msg);
		if (sig64) ctr_heap_free(sig64);
	return sig;
}

ctr_object* ctr_server_vault_pki_check(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* check = CtrStdBoolFalse;
	char* msg   = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	char* sig64  = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->object));
	char* pk64 = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->next->object));
	uint8_t pk       [32];
	uint8_t signature[64];
	if (base64_decode(pk64, strlen(pk64), pk)!=32) {
		ctr_error("base64 decoding failed", 0);
		goto cleanup;
	}
	if (base64_decode(sig64, strlen(sig64), signature)!=64) {
		ctr_error("base64 decoding failed", 0);
		goto cleanup;
	}
	check = ctr_build_bool(
		!crypto_eddsa_check(signature, pk, (uint8_t*)msg, strlen(msg))
	);
	cleanup:
		ctr_heap_free(msg);
		ctr_heap_free(pk64);
		ctr_heap_free(sig64);

	return check;
}

/**
 * @def
 * [ Vault ] hash: [ String ] type: [ String ]
 *
 * @test670
 */
ctr_object* ctr_server_vault_hash(ctr_object* myself, ctr_argument* argumentList) {
	uint8_t hash[64];
	size_t hash64len;
	ctr_object* result = CtrStdNil;
	char* message  = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	char* hashtype = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->object));
	char* hash64   = NULL;
	if (strcmp("blake2b", hashtype)!=0) {
		ctr_error("Unsupported hash type, use: blake2b", 0);
		goto cleanup;
	}
	crypto_blake2b(hash, 64, (uint8_t*)message, strlen(message));
	hash64len = BASE64_ENCODE_OUT_SIZE(64);
	hash64 = ctr_heap_allocate(hash64len + 1);
	if (base64_encode(hash, 64, hash64)!=hash64len-1) {
		ctr_error("base64 encoding failed", 0);
		goto cleanup;
	}
	result = ctr_build_string_from_cstring(hash64);
	cleanup:
		if (hash64) ctr_heap_free(hash64);
		ctr_heap_free(hashtype);
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
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "password-hash:" ), &ctr_server_vault_password_hash );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "password-hash:verify:" ), &ctr_server_vault_password_verify );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "edkeys" ), &ctr_server_vault_pki_create );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "sign:with:" ), &ctr_server_vault_pki_sign );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "check:signature:with:" ), &ctr_server_vault_pki_check );
	ctr_internal_create_func(vaultObject, ctr_build_string_from_cstring( "hash:type:" ), &ctr_server_vault_hash );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Vault" ), vaultObject, CTR_CATEGORY_PUBLIC_PROPERTY);
}
