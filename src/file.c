#include "xo.h"

/**
 * @def
 * File
 *
 *
 * @test536
 */


ctr_object* ctr_file_new(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* s = ctr_object_make(myself, argumentList);
	ctr_object* pathObject;
	s->info.type = CTR_OBJECT_TYPE_OTEX; /* indicates resource for GC */
	s->link = myself;
	s->value.rvalue = NULL;
	pathObject = ctr_internal_cast2string( argumentList->object );
	ctr_internal_object_add_property( s, ctr_build_string_from_cstring( "path" ), pathObject, 0 );
	return s;
}

/**
 * @def
 * [ File ] path
 *
 *
 * @test538
 */

ctr_object* ctr_file_path(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	if (path == NULL) return CtrStdNil;
	return path;
}

/**
 * @def
 * [ File ] string
 * 
 *
 * @test539
 */

ctr_object* ctr_file_to_string(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_file_path(myself,argumentList);
	if ( path == CtrStdNil) {
		return ctr_build_string_from_cstring( CTR_SYM_FILE );
	}
	return ctr_internal_cast2string(path);
}

/**
 * @def
 * [ File ] read
 *
 *
 * @test540
 */

ctr_object* ctr_file_read(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	ctr_object* str;
	ctr_size fileLen;
	char* pathString;
	char *buffer;
	size_t bytesRead;
	FILE* f;
	int error_code;
	if (path == NULL) return CtrStdNil;
	pathString = ctr_heap_allocate_cstring( path );
	f = fopen(pathString, "rb");
	error_code = errno;
	ctr_heap_free( pathString );
	if (!f) {
		ctr_error( CTR_ERR_OPEN, error_code );
		return CtrStdNil;
	}
	fseek(f, 0, SEEK_END);
	fileLen=ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer=(char *)ctr_heap_allocate(fileLen+1);
	if (!buffer){
		fprintf(stderr, CTR_ERR_OOM );
		fclose(f);exit(1);
	}
	bytesRead = fread(buffer, 1, fileLen, f);
	fclose(f);
	if (bytesRead != fileLen) {
		ctr_error( CTR_ERR_OPEN, error_code );
		ctr_heap_free( buffer );
		return CtrStdNil;
	}
	str = ctr_build_string(buffer, fileLen);
	ctr_heap_free( buffer );
	return str;
}

/**
 * @def
 * [ File ] write: [ String ]
 *
 *
 * @test541
 */

ctr_object* ctr_file_write(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* str = ctr_internal_cast2string(argumentList->object);
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0 );
	FILE* f;
	ctr_size vlen;
	char* pathString;
	int error_code;
	if (path == NULL) return CtrStdNil;
	vlen = path->value.svalue->vlen;
	pathString = ctr_heap_allocate(vlen + 1);
	memcpy(pathString, path->value.svalue->value, vlen);
	memcpy(pathString+vlen,"\0",1);
	f = fopen(pathString, "wb+");
	error_code = errno;
	ctr_heap_free( pathString );
	if (!f) {
		CtrStdFlow = ctr_error( CTR_ERR_OPEN, error_code );
		return CtrStdNil;
	}
	fwrite(str->value.svalue->value, sizeof(char), str->value.svalue->vlen, f);
	fclose(f);
	return myself;
}

/**
 * @def
 * [ File ] tempwrite: [ String ]
 *
 *
 * @test682
 */

ctr_object* ctr_file_tempwrite(ctr_object* myself, ctr_argument* argumentList) {
	char path[] = "/tmp/xotempXXXXXX";
	int f = mkstemp(path);
	if (f == -1) {
		ctr_error("Unable to create temporary file", 0);
		return CtrStdNil;
	}
	ctr_object* str = ctr_internal_cast2string(argumentList->object);
	write(f,str->value.svalue->value, str->value.svalue->vlen);
	close(f);
	ctr_argument a;
	a.object = ctr_build_string_from_cstring(path);
	a.next = NULL;
	return ctr_file_new(CtrStdFile, &a);
}

/**
 * @def
 * [ File ] append: [ String ]
 *
 *
 * @test542
 */

ctr_object* ctr_file_append(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* str = ctr_internal_cast2string(argumentList->object);
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	int error_code;
	char* pathString;
	FILE* f;
	if (path == NULL) return myself;
	pathString = ctr_heap_allocate_cstring( path );
	f = fopen(pathString, "ab+");
	error_code = errno;
	ctr_heap_free( pathString );
	if (!f) {
		CtrStdFlow = ctr_error( CTR_ERR_OPEN, error_code );
		return CtrStdNil;
	}
	fwrite(str->value.svalue->value, sizeof(char), str->value.svalue->vlen, f);
	fclose(f);
	return myself;
}

/**
 * @def
 * [ File ] exists
 *
 *
 * @test543
 */

ctr_object* ctr_file_exists(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	char* pathString;
	FILE* f;
	int exists;
	if (path == NULL) return CtrStdBoolFalse;
	pathString = ctr_heap_allocate_cstring( path );
	f = fopen(pathString, "r");
	ctr_heap_free( pathString );
	exists = (f != NULL );
	if (f) {
		fclose(f);
	}
	return ctr_build_bool(exists);
}

/**
 * @def
 * [ File ] delete
 * 
 *
 * @test544
 */

ctr_object* ctr_file_delete(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	char* pathString;
	int r;
	if (path == NULL) return myself;
	pathString = ctr_heap_allocate_cstring( path );
	r = remove(pathString);
	ctr_heap_free( pathString );
	if (r!=0) {
		CtrStdFlow = ctr_error( CTR_ERR_DELETE, 0 );
		return CtrStdNil;
	}
	return myself;
}

/**
 * @def
 * [ File ] size
 * 
 *
 * @test545
 */

ctr_object* ctr_file_size(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	char* pathString;
	FILE* f;
	int prev, sz;
	if (path == NULL) return ctr_build_number_from_float(0);
	pathString = ctr_heap_allocate_cstring( path );
	f = fopen(pathString, "r");
	ctr_heap_free( pathString );
	if (f == NULL) return ctr_build_number_from_float(0);
	prev = ftell(f);
	fseek(f, 0L, SEEK_END);
	sz=ftell(f);
	fseek(f,prev,SEEK_SET);
	if (f) {
		fclose(f);
	}
	return ctr_build_number_from_float( (ctr_number) sz );
}

/**
 * @def
 * [ File ] list: [ String ]
 * 
 *
 * @test546
 */

ctr_object* ctr_file_list(ctr_object* myself, ctr_argument* argumentList) {
	/**
	 * Returns a list with strings, not file objects, because
	 * there can be all sorts of objects in a folder and only
	 * files are represented by objects. If we would have returned
	 * objects, we would need objects for File, Folder, Link,
	 * Device etc. (depending on OS). Since Citrine only offers
	 * a limited IO-interface (because of minimalism and it might just
	 * as well be embedded into FAAS/SAAS, not needing any of this)
	 * this would quickly go beyond the scope of the project.
	 */
	DIR* d;
	struct dirent* entry;
	char* pathValue;
	char  pathBuf[PATH_MAX + 1];
	char  fullPath[PATH_MAX + 1];
	ctr_object* fileList;
	ctr_object* fileListItem;
	ctr_object* path;
	ctr_argument* putArgumentList;
	ctr_argument* addArgumentList;
	path = ctr_internal_cast2string( argumentList->object );
	fileList = ctr_array_new(CtrStdArray, NULL);
	pathValue = ctr_heap_allocate_cstring( path );
	struct stat st;
	d = opendir( pathValue );
	if (d == 0) {
		int error_code = errno;
		CtrStdFlow = ctr_error( CTR_ERR_OPEN, error_code );
		ctr_heap_free(pathValue);
		return CtrStdNil;
	}
	putArgumentList = ctr_heap_allocate( sizeof( ctr_argument ) );
	addArgumentList = ctr_heap_allocate( sizeof( ctr_argument ) );
	putArgumentList->next = ctr_heap_allocate( sizeof( ctr_argument ) );
	while((entry = readdir(d))) {
		fileListItem = ctr_map_new(CtrStdMap, NULL);
		putArgumentList->next->object = ctr_build_string_from_cstring( CTR_MSG_DSC_FILE );
		putArgumentList->object = ctr_build_string_from_cstring(entry->d_name);
		ctr_map_put(fileListItem, putArgumentList);
		putArgumentList->next->object = ctr_build_string_from_cstring( CTR_MSG_DSC_TYPE );
		if ((strlen(CTR_DIRSEP) + strlen(CTR_DIRSEP) + strlen(entry->d_name)) > PATH_MAX) {
			continue;
		}
		strcpy( fullPath, pathValue );
		strcat( fullPath, CTR_DIRSEP );
		strcat( fullPath, entry->d_name);
		if (realpath( fullPath, pathBuf )) {
		/* lstat is slow, but we have no choice, there is no other way to keep this portable */
		lstat(pathBuf, &st);
		if (S_ISREG(st.st_mode))
			putArgumentList->object = ctr_build_string_from_cstring( CTR_MSG_DSC_FILE );
		else if (S_ISDIR(st.st_mode))
			putArgumentList->object = ctr_build_string_from_cstring( CTR_MSG_DSC_FLDR );
		else if (S_ISLNK(st.st_mode))
			putArgumentList->object = ctr_build_string_from_cstring( CTR_MSG_DSC_SLNK );
		else if (S_ISCHR(st.st_mode))
			putArgumentList->object = ctr_build_string_from_cstring( CTR_MSG_DSC_CDEV );
		else if (S_ISBLK(st.st_mode))
			putArgumentList->object = ctr_build_string_from_cstring( CTR_MSG_DSC_BDEV );
		else if (S_ISSOCK(st.st_mode))
			putArgumentList->object = ctr_build_string_from_cstring( CTR_MSG_DSC_SOCK );
		else if (S_ISFIFO(st.st_mode))
			putArgumentList->object = ctr_build_string_from_cstring( CTR_MSG_DSC_NPIP );
		else
			putArgumentList->object = ctr_build_string_from_cstring( CTR_MSG_DSC_OTHR );
		ctr_map_put(fileListItem, putArgumentList);
		addArgumentList->object = fileListItem;
		ctr_array_push(fileList, addArgumentList);
		}
	}
	closedir(d);
	ctr_heap_free(putArgumentList->next);
	ctr_heap_free(putArgumentList);
	ctr_heap_free(addArgumentList);
	ctr_heap_free(pathValue);
	return fileList;
}

/**
 * @def
 * 
 * [ File ] lines: [ Code ]
 *
 * @test547
 */
ctr_object* ctr_file_lines(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path;
	ctr_argument* lineArg;
	ctr_object* lineObj ;
	char* pathString;
	FILE* f;
	int error_code;
	char* line = NULL;
	size_t linesize = 0;
	ssize_t linelen;
	path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	if (path == NULL) return CtrStdNil;
	pathString = ctr_heap_allocate_cstring( path );
	f = fopen(pathString, "r");
	error_code = errno;
	ctr_heap_free( pathString );
	if (!f) {
		ctr_error( CTR_ERR_OPEN, error_code );
		return CtrStdNil;
	}
	lineArg = ctr_heap_allocate(sizeof(ctr_argument));
	while ((linelen = getline(&line, &linesize, f)) != -1) {
		lineObj = ctr_build_string(line, (ctr_size) linelen - 1);
		lineObj->info.sticky = 1;
		lineArg->object = lineObj;
		lineArg->next = NULL;
		ctr_block_run(argumentList->object, lineArg, NULL);
		if (CtrStdFlow == CtrStdContinue) CtrStdFlow = NULL; /* consume continue */
		if (CtrStdFlow) break;
	}
	ctr_heap_free(lineArg);
	if (line) free(line);
	fclose(f);
	return myself;	
}

/**
 * @def
 * [ File ] delimiter: [ String ] quote: [ String ] lines: [ Function ]
 *
 * @test675
 */
ctr_object* ctr_file_csvlines( ctr_object* myself, ctr_argument* argumentList ) {
	ctr_object* path;
	ctr_object* result;
	ctr_argument a;
	ctr_argument cba;
	size_t bufsize;
	char* pathstr;
	FILE* f;
	char  error_message[200];
	char* delim;
	char* quote;
	char* buf;
	char q;
	char d;
	char c;
	int error_code;
	size_t row;
	size_t col;
	int eof;
	int st;
	int o;
	int p;
	size_t headers;
	size_t columns;
	size_t line;
	path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	if (path == NULL) return CtrStdNil;
	pathstr = ctr_heap_allocate_cstring( path );
	f = fopen(pathstr, "r");
	error_code = errno;
	ctr_heap_free( pathstr );
	if (!f) {
		ctr_error( CTR_ERR_OPEN, error_code );
		return CtrStdNil;
	}
	delim = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	quote = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->object));
	buf = NULL;
	if (strlen(quote)!=1 || strlen(delim)!=1) {
		ctr_error("Invalid delimiter or quote.", 0);
		goto cleanup;
	}
	bufsize = 10;
	buf = ctr_heap_allocate(bufsize);
	eof = 0;
	st = 0;
	q = quote[0];
	d = delim[0];
	o = 0;
	p = 0;
	row = 0;
	col = 0;
	headers = 0;
	columns = 0;
	line = 0;
	result = ctr_array_new(CtrStdArray, argumentList);
	for(;;) {
		o = fgetc(f);
		col++;
		if (o == EOF) eof = 1;
		c = (char) o;
		if (c == '\n') { col = 0; line++; }
		if (st == 3) {
			st = 0;
			if (c == '\n') {
				continue;
			}
		}
		if (st == 0 && c == q) {
			st = 1;
			continue;
		}
		if (st == 1 && c == q) {
			st = 2;
			continue;
		}
		if (st == 2 && c == q) {
			st = 1;
		}
		if (st != 1 && (c == d || c == '\r' || c == '\n' || eof)) {
			buf[p] = 0;
			a.object = ctr_build_string_from_cstring(buf);
			a.next = NULL;
			ctr_array_push(result, &a);
			p = 0;
			st = 0;
			columns++;
			if (c == '\r' || c == '\n' || eof) {
				if (row == 0) {
					headers = columns;
				} else if (headers != columns) {
					snprintf(error_message, 200, "Invalid column number on line %ld (expected: %ld got: %ld) \n", row, headers,columns);
					ctr_error(error_message, 0);
					goto cleanup;
				}
				row++;
				columns = 0;
				col = 0;
				cba.object = result;
				cba.next = NULL;
				ctr_internal_object_property(myself, "csvline", result); // prevent GC for whole line (array + elements)
				ctr_block_run(argumentList->next->next->object, &cba, NULL);
				if (CtrStdFlow == CtrStdContinue) CtrStdFlow = NULL; // consume continue
				if (CtrStdFlow) break;
				if (c == '\r') st = 3;
				if (eof) break;
				result = ctr_array_new(CtrStdArray, argumentList);
			}
			continue;
		}
		if (st == 2) {
			snprintf(error_message, 200, "Unexpected 0x0%x at line: %ld character: %ld", c, line, col);
			ctr_error(error_message, 0);
			goto cleanup;
		}
		buf[p++] = c;
		if (p >= bufsize) {
			bufsize *= 2;
			buf = ctr_heap_reallocate( buf, bufsize );
		}
	}
	cleanup:
		fclose(f);
		ctr_heap_free(delim);
		ctr_heap_free(quote);
		if (buf) ctr_heap_free(buf);
	return myself;
}

/**
 * @def
 * [ File ] chmod: [ Number ]
 *
 * @test677
 */
ctr_object* ctr_file_chmod(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	int mask = (int) ctr_tonum(argumentList->object);
	char* pathstr;
	if (path == NULL) return myself;
	pathstr = ctr_heap_allocate_cstring( path );
	int err = chmod(pathstr, mask);
	int errcode = errno;
	ctr_heap_free( pathstr );
	if (err) {
		CtrStdFlow = ctr_error( "chmod failed", errcode );
		return CtrStdNil;
	}
	return myself;
}

/**
 * @def
 * [ File ] owner: [ String ] group: [ String ]
 *
 * @test679
 */
ctr_object* ctr_file_chown(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	int mask = (int) ctr_tonum(argumentList->object);
	char* pathstr;
	if (path == NULL) return myself;
	pathstr = ctr_heap_allocate_cstring( path );
	char* owner = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->object));
	char* group = ctr_heap_allocate_cstring(ctr_internal_cast2string(argumentList->next->object));
	struct passwd *pw;
	struct group *gr;
	uid_t uid;
	gid_t gid;
	pw = getpwnam(owner);
	if (!pw) {
		ctr_error("Unknown user id", 0);
		goto cleanup;
	}
	uid = pw->pw_uid;
	gr = getgrnam(group);
	if (!gr) {
		ctr_error("Unknown group id", 0);
		goto cleanup;
	}
	gid = gr->gr_gid;
	if (chown(pathstr, uid, gid) != 0) {
		ctr_error("Chown failed", 0);
		goto cleanup;
	}
	cleanup:
	ctr_heap_free( pathstr );
	ctr_heap_free( owner );
	ctr_heap_free( group );
	return myself;
}

/**
 * @internal
 *
 * Locks a file or unlocks a file.
 * All locking functions use this function under the hood.
 */
ctr_object* ctr_file_lock_generic(ctr_object* myself, ctr_argument* argumentList, int lock) {
	int b;
	int fd;
	char* path;
	ctr_object* pathObj;
	ctr_object* answer;
	ctr_object* fdObj;
	ctr_object* fdObjKey;
	pathObj = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	path = ctr_heap_allocate_cstring( pathObj );
	fdObjKey = ctr_build_string_from_cstring("fileDescriptor");
	fdObj = ctr_internal_object_find_property(
		myself,
		fdObjKey,
		CTR_CATEGORY_PRIVATE_PROPERTY
	);
	if (fdObj == NULL) {
		fd = open( path, O_CREAT );
		fdObj = ctr_build_number_from_float( (ctr_size) fd );
		ctr_internal_object_set_property(
			myself, fdObjKey, fdObj, CTR_CATEGORY_PRIVATE_PROPERTY
		);
	} else {
		fd = (int) fdObj->value.nvalue;
	}
	b = flock( fd, lock );
	if (b != 0) {
		close(fd);
		answer = ctr_build_bool(0);
		ctr_internal_object_delete_property( myself, fdObjKey, CTR_CATEGORY_PRIVATE_PROPERTY );
	} else {
		answer = ctr_build_bool(1);
	}
	ctr_heap_free( path );
	return answer;
}

/**
 * @def
 * [ File ] unlock
 *
 * @test678
 */
ctr_object* ctr_file_unlock(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_file_lock_generic( myself, argumentList, LOCK_UN | LOCK_NB );
}

/**
 * @def
 * [ File ] lock
 *
 * @test678
 */
ctr_object* ctr_file_lock(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_file_lock_generic( myself, argumentList, LOCK_EX | LOCK_NB );
}

/**
 * @def
 * [ File ] stat
 *
 * @test677
 */
ctr_object* ctr_file_stat(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* path = ctr_internal_object_find_property(myself, ctr_build_string_from_cstring( "path" ), 0);
	char* pathstr;
	if (path == NULL) return myself;
	pathstr = ctr_heap_allocate_cstring( path );
	struct stat st;
	int err = stat(pathstr, &st);
	int errcode = errno;
	ctr_heap_free( pathstr );
	if (err) {
		CtrStdFlow = ctr_error( "stat failed", errcode );
		return CtrStdNil;
	}
	ctr_argument a;
	a.next = NULL;
	a.object = NULL;
	ctr_object* info = ctr_map_new(CtrStdMap, &a);
	ctr_argument arg_val;
	ctr_argument arg_key;
	ctr_object* mode = ctr_build_number_from_float( (double) st.st_mode );
	mode->info.sticky = 1; //gc
	arg_val.object = mode;
	arg_val.next = &arg_key;
	ctr_object* mode_key = ctr_build_string_from_cstring("mode");
	mode_key->info.sticky = 1;
	arg_key.object = mode_key;
	arg_key.next = NULL;
	ctr_map_put(info, &arg_val);
	mode->info.sticky = 0;
	mode_key->info.sticky = 0;
	return info;
}
