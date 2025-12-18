#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mariadb.h"
#include <server.h>
#include "../../citrine.h"

#define CTR_OBJECT_RESOURCE_MARIADB 41
#define CTR_OBJECT_RESOURCE_MARIADB_STM 42

ctr_object* CtrMariaDB;
ctr_object* CtrMariaDBQuery;

void ctr_mariadb_destructor(ctr_resource* rs) {
	//@no need
}

void ctr_mariadb_stm_destructor(ctr_resource* rs) {
	//@no need
}

// Define classes
CTR_DEFINE_CLASS_OTEX(ctr_mariadb_new, CTR_OBJECT_RESOURCE_MARIADB, ctr_mariadb_destructor);
CTR_DEFINE_CLASS_OTEX(ctr_mariadb_query_new, CTR_OBJECT_RESOURCE_MARIADB_STM, ctr_mariadb_stm_destructor);

// Define setters
CTR_DEFINE_SETTER_CAST(ctr_mariadb_host_set,        "host", ctr_internal_copy2string);
CTR_DEFINE_SETTER_CAST(ctr_mariadb_username_set,    "username", ctr_internal_copy2string);
CTR_DEFINE_SETTER_CAST(ctr_mariadb_password_set,    "password", ctr_internal_copy2string);
CTR_DEFINE_SETTER_CAST(ctr_mariadb_dbname_set,      "dbname", ctr_internal_copy2string);
CTR_DEFINE_SETTER_CAST(ctr_mariadb_query_query_set, "query", ctr_internal_copy2string);
CTR_DEFINE_SETTER(ctr_mariadb_query_database_set,   "database");
CTR_DEFINE_SETTER(ctr_mariadb_query_param_set,      "parameters");

ctr_object* ctr_mariadb_connected(ctr_object* myself, ctr_argument* argumentList) {
	MYSQL* conn;
	conn = (MYSQL*) myself->value.rvalue->ptr;
	return ctr_build_bool( conn != NULL );
}

ctr_object* ctr_mariadb_connect(ctr_object* myself, ctr_argument* argumentList) {
	MYSQL* conn;
	conn = mysql_init(NULL);
	myself->value.rvalue->ptr = (void*) conn;
	char* host;
	char* user;
	char* pass;
	char* name;
	ctr_object* prop;
	prop = ctr_internal_object_property(myself, "host", NULL);
	if (prop == CtrStdNil) {
		ctr_error("Cannot connect to MariaDB: no hostname, use hostname: to specify hostname.", 0);
		return CtrStdNil;
	}
	host = ctr_heap_allocate_cstring(prop);
	prop = ctr_internal_object_property(myself, "username", NULL);
	if (prop == CtrStdNil) {
		ctr_error("Cannot connect to MariaDB: no username, use username: to specify username.", 0);
		ctr_heap_free(host);
		return CtrStdNil;
	}
	user = ctr_heap_allocate_cstring(prop);
	prop = ctr_internal_object_property(myself, "password", NULL);
	if (prop == CtrStdNil) {
		ctr_error("Cannot connect to MariaDB: no password, use password: to specify password.", 0);
		ctr_heap_free(host);
		ctr_heap_free(user);
		return CtrStdNil;
	}
	pass = ctr_heap_allocate_cstring(prop);
	prop = ctr_internal_object_property(myself, "dbname", NULL);
	if (prop == CtrStdNil) {
		ctr_error("Cannot connect to MariaDB: no database name, use dbname: to specify name.", 0);
		ctr_heap_free(host);
		ctr_heap_free(user);
		ctr_heap_free(pass);
		return CtrStdNil;
	}
	name = ctr_heap_allocate_cstring(prop);
    if (mysql_real_connect(conn,
                           host,
                           user,
                           pass,
                           name,
                           0, NULL, 0) == NULL) {
        ctr_error(mysql_error(conn), 0);
        mysql_close(conn);
        myself->value.rvalue->ptr = NULL;
    } else {
		myself->value.rvalue->ptr = conn;
	}
	//@fixme, conn = NULL!
	if (mysql_autocommit(conn, 0) != 0) {
		ctr_error("Failed to start transactional database mode (autocommit is ON)", 0);
	}
	ctr_heap_free(host);
	ctr_heap_free(user);
	ctr_heap_free(pass);
	ctr_heap_free(name);
	return myself;
}

ctr_object* ctr_mariadb_query_new_set(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* query = ctr_mariadb_query_new(myself, argumentList);
	ctr_mariadb_query_query_set(query, argumentList);
	return query;
}

ctr_object* ctr_mariadb_query_tostring(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_internal_object_property(myself, "query", NULL);
}

ctr_object* ctr_mariadb_query_insert_id(ctr_object* myself, ctr_argument* argumentList) {
	MYSQL_STMT* prepared_statement;
	ctr_object* insert_id;
	my_ulonglong id;
	char* str;
	insert_id = CtrStdNil;
	if (myself->value.rvalue->ptr) {
		prepared_statement = (MYSQL_STMT*) myself->value.rvalue->ptr;
		id = mysql_stmt_insert_id(prepared_statement);
		str = ctr_heap_allocate(32);
		snprintf(str, 32, "%llu", id);
		insert_id = ctr_build_string_from_cstring(str);
		ctr_heap_free(str);
	}
	return insert_id;
}


ctr_object* ctr_internal_mariadb_execute(ctr_object* myself, ctr_argument* argumentList, int fetch_mode) {
	int            count;
	MYSQL_BIND*    parambinds = NULL;
	ctr_argument*  positionArgument;
	ctr_object*    positionIndex;
	ctr_object*    parameter;
	ctr_object*    parameterValue;
	ctr_object*    queryobj;
	unsigned int   num_fields;
	unsigned long* plens;
	MYSQL_BIND* rbindings;
	void **rbuffers;
	unsigned long *rlens;
	my_bool *rnull;
	queryobj = ctr_internal_object_property(myself, "query", NULL);
	if (queryobj == CtrStdNil) {
		ctr_error("No Query", 0);
		return CtrStdNil;
	}
	ctr_object* database = ctr_internal_object_property(myself, "database", NULL);
	if (database == CtrStdNil) {
		ctr_error("No Database", 0);
		return CtrStdNil;
	}
	MYSQL *conn;
	conn = (MYSQL*) database->value.rvalue->ptr;
	if (conn == NULL) {
		ctr_error("No active connection", 0);
		return CtrStdNil;
	}
	positionArgument = ctr_heap_allocate(sizeof(ctr_argument));
	char* query = ctr_heap_allocate_cstring(ctr_internal_copy2string(queryobj));
	unsigned long query_length = (unsigned long) queryobj->value.svalue->vlen;
	ctr_object* params = ctr_internal_object_property(myself,"parameters",NULL);
	if (params->info.type == CTR_OBJECT_TYPE_OTARRAY) {
		count = ctr_tonum( ctr_array_count(params, argumentList) );
		parambinds = ctr_heap_allocate((count) * sizeof(MYSQL_BIND));
		plens = ctr_heap_allocate(count * sizeof(unsigned long));
		for (int i = 0; i < count; i ++) {
			positionIndex = ctr_build_number_from_float((double) i);
			positionArgument->object = positionIndex;
			positionArgument->next = NULL;
			parameter = ctr_array_get(params, positionArgument);
			parameterValue = ctr_internal_cast2string(parameter);
			char* pval = ctr_heap_allocate_cstring(parameterValue);
			MYSQL_BIND* binding = parambinds + i;
			binding->buffer_type = MYSQL_TYPE_STRING;
			binding->buffer = (char*) pval;
			binding->buffer_length = strlen(pval) + 1;
			plens[i] = strlen(pval);
			binding->length = &plens[i];
		}
	}
	MYSQL_STMT* prepared_statement = mysql_stmt_init(conn);
	if (!prepared_statement) {
		ctr_error("Failed to create prepared statement", 0);
		goto free_query;
	}
	myself->value.rvalue->ptr = (void*) prepared_statement;
	if (mysql_stmt_prepare(prepared_statement,query, query_length)) {
		ctr_error(mysql_stmt_error(prepared_statement), 0);
        return CtrStdNil;
	}
    if (mysql_stmt_bind_param(prepared_statement, parambinds)) {
        ctr_error(mysql_stmt_error(prepared_statement),0);
        return CtrStdNil;
	}
	if (mysql_stmt_execute(prepared_statement)) {
       ctr_error(mysql_stmt_error(prepared_statement),0);
       return CtrStdNil;
    }
	if (fetch_mode) {
		MYSQL_RES* rparams = mysql_stmt_result_metadata(prepared_statement);
		if (!rparams) {
			ctr_error(mysql_stmt_error(prepared_statement),0);
			return CtrStdNil;
		} else {
			num_fields = mysql_num_fields(rparams);
			MYSQL_FIELD* rfields = mysql_fetch_fields(rparams);
			rbindings = ctr_heap_allocate(num_fields * sizeof(MYSQL_BIND));
			rbuffers = ctr_heap_allocate(num_fields * sizeof(void*));
			rlens = ctr_heap_allocate(num_fields * sizeof(unsigned long));
			rnull = ctr_heap_allocate(num_fields * sizeof(my_bool));
			for (unsigned int r = 0; r < num_fields; r++) {
				rbindings[r].buffer_type = rfields[r].type;
				unsigned long max_len = rfields[r].max_length;
				if (max_len < 128) max_len = 128;
				rbuffers[r] = ctr_heap_allocate(max_len + 1);
				rbindings[r].buffer = rbuffers[r];
				rbindings[r].buffer_length = max_len + 1;
				rbindings[r].length = &rlens[r];
				rbindings[r].is_null = &rnull[r];
			}
			if (mysql_stmt_bind_result(prepared_statement, rbindings)) {
				ctr_error(mysql_stmt_error(prepared_statement),0);
				return CtrStdNil;
			}
			ctr_argument* resultArgs;
			resultArgs = ctr_heap_allocate(sizeof(ctr_argument));
			resultArgs->object = CtrStdNil;
			resultArgs->next = NULL;
			ctr_argument* none = ctr_heap_allocate(sizeof(ctr_argument));
			none->object = NULL;
			none->next = NULL;
			ctr_argument* map_entry_val = ctr_heap_allocate(sizeof(ctr_argument));
			ctr_argument* map_entry_key = ctr_heap_allocate(sizeof(ctr_argument));
			map_entry_val->next = map_entry_key;
			map_entry_key->next = NULL;
			while (1) {
				int s = mysql_stmt_fetch(prepared_statement);
				if (s == MYSQL_NO_DATA) break;
				if (s == MYSQL_DATA_TRUNCATED)
				fprintf(stderr, "Warning: truncated data\n");
				if (s == 1) {
					ctr_error(mysql_stmt_error(prepared_statement),0);
					goto free_rbuffers;
				}
				ctr_object* map = ctr_map_new(CtrStdMap, none);
				for (unsigned int i = 0; i < num_fields; i++) {
					map_entry_key->object = ctr_build_string_from_cstring(rfields[i].name);
					if (rnull[i]) {
						map_entry_val->object = CtrStdNil;
					} else {
						switch (rfields[i].type) {
							case MYSQL_TYPE_LONG:
							case MYSQL_TYPE_LONGLONG:
								map_entry_val->object = ctr_build_number_from_float((double)*(int*)rbuffers[i]);
								break;
							case MYSQL_TYPE_DOUBLE:
							case MYSQL_TYPE_FLOAT:
								map_entry_val->object = ctr_build_number_from_float(*(double*)rbuffers[i]);
								break;
							default: {
								map_entry_val->object = ctr_build_string((char*) rbuffers[i], rlens[i]);
								break;
							}
						}
					}
					ctr_map_put(map, map_entry_val);
				}
				resultArgs->object = map;
				ctr_block_run(argumentList->object, resultArgs, argumentList->object);
			}
			ctr_heap_free(map_entry_val);
			ctr_heap_free(map_entry_key);
			ctr_heap_free(resultArgs);
			ctr_heap_free(none);
			
			free_rbuffers:
			for (unsigned int r = 0; r < num_fields; r++) {
				ctr_heap_free(rbuffers[r]);
			}
			ctr_heap_free(rbuffers);
			ctr_heap_free(rbindings);
			ctr_heap_free(rlens);
			ctr_heap_free(rnull);
			mysql_free_result(rparams);
		} //fetch mode
	}
	free_query:
	if (parambinds) {
		for(int i = 0; i<count; i++) {
			ctr_heap_free(parambinds[i].buffer);
		}
		ctr_heap_free(parambinds);
		ctr_heap_free(plens);
	}
	ctr_heap_free(positionArgument);
	ctr_heap_free(query);
	return myself;
}

ctr_object* ctr_mariadb_query_execute(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_internal_mariadb_execute(myself, argumentList, 0);
}

ctr_object* ctr_mariadb_query_fetch(ctr_object* myself, ctr_argument* argumentList) {
	return ctr_internal_mariadb_execute(myself, argumentList, 1);
}

ctr_object* ctr_mariadb_query_close(ctr_object* myself, ctr_argument* argumentList) {
	MYSQL_STMT* prepared_statement;
	ctr_object* ok = CtrStdBoolFalse;
	if (myself->value.rvalue->ptr) {
		prepared_statement = (MYSQL_STMT*) myself->value.rvalue->ptr;
		ok = ctr_build_bool( ( ( (int) mysql_stmt_close(prepared_statement) ) == 0 ) );
		if (ok) {
			myself->value.rvalue->ptr = NULL;
		}
	}
	return ok;
}

ctr_object* ctr_mariadb_query_set(ctr_object* myself, ctr_argument* argumentList) {
	ctr_object* query = ctr_mariadb_query_new_set(CtrMariaDBQuery, argumentList);
	ctr_argument a;
	a.object = myself;
	a.next = NULL;
	ctr_mariadb_query_database_set(query, &a);
	return query;
}

ctr_object* ctr_mariadb_close(ctr_object* myself, ctr_argument* argumentList) {
	MYSQL *conn;
	if (myself->value.rvalue->ptr) {
		conn = (MYSQL*) myself->value.rvalue->ptr;
		mysql_close(conn);
		myself->value.rvalue->ptr = NULL;
	}
	return CtrStdBoolTrue;
}

ctr_object* ctr_mariadb_commit(ctr_object* myself, ctr_argument* argumentList) {
	MYSQL *conn;
	if (myself->value.rvalue->ptr) {
		conn = (MYSQL*) myself->value.rvalue->ptr;
		if (mysql_commit(conn) != 0) {
			ctr_error("Transaction Failed", 0);
			return CtrStdNil;
		}
	}
	return myself;
}

ctr_object* ctr_mariadb_rollback(ctr_object* myself, ctr_argument* argumentList) {
	MYSQL *conn;
	if (myself->value.rvalue->ptr) {
		conn = (MYSQL*) myself->value.rvalue->ptr;
		if (mysql_rollback(conn) != 0) {
			ctr_error("Rollback Failed", 0);
			return CtrStdNil;
		}
	}
	return myself;
}

void begin_mariadb(){
	CtrMariaDB = ctr_internal_create_object(CTR_OBJECT_TYPE_OTEX);
	CtrMariaDB->value.rvalue = NULL;
	CtrMariaDBQuery = ctr_internal_create_object(CTR_OBJECT_TYPE_OTEX);
	CtrMariaDBQuery->value.rvalue = NULL;
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "new" ), &ctr_mariadb_new );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "host:" ), &ctr_mariadb_host_set );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "username:" ), &ctr_mariadb_username_set );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "password:" ), &ctr_mariadb_password_set );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "dbname:" ), &ctr_mariadb_dbname_set );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "connect" ), &ctr_mariadb_connect );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "query:" ), &ctr_mariadb_query_set );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "connected?" ), &ctr_mariadb_connected );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "commit" ), &ctr_mariadb_commit );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "rollback" ), &ctr_mariadb_rollback );
	ctr_internal_create_func(CtrMariaDB, ctr_build_string_from_cstring( "close" ), &ctr_mariadb_close );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "new" ), &ctr_mariadb_query_new );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "new:" ), &ctr_mariadb_query_new_set );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "database:" ), &ctr_mariadb_query_database_set );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "query:" ), &ctr_mariadb_query_query_set );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "string" ), &ctr_mariadb_query_tostring );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "parameters:" ), &ctr_mariadb_query_param_set );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "execute" ), &ctr_mariadb_query_execute );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "fetch:" ), &ctr_mariadb_query_fetch );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "insert-id" ), &ctr_mariadb_query_insert_id );
	ctr_internal_create_func(CtrMariaDBQuery, ctr_build_string_from_cstring( "close" ), &ctr_mariadb_query_close );
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Maria-DB" ), CtrMariaDB, CTR_CATEGORY_PUBLIC_PROPERTY);
	ctr_internal_object_add_property(CtrStdWorld, ctr_build_string_from_cstring( "Maria-Query" ), CtrMariaDBQuery, CTR_CATEGORY_PUBLIC_PROPERTY);
	CtrMariaDB->link = CtrStdObject;
	CtrMariaDB->info.sticky = 1;
	CtrMariaDBQuery->link = CtrStdObject;
	CtrMariaDBQuery->info.sticky = 1;
}