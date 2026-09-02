#include "xo.h"

int ctr_clex_bflmt = 255;
ctr_size ctr_clex_tokvlen = 0; /* length of the string value of a token */
char* ctr_clex_buffer;
char* ctr_code;
char* ctr_code_start;
char* ctr_code_eoi;

int ctr_clex_line_number;
char* ctr_eofcode;

char* ctr_clex_oldptr;
char* ctr_clex_olderptr;
int ctr_clex_old_line_number = 0;
int ctr_clex_older_line_number = 0;
int ctr_clex_number_of_lines = 0;
char ctr_clex_param_prefix_char;

char* ctr_clex_keyword_me_icon;
char* ctr_clex_keyword_my_icon;
char* ctr_clex_keyword_var_icon;

ctr_size ctr_clen_keyword_assignment_len;
ctr_size ctr_clex_keyword_my_icon_len;
ctr_size ctr_clex_keyword_var_icon_len;

ctr_size ctr_clex_keyword_qo_len;
ctr_size ctr_clex_keyword_qc_len;

int ctr_clex_true_len = 0;
int ctr_clex_false_len = 0;
int ctr_clex_nil_len = 0;

char* ivarname;
int ivarlen;

/**
 * Lexer - is Symbol Delimiter ?
 * Determines whether the specified symbol is a delimiter.
 * Returns 1 if the symbol is a delimiter and 0 otherwise.
 *
 * @param char* code code to be inspected
 *
 * @return uint8_t
 */
uint8_t ctr_clex_is_delimiter( char* code ) {
	if (strncmp(code, CTR_DICT_END_OF_LINE, ctr_clex_keyword_eol_len) == 0) {
		return 1;
	}
	if (strncmp(code, CTR_DICT_QUOT_OPEN, ctr_clex_keyword_qo_len) == 0 ) {
		return 1;
	}
	if (strncmp(code, CTR_DICT_ASSIGN, ctr_clex_keyword_assignment_len) == 0) {
		return 1;
	}
	if (strncmp(code, CTR_DICT_MESSAGE_CHAIN, ctr_clex_keyword_chain_len) == 0 ) {
		return 1;
	}
	char symbol = *(code);
	return (
	   symbol == '('
	|| symbol == ')'
	|| symbol == ctr_clex_param_prefix_char
	|| symbol == ' '
	|| symbol == '\n'
	|| symbol == '\t'
	|| symbol == '\r'
	);
}

/**
 * CTRLexerEmitError
 *
 * Displays an error message for the lexer.
 */
void ctr_clex_emit_error( char* message ) {
	printf(CTR_ERR_LEX, message, ctr_clex_line_number );
	exit(1);
}

/**
 * CTRLexerLoad
 *
 * Loads program into memory.
 */
void ctr_clex_load(char* prg) {
	ctr_clex_true_len = strlen(CTR_DICT_TRUE_OBJECT);
	ctr_clex_false_len = strlen(CTR_DICT_FALSE_OBJECT);
	ctr_clex_nil_len = strlen(CTR_DICT_NIL_OBJECT);
	ctr_code = prg;
	ctr_code_start = prg;
	ctr_clex_buffer = ctr_heap_allocate_tracked(ctr_clex_bflmt);
	ctr_clex_buffer[0] = '\0';
	ctr_eofcode = (ctr_code + ctr_program_length);
	ctr_clex_line_number = 0;
	ctr_code_start = ctr_code;
}

/**
 * CTRLexerTokenValue
 *
 * Returns the string of characters representing the value
 * of the currently selected token.
 */
char* ctr_clex_tok_value() {
	return ctr_clex_buffer;
}

char* ctr_token_descriptions[] = {
	[CTR_TOKEN_RET] = CTR_DICT_RETURN,
	[CTR_TOKEN_ASSIGNMENT] = CTR_DICT_ASSIGN,
	[CTR_TOKEN_BLOCKCLOSE] = CTR_DICT_BLOCK_END,
	[CTR_TOKEN_BLOCKOPEN] = CTR_DICT_BLOCK_START,
	[CTR_TOKEN_BOOLEANNO] = CTR_DICT_FALSE_OBJECT,
	[CTR_TOKEN_BOOLEANYES] = CTR_DICT_TRUE_OBJECT,
	[CTR_TOKEN_CHAIN] = CTR_DICT_MESSAGE_CHAIN,
	[CTR_TOKEN_COLON] = CTR_DICT_PARAMETER_PREFIX,
	[CTR_TOKEN_DOT] = CTR_DICT_END_OF_LINE,
	[CTR_TOKEN_FIN] = "end of program",
	[CTR_TOKEN_NIL] = CTR_DICT_NIL_OBJECT,
	[CTR_TOKEN_NUMBER] = CTR_DICT_NUMBER_OBJECT,
	[CTR_TOKEN_PARCLOSE] = CTR_DICT_PAREN_CLOSE,
	[CTR_TOKEN_PAROPEN] = CTR_DICT_PAREN_OPEN,
	[CTR_TOKEN_QUOTE] = CTR_DICT_QUOT_OPEN,
	[CTR_TOKEN_REF] = "reference",
};

/**
 * CTRLexerTokenDescribe
 *
 * Returns a pointer to a string describing the token.
 */
char* ctr_clex_tok_describe(int token) {
	char* description = ctr_token_descriptions[token];
	if (description==NULL) return "unknown token";
	return description;
}


/**
 * CTRLexerTokenValueLength
 *
 * Returns the length of the value of the currently selected token.
 */
long ctr_clex_tok_value_length() {
	return ctr_clex_tokvlen;
}

/**
 * CTRLexerPutBackToken
 *
 * Puts back a token and resets the pointer to the previous one.
 */
void ctr_clex_putback() {
	ctr_code = ctr_clex_oldptr;
	ctr_clex_oldptr = ctr_clex_olderptr;
	ctr_clex_line_number = ctr_clex_old_line_number;
	ctr_clex_old_line_number = ctr_clex_older_line_number;
}

/**
 * CTRLexerReadToken
 *
 * Reads the next token from the program buffer and selects this
 * token.
 */
int ctr_clex_tok() {
	char c;
	int i;
	char eol;
	ctr_clex_tokvlen = 0;
	ctr_clex_olderptr = ctr_clex_oldptr;
	ctr_clex_oldptr = ctr_code;
	ctr_clex_older_line_number = ctr_clex_old_line_number;
	ctr_clex_old_line_number = ctr_clex_line_number;
	i = 0;
	c = *ctr_code;
	for(;;) {
		while(ctr_code != ctr_eofcode && (isspace(c))) {
			if (c == '\n') ctr_clex_line_number++;
			ctr_code ++;
			c = *ctr_code;
		}
		if (c == '#') {
			while(ctr_code != ctr_eofcode && c!='\n') {
				ctr_code ++;
				c = *ctr_code;
			}
		} else {
			break;
		}
	}
	if (ctr_code == ctr_eofcode) return CTR_TOKEN_FIN;
	if (c == '(') { ctr_code++; return CTR_TOKEN_PAROPEN; }
	if (c == ')') { ctr_code++; return CTR_TOKEN_PARCLOSE; }
	if (c == '{') { ctr_code++; return CTR_TOKEN_BLOCKOPEN; }
	if (c == '}') { ctr_code++; return CTR_TOKEN_BLOCKCLOSE; }
	if (strncmp(ctr_code, CTR_DICT_END_OF_LINE, ctr_clex_keyword_eol_len)==0) {
		ctr_code+=ctr_clex_keyword_eol_len;
		return CTR_TOKEN_DOT;
	}
	if (strncmp(ctr_code, CTR_DICT_MESSAGE_CHAIN, ctr_clex_keyword_chain_len) == 0 ) {
		 ctr_code+=ctr_clex_keyword_chain_len;
		 return CTR_TOKEN_CHAIN;
	}
	if (strncmp(ctr_code, CTR_DICT_ASSIGN, ctr_clex_keyword_assignment_len)==0) {
		ctr_code += ctr_clex_keyword_assignment_len;
		return CTR_TOKEN_ASSIGNMENT; 
	}
	if (strncmp(ctr_code, ":=", 2)==0) {
		ctr_code += 2;
		return CTR_TOKEN_ASSIGNMENT;
	}
	if (c == ctr_clex_param_prefix_char) { ctr_code++; return CTR_TOKEN_COLON; }
	if (strncmp(ctr_code, CTR_DICT_RETURN, ctr_clex_keyword_return_len)==0
	&& ( isspace(*(ctr_code+ctr_clex_keyword_return_len)) )
	) {
		ctr_code += ctr_clex_keyword_return_len;
		return CTR_TOKEN_RET;
	}
	if (strncmp(ctr_code, CTR_DICT_QUOT_OPEN, ctr_clex_keyword_qo_len)==0) {
		ctr_code+=ctr_clex_keyword_qo_len;
		return CTR_TOKEN_QUOTE;
	}
	eol = ( strncmp(ctr_code,CTR_DICT_END_OF_LINE,ctr_clex_keyword_eol_len)==0 );
	if ((c == '-' && (ctr_code+1)<ctr_eofcode && isdigit(*(ctr_code+1))) || isdigit(c)) {
		if (c == '-') {
			ctr_clex_buffer[i] = c; ctr_clex_tokvlen++;
			i++;
			if (i >= ctr_clex_bflmt) {
				ctr_clex_emit_error( CTR_ERR_TOKBUFF );
			}
			ctr_code++;
			c = *ctr_code;
		}
		while(isdigit(c)){
			ctr_clex_buffer[i++] = c;
			ctr_clex_tokvlen++;
			ctr_code++;
			c = *ctr_code;
			if (i >= ctr_clex_bflmt) {
				ctr_clex_emit_error( CTR_ERR_TOKBUFF );
			}
		}
		eol = ( strncmp(ctr_code,CTR_DICT_END_OF_LINE,ctr_clex_keyword_eol_len)==0 );
		if (eol && (ctr_code+ctr_clex_keyword_eol_len <= ctr_eofcode) && !isdigit(*(ctr_code+ctr_clex_keyword_eol_len))) {
			return CTR_TOKEN_NUMBER;
		}
		//Parse decimal separator (turn into international symbol .)
		if (
		((ctr_code+1+1) <= ctr_eofcode) &&
		isdigit(*(ctr_code+1)) &&
		*ctr_code=='.') {
			ctr_clex_buffer[i] = '.'; ctr_clex_tokvlen++;
			i++;
			if (i >= ctr_clex_bflmt) {
				ctr_clex_emit_error( CTR_ERR_TOKBUFF );
			}
			ctr_code++;
			c = *ctr_code;
		}
		
		while((isdigit(c))) {
			ctr_clex_buffer[i] = c; ctr_clex_tokvlen++;
			i++;
			if (i >= ctr_clex_bflmt) {
				ctr_clex_emit_error( CTR_ERR_TOKBUFF );
			}
			ctr_code++;
			c = *ctr_code;
		}
		return CTR_TOKEN_NUMBER;
	}
	while( !ctr_clex_is_delimiter( ctr_code ) && ctr_code!=ctr_eofcode ) {
		ctr_clex_buffer[i] = c;
		if (c == '#' && i > 0) {
			i = 0;
			ctr_clex_tokvlen = 0;
		}
		ctr_clex_tokvlen++;
		i++;
		if (i >= ctr_clex_bflmt) {
			ctr_clex_emit_error( CTR_ERR_TOKBUFF );
		}
		ctr_code++;
		c = *ctr_code;
	}
	return CTR_TOKEN_REF;
}

char* ctr_clex_code_pointer() {
	return ctr_code;
}

/**
 * CTRLexerStringReader
 *
 * Reads an entire string between a pair of quotes.
 */
char* ctr_clex_readstr() {
	ctr_size nesting = 0;
	char* strbuff;
	char c;
	int escape;
	char* beginbuff;
	ctr_size page = 100; /* 100 byte pages */
	ctr_size memblock = 100;
	ctr_clex_tokvlen=0;
	strbuff = (char*) ctr_heap_allocate(memblock);
	beginbuff = strbuff;
	escape = 0;
	while(
		(ctr_code<ctr_eofcode-ctr_clex_keyword_qc_len) &&
		(strncmp(ctr_code, CTR_DICT_QUOT_CLOSE, ctr_clex_keyword_qc_len)!=0 || nesting>0 || escape)
	) {
		c = *ctr_code;
		if ( c == '\n' ) ctr_clex_line_number ++;
		if ( c == '\\' && !escape) {
			escape = 1;
			ctr_code ++;
			continue;
		}
		if ( escape == 1 ) {
			switch(c) {
				case 'n':
					*(strbuff) = '\n';
					ctr_clex_tokvlen += 1;
					strbuff++;
					ctr_code++;
					break;
				case 'r':
					*(strbuff) = '\r';
					ctr_clex_tokvlen += 1;
					strbuff++;
					ctr_code++;
					break;
				case 't':
					*(strbuff) = '\t';
					ctr_clex_tokvlen += 1;
					strbuff++;
					ctr_code++;
					break;
				case 'v':
					*(strbuff) = '\v';
					ctr_clex_tokvlen += 1;
					strbuff++;
					ctr_code++;
					break;
				case 'b':
					*(strbuff) = '\b';
					ctr_clex_tokvlen += 1;
					strbuff++;
					ctr_code++;
					break;
				case 'a':
					*(strbuff) = '\a';
					ctr_clex_tokvlen += 1;
					strbuff++;
					ctr_code++;
					break;
				case 'f':
					*(strbuff) = '\f';
					ctr_clex_tokvlen += 1;
					strbuff++;
					ctr_code++;
					break;
				case '0':
					*(strbuff) = '\0';
					ctr_clex_tokvlen += 1;
					strbuff++;
					ctr_code++;
					break;
				default:
					*(strbuff) = *(ctr_code);
					strbuff++;
					ctr_code++;
					ctr_clex_tokvlen++;
					break;
			}
		}
		else if (!escape && strncmp(ctr_code, "↵", 3)==0) {
			ctr_code += 3;
			ctr_clex_tokvlen += 1;
			*(strbuff) = '\n';
			strbuff++;
		}
		else if (!escape && strncmp(ctr_code, "⇿", 3)==0) {
			ctr_code += 3;
			ctr_clex_tokvlen += 1;
			*(strbuff) = '\t';
			strbuff++;
		}
		else if (strncmp(ctr_code, CTR_DICT_QUOT_CLOSE, ctr_clex_keyword_qc_len)==0) {
			if (!escape) nesting--;
			memcpy(strbuff, CTR_DICT_QUOT_CLOSE, ctr_clex_keyword_qc_len);
			ctr_code += ctr_clex_keyword_qc_len;
			ctr_clex_tokvlen += ctr_clex_keyword_qc_len;
			strbuff += ctr_clex_keyword_qc_len;
		}
		else if (strncmp(ctr_code, CTR_DICT_QUOT_OPEN, ctr_clex_keyword_qo_len)==0) {
			if (!escape) nesting++;
			memcpy(strbuff, CTR_DICT_QUOT_OPEN, ctr_clex_keyword_qo_len);
			ctr_code += ctr_clex_keyword_qo_len;
			ctr_clex_tokvlen += ctr_clex_keyword_qo_len;
			strbuff += ctr_clex_keyword_qo_len;
		} else {
			*(strbuff) = *(ctr_code);
			strbuff++;
			ctr_code++;
			ctr_clex_tokvlen++;
		}
		
		if ((ctr_clex_tokvlen + 10) >= memblock) {
			memblock += page;
			beginbuff = (char*) ctr_heap_reallocate( beginbuff, memblock );
			if (beginbuff == NULL) {
				ctr_clex_emit_error( CTR_ERR_OOM );
			}
			/* reset pointer, memory location might have been changed */
			strbuff = beginbuff + ctr_clex_tokvlen;
		}
		escape = 0;
	}
	/* absorb trailing quote, unless eof encountered - then string ends at eof */
	if (ctr_code<=ctr_eofcode-ctr_clex_keyword_qc_len) {
		ctr_code += ctr_clex_keyword_qc_len;
	}
	return beginbuff;
}
