/* English Language File for XOScript Server Plugin */

#define CTR_DICT_VAULT_OBJECT                    "Vault"                     // Word for object providing cryptography features
#define CTR_DICT_JSON_OBJECT                     "JSON"                      // Word for object that handles JSON protocol
#define CTR_DICT_PLUGIN_REQUEST                  "HTTP-Request"              // Word for object representing the current HTTP-Request
#define CTR_DICT_NETWORK_OBJECT                  "Net"                       // Word for object providing network functionality
#define CTR_DICT_BLOB_OBJECT                     "Blob"                      // Word for object representing a computer memory block
#define CTR_DICT_SERVER_OBJECT                   "Server"                    // Word for object providing server functionality
#define CTR_DICT_URL_OBJECT                      "URL"                       // Word for object representing internet address or URL
#define CTR_DICT_DATABASE_MARIADB_OBJECT         "Maria-DB"                  // Word for object representing MariaDB database system
#define CTR_DICT_DATABASE_MARIADB_QUERY_OBJECT   "Maria-Query"               // Word for object representing a MariaDB database query
#define CTR_DICT_PATTERN_OBJECT                  "Pattern"                   // Word for object representing a PCRE2-style regular expression
#define CTR_DICT_FORMAT_OBJECT                   "Format"                    // Word for object that represents a specific formatting for a string
#define CTR_DICT_FORMAT_SET                      "format:"                   // Term to produce an object implementing the format as specified by argument 1
#define CTR_DICT_JSONIFY                         "jsonify:"                  // Term to turn objects into a string with JSON encoding
#define CTR_DICT_OBJECT_FROM_SET                 "object:"                   // Term to turn serialized string back into an object
#define CTR_DICT_LINK_SET                        "link:"                     // Word to connect or link something to something else
#define CTR_DICT_FREE                            "free"                      // Word to free allocated computer memory
#define CTR_DICT_FREE_STRUCT                     "structfree"                // Term to free allocated c-structure in computer memory
#define CTR_DICT_STRUCT_SET                      "struct:"                   // Term to describe a c-structure in computer memory
#define CTR_DICT_DEREF                           "deref"                     // Term for dereferencing a c pointer
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
#define CTR_DICT_CHECKSUM                        "checksum"                  // Word to generate a checksum string of the recipient object
#define CTR_DICT_HTML_ENCODE_SET                 "html-encode:"              // Word to HTML-encode the object in argument 1
#define CTR_DICT_URL_ENCODE_SET                  "url-encode:"               // Word to URL-encode the object in argument 1
#define CTR_DICT_FORM_ENCODE_SET                 "form-encode:"              // Word to FORM-encode the object in argument 1
#define CTR_DICT_BASE64_ENCODE_SET               "base64-encode:"            // Word to BASE64-encode the object in argument 1
#define CTR_DICT_BASE64_DECODE_SET               "base64-decode:"            // Word to BASE64-decode the object in argument 1
#define CTR_DICT_PASSTHRU_PREFIX_SET             "passthru:prefix:"          // Phrase to serve the asset specified in argument 1 and in container directory specified by argument 2
#define CTR_DICT_MIMETYPE_SET                    "mimetype:"                 // Word or phrase to inquire about the MIME-type of object specified in argument
#define CTR_DICT_APPLY_TO_INT_SET                "apply-int:"                // Word or phrase to apply a function to an object that is of type Int64
#define CTR_DICT_IPV4                            "ipv4?"                     // Word or phrase to inquire whether the recipient object can be classified as an IPv4 address
#define CTR_DICT_IPV6                            "ipv6?"                     // Word or phrase to inquire whether the recipient object can be classified as an IPv6 address
#define CTR_DICT_MAC                             "mac?"                      // Word or phrase to inquire whether the recipient object can be classified as an mac address
#define CTR_DICT_HTML                            "html"                      // Word or phrase to change recipient object into html, the recipient object contains a simplified markup language
#define CTR_DICT_HTML_ENCODE                     "html-encode"               // Word or phrase to generate a HTML-encoded representation of the recipient object
#define CTR_DICT_URL_ENCODE                      "url-encode"                // Word or phrase to generate a URL-encoded representation of the recipient object
#define CTR_DICT_FORM_ENCODE                     "form-encode"               // Word or phrase to generate a FORM-encoded representation of the recipient object
#define CTR_DICT_BASE64_ENCODE                   "base64-encode"             // Word or phrase to generate a BASE64-encoded representation of the recipient object
#define CTR_DICT_BASE64_DECODE                   "base64-decode"             // Word or phrase to generate a BASE64-decoded representation of the recipient object
#define CTR_DICT_MATCH_DO_SET                    "match:do:"                 // Phrase to match a string in argument 1 against the recipient object and upon matching perform the function specified in argument 2
#define CTR_DICT_MATCH_CAPTURE_SET               "match:capture:"            // Alias for match:do: (above)
#define CTR_DICT_MATCH_SET                       "match:"                    // Word to count the number of matches of argument 1 against the recipient object
#define CTR_DICT_URL_SCHEME                      "scheme"                    // Word to obtain the scheme part of an URL
#define CTR_DICT_URL_HOST                        "host"                      // Word to obtain the host part of an URL
#define CTR_DICT_URL_HOST_SET                    "host:"                     // Word to change the host of an URL
#define CTR_DICT_URL_USERNAME_SET                "username:"                 // Word to change the username in an URL
#define CTR_DICT_URL_PORT                        "port"                      // Word to obtain the port part in an URL
#define CTR_DICT_URL_PATH                        "path"                      // Word to obtain the path part in an URL
#define CTR_DICT_URL_QUERY                       "query"                     // Word to obtain the query part of an URL
#define CTR_DICT_URL_FRAGMENT                    "fragment"                  // Word to obtain the fragment part of an URL
#define CTR_DICT_WIPE                            "wipe"                      // Word to delete the contents of an object
#define CTR_DICT_DECODE_SET                      "decode:"                   // Word to decode the recipient object according to the decoding protocol specified in argument 1
#define CTR_DICT_DATABASENAME_SET                "dbname:"                   // Word to associate the database name in argument 1 with the recipient object
#define CTR_DICT_DATABASE_SET                    "database:"                 // Word to associate the database object in argument 1 with the recipient object
#define CTR_DICT_CLOSE                           "close"                     // Word to invoke a closing operation on the recipient object
#define CTR_DICT_CONNECT                         "connect"                   // Word to invoke a connecting operting on the recipient object
#define CTR_DICT_CONNECTED                       "connected?"                // Word to inquire about the connection status of the recipient object
#define CTR_DICT_COMMIT                          "commit"                    // Word to mark the end of a transaction
#define CTR_DICT_ROLLBACK                        "rollback"                  // Word to undo the a series of operations applied to recipient object as part of a transaction
#define CTR_DICT_EXECUTE                         "execute"                   // Word to execute a predefined series of operations on the recipient object
#define CTR_DICT_DATABASE_QUERY_SET              "query:"                    // Word to specify a database query in argument 1 to be applied to the recipient object
#define CTR_DICT_DATABASE_QUERYPARAMS_SET        "parameters:"               // Word to associate database query parameters in argument with the current state of the recipient object
#define CTR_DICT_FETCH_SET                       "fetch:"                    // Word to fetch something from the recipient object and associate a callback function using the argument
#define CTR_DICT_DATABASE_INSERTID               "insert-id"                 // Word to return a database insertion id resulting from an insert operation on a database