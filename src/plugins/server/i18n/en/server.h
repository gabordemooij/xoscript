#define CTR_DICT_VAULT_OBJECT                    "Vault"                     // Name of the object used for cryptography
#define CTR_DICT_JSON                            "JSON"                      // Word for object that handles JSON protocol
#define CTR_DICT_PLUGIN_REQUEST                  "HTTP-Request"              // Name of the HTTP-Request object that represents the currently received HTTP request
#define CTR_DICT_NETWORK_OBJECT                  "Net"                       // Name of the Network object, responsible for network services
#define CTR_DICT_BLOB_OBJECT                     "Blob"                      // Object representing a computer memory block
#define CTR_DICT_SERVER_OBJECT                   "Server"
#define CTR_DICT_URL_OBJECT                      "URL"
#define CTR_DICT_DATABASE_MARIADB_OBJECT         "Maria-DB"
#define CTR_DICT_DATABASE_MARIADB_QUERY_OBJECT   "Maria-Query"
#define CTR_DICT_PATTERN_OBJECT                  "Pattern"
#define CTR_DICT_NAME                            "name"                      // Name
#define CTR_DICT_JSONIFY                         "jsonify:"                  // Term to turn objects into a string with JSON encoding
#define CTR_DICT_OBJECT_FROM_SET                 "object:"                   // Term to turn serialized string back into an object
#define CTR_DICT_LINK_SET                        "link:"                     // Word to connect or link something to something else
#define CTR_DICT_BYTES_SET                       "bytes:"                    // Word to change or set the bytes of an object (most likely Blob)
#define CTR_DICT_FREE                            "free"                      // Word to free allocated computer memory
#define CTR_DICT_FREE_STRUCT                     "structfree"                // Term to free allocated c-structure in computer memory
#define CTR_DICT_STRUCT_SET                      "struct:"                   // Term to describe a c-structure in computer memory
#define CTR_DICT_DEREF                           "deref"                     // Term for dereferencing a c pointer
#define CTR_DICT_UTF8_SET                        "utf8:"                     // Word to set utf8 encoded data
#define CTR_DICT_NEW_TYPE_SET                    "new:type:"                 // Phrase to create a new object, passing a size or initial argument and a type argument
#define CTR_DICT_HTTP_REQUEST_GET_SET            "get:"                      // Term to obtain the value of an http search parameter (from a HTTP GET request)
#define CTR_DICT_HTTP_REQUEST_GET_LIST_SET       "get-list:"                 // Term to obtain a list of similary named search parameters (from a HTTP GET request)
#define CTR_DICT_HTTP_REQUEST_COOKIE_SET         "cookie:"                   // Term to obtain the value of an http cookie header
#define CTR_DICT_HTTP_REQUEST_COOKIE_LIST_SET    "cookie-list:"              // Term to obtain a list of similary named cookies
#define CTR_DICT_HTTP_REQUEST_POST_SET           "post:"                     // Term to obtain the value of a form/post field of an HTTP POST request
#define CTR_DICT_HTTP_REQUEST_POST_TO_SET        "post:to:"                  // Term to send an HTTP POST request with the payload specified in argument 1 to the server specified by argument 2
#define CTR_DICT_HTTP_REQUEST_POST_LIST_SET      "post-list:"                // Term to obtain a list of similary named post field values
#define CTR_DICT_HTTP_REQUEST_UPLOAD_SET         "upload:"                   // Term to obtain a list of similary named uploads
#define CTR_DICT_ENCRYPT_KEY_SET                 "encrypt:key:"              // Phrase to encrypt a string in argument 1 with the key in argument 2
#define CTR_DICT_DECRYPT_KEY_SET                 "decrypt:key:"              // Phrase to decrypt a string in argument 1 with the key in argument 2
#define CTR_DICT_TOKEN_SET                       "token:"                    // Word to generate a secure token of the specified length in the argument
#define CTR_DICT_PASSWORD_HASH_SET               "password-hash:"            // Word or phrase to generate a secure hash for a password or secret
#define CTR_DICT_PASSWORD_HASH_VERIFY_SET        "password-hash:verify:"     // Word or phrase to verify if the hash in argument 1 is associated with the secret in argument 2
#define CTR_DICT_EDKEYS                          "edkeys"                    // Term to generate a Ed25519 key pair
#define CTR_DICT_SIGN_WITH_SET                   "sign:with:"                // Phrase to sign the string in argument 1 with the edkey in argument 2
#define CTR_DICT_CHECK_SIGNATURE_SET             "check:signature:with:"     // Phrase to check the signed string in argument 1 with the signature in argument 2 and the private key in argument 3
#define CTR_DICT_HASH_TYPE_SET                   "hash:type:"                // Phrase to generate a hash of the string in argument 1 with the hashing function identified by the string in argument 2

#define CTR_DICT_CHECKSUM                        "checksum"
#define CTR_DICT_HTML_ENCODE_SET                 "html-encode:"
#define CTR_DICT_URL_ENCODE_SET                  "url-encode:"
#define CTR_DICT_FORM_ENCODE_SET                 "form-encode:"
#define CTR_DICT_BASE64_ENCODE_SET               "base64-encode:"
#define CTR_DICT_BASE64_DECODE_SET               "base64-decode:"
#define CTR_DICT_LINK_SET                        "link:"
#define CTR_DICT_PASSTHRU_PREFIX_SET             "passthru:prefix:"
#define CTR_DICT_MIMETYPE_SET                    "mimetype:"
#define CTR_DICT_FORMAT_SET                      "format:"
#define CTR_DICT_APPLY_TO_INT_SET                "apply-int:"
#define CTR_DICT_FORMAT_OBJECT                   "Format"
#define CTR_DICT_IPV4                            "ipv4?"
#define CTR_DICT_IPV6                            "ipv6?"
#define CTR_DICT_MAC                             "mac?"
#define CTR_DICT_HTML                            "html"
#define CTR_DICT_HTML_ENCODE                     "html-encode"
#define CTR_DICT_URL_ENCODE                      "url-encode"
#define CTR_DICT_FORM_ENCODE                     "form-encode"
#define CTR_DICT_BASE64_ENCODE                   "base64-encode"
#define CTR_DICT_BASE64_DECODE                   "base64-decode"
#define CTR_DICT_MATCH_DO_SET                    "match:do:"
#define CTR_DICT_MATCH_CAPTURE_SET               "match:capture:"
#define CTR_DICT_MATCH_SET                       "match:"
#define CTR_DICT_URL_SCHEME                      "scheme"
#define CTR_DICT_URL_HOST                        "host"
#define CTR_DICT_URL_HOST_SET                    "host:"
#define CTR_DICT_URL_USERNAME_SET                "username:"
#define CTR_DICT_URL_PORT                        "port"
#define CTR_DICT_URL_PATH                        "path"
#define CTR_DICT_URL_QUERY                       "query"
#define CTR_DICT_URL_FRAGMENT                    "fragment"
#define CTR_DICT_WIPE                            "wipe"
#define CTR_DICT_DECODE_SET                      "decode:"
#define CTR_DICT_PASSWORD_SET                    "password:"
#define CTR_DICT_DATABASENAME_SET                "dbname:"
#define CTR_DICT_DATABASE_SET                    "database:"
#define CTR_DICT_CLOSE                           "close"
#define CTR_DICT_CONNECT                         "connect"
#define CTR_DICT_CONNECTED                       "connected?"
#define CTR_DICT_COMMIT                          "commit"
#define CTR_DICT_ROLLBACK                        "rollback"
#define CTR_DICT_EXECUTE                         "execute"
#define CTR_DICT_DATABASE_QUERY_SET              "query:"
#define CTR_DICT_DATABASE_QUERYPARAMS_SET        "parameters:"
#define CTR_DICT_FETCH_SET                       "fetch:"
#define CTR_DICT_DATABASE_INSERTID               "insert-id"




