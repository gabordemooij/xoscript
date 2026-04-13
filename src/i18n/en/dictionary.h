/* English Language File for XOScript Core Module */

/* Section A: Objects, Keywords & Messages (translation recommended) */
#define CTR_DICT_NIL                             "None"                      // None object (null)
#define CTR_DICT_BOOLEAN                         "Bool"                      // Bool object (boolean, parent of True and False, equals False)
#define CTR_DICT_TRUE                            "True"                      // True object (extends Bool)
#define CTR_DICT_FALSE                           "False"                     // False object (extends Bool)
#define CTR_DICT_NUMBER                          "Number"                    // Number object (root object of all numbers)
#define CTR_DICT_STRING                          "String"                    // String object (root object of all strings)
#define CTR_DICT_TASK                            "Function"                  // Function object (root object of all functions)
#define CTR_DICT_OBJECT                          "Object"                    // Root object (root object of all objects)
#define CTR_DICT_ARRAY_OBJECT                    "List"                      // List object (root object of all lists)
#define CTR_DICT_MAP_OBJECT                      "Dict"                      // Dict object (root object of all dictionaries/maps)
#define CTR_DICT_PROGRAM                         "Program"                   // Program object (to communicate with process)
#define CTR_DICT_FILE                            "File"                      // File object (root object of all files)
#define CTR_DICT_MOMENT                          "Moment"                    // Moment object (root object of all time/moment objects)
#define CTR_DICT_INT64                           "Int64"                     // 64-bit Integer Number class-like object
#define CTR_DICT_PATH_OBJECT                     "Path"                      // Path object, root of all path objects, file locations, can be used to turn messages into strings separated by OS-dependent path separator
#define CTR_DICT_CMD_OBJECT                      "Command"                   // Command object, root all command objects, can be used to turn messages into strings separated by spaces
#define CTR_DICT_PEN_ICON                        "Out"                       // Word or symbol for standard output object (stdout)
#define CTR_DICT_ME_ICON                         "self"                      // Word or symbol to refer to the object itself from within a method to call another method
#define CTR_DICT_MY_ICON                         "own"                       // Word or symbol to refer to the object itself from within a method to access a property
#define CTR_DICT_NEW                             "new"                       // Word or symbol for unary message to create a new object (unary message, no colon allowed)
#define CTR_DICT_EQUALS                          "equals:"                   // Compares the identify (memory location) of two objects (must keyword message with exactly 1 colon at the end)
#define CTR_DICT_AND                             "and:"                      // Word for and as in (A and B), must contain only 1 colon at the end
#define CTR_DICT_OR                              "or:"                       // Word for or as in (A or B), must contain only 1 colon at the end
#define CTR_DICT_MODULO                          "modulo:"                   // Word for modulo (remainder of division), must contain only 1 colon at the end
#define CTR_DICT_NOR                             "nor:"                      // Word for nor/neither (A nor B), must contain only 1 colon at the end
#define CTR_DICT_ONDO                            "on:do:"                    // Word for on:do: as in (on receiving message do answer), used to attach functions to objects, 2 colons
#define CTR_DICT_TYPE                            "type"                      // Word for the type of an object
#define CTR_DICT_ISNIL                           "None?"                     // Word to ask if an object is None
#define CTR_DICT_MYSELF                          "myself"                    // Word for myself, returns a reference to the object itself
#define CTR_DICT_DO                              "do"                        // Word for do, after this, returns are ignored until done
#define CTR_DICT_DONE                            "done"                      // Word for done, ends a return-ignore sequence started by do
#define CTR_DICT_IFFALSE                         "false:"                    // Word for do-if-false, runs function if send to False (false:)
#define CTR_DICT_IFTRUE                          "true:"                     // Word for do-if-true, runs function if send to True
#define CTR_DICT_WHILE                           "while:"                    // Word for run-me-while-this-is-true, runs recipient Function as long as argument Function returns True
#define CTR_DICT_MESSAGEARGS                     "message:arguments:"        // Word for send a message to an object as a variable and a list for the arguments
#define CTR_DICT_MESSAGE                         "message:"                  // Word for: send a message to an object as a variable
#define CTR_DICT_LEARN                           "learn:means:"              // Word for: learn that this message now means this, remaps message
#define CTR_DICT_BREAK                           "break"                     // Word for: break the loop or procedure here and skip the remaining iterations
#define CTR_DICT_CONTINUE                        "continue"                  // Word for: continue the loop, skip the rest of this iteration and continue with next iteration
#define CTR_DICT_ELSE                            "else:"                     // Alias for: 'false:'
#define CTR_DICT_NOT                             "not"                       // Word for inversion, like green is not red
#define CTR_DICT_TONUMBER                        "number"                    // Word for casting to a Number
#define CTR_DICT_TOSTRING                        "string"                    // Word for casting to a String
#define CTR_DICT_CHAR_AT_SET                     "character:"                // Word to access an UTF-8 characters (1 code point) as a String from the specified position
#define CTR_DICT_EITHEROR                        "either:or:"                // Word to select 1 of 2 objects, either A or B
#define CTR_DICT_BY_SET                          "by:"                       // Word to combine 2 lists into 1 dict, recipient list will provide the values while the argument list provides the keys
#define CTR_DICT_FLOOR                           "floor"                     // Word for rounding to the lower number
#define CTR_DICT_CEIL                            "ceil"                      // Word for rounding to the higher number
#define CTR_DICT_ROUND                           "round"                     // Word for rounding to the nearest number
#define CTR_DICT_POWER                           "power:"                    // Word for the power of the recipient number, as specified by the argument
#define CTR_DICT_MIN                             "minimum"                   // Word for the smallest element in a list
#define CTR_DICT_MAX                             "maximum"                   // Word for the biggest element in a list
#define CTR_DICT_ODD                             "odd?"                      // Word to ask whether a number is an odd number (1, 3, 5...)
#define CTR_DICT_EVEN                            "even?"                     // Word to ask whether a number is an even number (2, 4, 6...)
#define CTR_DICT_POS                             "positive?"                 // Word to ask whether a number is > 0
#define CTR_DICT_NEG                             "negative?"                 // Word to ask whether a number is < 0
#define CTR_DICT_TOBOOL                          "bool"                      // Word for casting to True or False
#define CTR_DICT_RANDOM_NUM_BETWEEN              "between:and:"              // Phrase with 2 colons for asking a random number between argument 1 and argument 2
#define CTR_DICT_LENGTH                          "length"                    // Word for asking for the length of something
#define CTR_DICT_FROM_LENGTH                     "from:length:"              // Phrase for requesting a part of something specifying the start with argument 1 and the length / amount with argument 2
#define CTR_DICT_TRIM                            "trim"                      // Word to remove surrounding spaces from a string
#define CTR_DICT_AT                              "at:"                       // Word to request an element in a collection located using the argument
#define CTR_DICT_POSITION_SET                    "position:"                 // Word to request an element in a collection located at a numeric position or index using the argument
#define CTR_DICT_INDEX_OF                        "find:"                     // Word to request the location or key of the specified object in a collection using the argument
#define CTR_DICT_LAST_INDEX_OF                   "last:"                     // Word to ask for the last element in an ordered collection like a list
#define CTR_DICT_REPLACE_WITH                    "replace:with:"             // Phrase to replace a portion indicated by argument 1 with a replacement indicated by argument 2 in an object
#define CTR_DICT_SPLIT                           "split:"                    // Word to divide an object into multiple parts using the argument
#define CTR_DICT_SKIP                            "offset:"                   // Word to return the remainder of an object skipping the first part as indicated by the argument
#define CTR_DICT_RUN                             "start"                     // Word to call a function, start a task or start a block of code
#define CTR_DICT_APPLY_TO                        "apply:"                    // Word to call a function (recipient object) with 1 argument
#define CTR_DICT_APPLY_TO_AND                    "apply:and:"                // Phrase to call a function (recipient object) with 2 arguments
#define CTR_DICT_APPLY_TO_AND_AND                "apply:and:and:"            // Same as apply: but with 2 arguments
#define CTR_DICT_VALUE_SET                       "set:value:"                // Phrase to inject a value (argument 2) into a function under the specified name (argument 1)
#define CTR_DICT_ERROR                           "error:"                    // Word to write a string to the standard error channel, stderr
#define CTR_DICT_CATCH                           "except:"                   // Word to associate an exception handler function (argument) with the recipient function
#define CTR_DICT_SHIFT                           "shift"                     // Word to shift-off the first element of a list
#define CTR_DICT_COUNT                           "count"                     // Word to count the number of elements in a collection
#define CTR_DICT_JOIN                            "combine:"                  // Word to combine multiple objects in a collection into one
#define CTR_DICT_POP                             "pop"                       // Word to remove and return the last element in a collection
#define CTR_DICT_SORT                            "sort:"                     // Word to sort the elements in the receiver according to the specified function
#define CTR_DICT_PUT_AT                          "put:at:"                   // Word to add argument 1 to a collection using argument 2 as its key
#define CTR_DICT_MAP                             "map:"                      // Word to apply the function in the argument to each element in the collection (map:)
#define CTR_DICT_EACH                            "each:"                     // Alias for map:
#define CTR_DICT_WRITE                           "write:"                    // Word to write the argument object as data to the recipient object (can be file or stdout)
#define CTR_DICT_PATH                            "path"                      // Word for the location of a file in the filesystem (path)
#define CTR_DICT_READ                            "read"                      // Word to read data from the recipient object
#define CTR_DICT_APPEND                          "append:"                   // Word to add an element at the end of an ordered collection
#define CTR_DICT_PREPEND                         "prepend:"                  // Word to add an element at the beginning of an ordered collection
#define CTR_DICT_EXISTS                          "exists"                    // Word to inquire whether the item the recipient object represents exists
#define CTR_DICT_SIZE                            "size"                      // Word to measure the size of or space taken by the recipient object
#define CTR_DICT_DELETE                          "delete"                    // Word to delete the entity that the recipient object represents
#define CTR_DICT_USE_SET                         "use:"                      // Word to order the use of a tool or subprogram
#define CTR_DICT_ARRAY                           "list:"                     // Word to extract a list from an object specified by the argument
#define CTR_DICT_END                             "end"                       // Word to end something or the program
#define CTR_DICT_ARGUMENT                        "argument:"                 // Word to obtain a passed argument identified by the number or key specified in the argument
#define CTR_DICT_ARGUMENT_COUNT                  "arguments"                 // Word or phrase to obtain the number of arguments passed
#define CTR_DICT_WAIT_FOR_PASSW                  "ask-password"              // Word or phrase to ask for password or secret (assumes user interaction!)
#define CTR_DICT_WAIT_FOR_INPUT                  "ask"                       // Word or phrase to ask for user input that is not a secret (assumes user interaction!)
#define CTR_DICT_INPUT                           "input"                     // Word or phrase to ask for input without user interaction like stdin or a data stream
#define CTR_DICT_FLUSH                           "flush"                     // Word or phrase to request the contents of an intermediate buffer to be streamed to the next end point, emptying said buffer
#define CTR_DICT_WAIT                            "wait:"                     // Word or phrase to request a pause in the program causing a delay specified by the number of seconds in the argument
#define CTR_DICT_TIME                            "time"                      // Word to request a timestamp from an object
#define CTR_DICT_RESPOND_TO                      "respond:"                  // Word to use to respond to a message not explicitly associated with the recipient object through on:do: as a method
#define CTR_DICT_RESPOND_TO_AND                  "respond:and:"              // Same as respond: (above), but with 1 argument
#define CTR_DICT_RESPOND_TO_AND_AND              "respond:and:and:"          // Same as respond: (above), but with 2 arguments
#define CTR_DICT_RESPOND_TO_AND_AND_AND          "respond:and:and:and:"      // Same as respond: (above), but with 3 arguments
#define CTR_DICT_SHELL                           "os:"                       // Word or phrase to send a command to the operating system shell
#define CTR_DICT_SWEEP                           "clean-up"                  // Word or phrase for cleaning up, tidying up
#define CTR_DICT_MEMORY_LIMIT                    "memory:"                   // Word to change computer memory
#define CTR_DICT_MEMORY                          "memory"                    // Word to request information about computer memory
#define CTR_DICT_GC_MODE                         "memory-management:"        // Word or phrase to change computer memory management
#define CTR_DICT_HASH_WITH_KEY                   "hash:"                     // Word to calculate a simple hash with a key
#define CTR_DICT_CHARACTERS                      "characters"                // Word to refer to characters or letters in a string, resulting in a list
#define CTR_DICT_QUALIFIER_SET                   "qualify:"                  // Word to add a description or unit of measurement string to a number
#define CTR_DICT_QUALIFIER                       "qualifier"                 // Word to obtain the description or unit of measurement string associated with a number
#define CTR_DICT_NEW_SET                         "new:"                      // Word to create a new object based on the recipient with an additional argument for initialisation
#define CTR_DICT_HOUR                            "hour"                      // Word to obtain the hour of the day from an object respresenting a point in time
#define CTR_DICT_HOUR_SET                        "hour:"                     // Word to change the hour of the day in an object representing a point in time
#define CTR_DICT_MINUTE_SET                      "minute:"                   // Word to change the minute of the hour in an object representing a point in time
#define CTR_DICT_MINUTE                          "minute"                    // Word to obtain the minute of the hour from an object respresenting a point in time
#define CTR_DICT_SECOND_SET                      "second:"                   // Word to change the second of the minute in an object representing a point in time
#define CTR_DICT_SECOND                          "second"                    // Word to obtain the second of the minute from an object respresenting a point in time
#define CTR_DICT_DAY                             "day"                       // Word to obtain the day of the month from an object respresenting a point in time
#define CTR_DICT_DAY_SET                         "day:"                      // Word to change the day of the month in an object representing a point in time
#define CTR_DICT_WEEK                            "week"                      // Word to obtain the week of the year from an object respresenting a point in time
#define CTR_DICT_WEEK_SET                        "week:"                     // Word to change the week of the year in an object representing a point in time
#define CTR_DICT_MONTH                           "month"                     // Word to obtain the month of the year from an object respresenting a point in time
#define CTR_DICT_MONTH_SET                       "month:"                    // Word to change the month of the year in an object representing a point in time
#define CTR_DICT_YEAR                            "year"                      // Word to obtain the year from an object respresenting a point in time
#define CTR_DICT_RAW                             "plain"                     // Word to obtain an object without associated qualifications or just in a simplified form
#define CTR_DICT_YEAR_SET                        "year:"                     // Word to change the year in an object representing a point in time
#define CTR_DICT_WEEK_DAY                        "weekday"                   // Word to obtain the day of the week from an object respresenting a point in time
#define CTR_DICT_YEAR_DAY                        "yearday"                   // Word to obtain the day of the year from an object respresenting a point in time
#define CTR_DICT_ZONE                            "zone"                      // Word to obtain the time zone from an object respresenting a point in time
#define CTR_DICT_ZONE_SET                        "zone:"                     // Word to change the time zone of an object representing a point in time
#define CTR_DICT_ADD_SET                         "add:"                      // Word to add the specified number to the recipient object, changing the object itself
#define CTR_DICT_SUBTRACT_SET                    "subtract:"                 // Word to subtract the specified number from the recipient object, changing the object itself
#define CTR_DICT_MULTIPLIER_SET                  "multiply-by:"              // Word to multiply the recipient by the specified number, changing the object itself
#define CTR_DICT_DIVIDER_SET                     "divide-by:"                // Word to devide the recipient by the specified number, changing the object itself
#define CTR_DICT_LAST                            "last"                      // Word to obtain the last element of an ordered collection
#define CTR_DICT_FIRST                           "first"                     // Word to obtain the first element of an ordered collection
#define CTR_DICT_SECOND_LAST                     "penultimate"               // Word to obtain the second last element of an ordered collection
#define CTR_DICT_FILL_WITH                       "fill:with:"                // Phrase to add the specified number of elements (argument 1) with the specified value (argument 2)
#define CTR_DICT_SPLICE                          "replace:length:with:"      // Phrase to replace elements in recipient object starting at argument 1 with the specified number of elements in argument 2 from the collection in argument 3
#define CTR_DICT_VALUES                          "values"                    // Word or phrase to obtain a list of values from a dict
#define CTR_DICT_ENTRIES                         "entries"                   // Word or phrase to obtain a list of keys from a dict
#define CTR_DICT_COMPARE_SET                     "compare:"                  // Word or phrase to compare the recipient object to another object
#define CTR_DICT_HAS                             "has:"                      // Word or phrase to inquire whether the argument object is present in the recipient (collection) object
#define CTR_DICT_COPY                            "copy"                      // Word to make a copy of an object
#define CTR_DICT_CASE_DO                         "case:do:"                  // Phrase to compare the recipient object to the object in argument 1 and if are equal in value then call the function specified in argument 2
#define CTR_DICT_STOP                            "stop"                      // Word to describe a new line in a text
#define CTR_DICT_ASCII_UPPER_CASE                "upper"                     // Word to describe upper casing of characters (if applicable)
#define CTR_DICT_ASCII_LOWER_CASE                "lower"                     // Word to describe lower casing of characters (if applicable)
#define CTR_DICT_CONTAINS                        "contains:"                 // Alias for has:
#define CTR_DICT_ENVIRONMENT_VARIABLE            "setting:"                  // Word to obtain a program setting value with the specified name
#define CTR_DICT_SET_ENVIRONMENT_VARIABLE        "setting:value:"            // Phrase to change the program setting indicated in argument 1 to the value specified in argument 2
#define CTR_DICT_CURRENT_TASK                    "this-task"                 // Word to reference the currently running function
#define CTR_DICT_CODE                            "code"                      // Word to cast an object to an executable string representation
#define CTR_DICT_PROCEDURE                       "procedure"                 // Word to use for a group of instructions that allow breaks (alias for * 1)
#define CTR_DICT_TOOBJECT                        "object"                    // Word to use to cast a string to an object by parsing/evaluating the code within
#define CTR_DICT_RECURSIVE                       "recursive"                 // Word to enable calling the same method from a method
#define CTR_DICT_VERSION_SET                     "version:"                  // Word to set the version of recipient to the specified value in the argument
#define CTR_DICT_FROM_STRING                     "from-string:"              // Word to obtain an object from a string
#define CTR_DICT_LINES_SET                       "lines:"                    // Word to call a function for each line read from an object
#define CTR_DICT_PLATFORM                        "platform"                  // Word to obtain a string identifying the current platform
#define CTR_DICT_ALARM_SET                       "alarm:"                    // Word or phrase to limit the execution of the program to the number of seconds specified by the argument
#define CTR_DICT_FORMAT_SET                      "format:"                   // Word or phrase to obtain a string representation of the recipient object in the specified format in the argument
#define CTR_DICT_DELIM_QUOTE_LINES               "delimiter:quote:lines:"    // Phrase to apply a function to a CSV line from a readable object, argument 1 must be the delimiter, argument 2 must be the quote style, argument 3 is the function
#define CTR_DICT_LOCK                            "lock"                      // Word for locking the resource respresented by the recipient object
#define CTR_DICT_UNLOCK                          "unlock"                    // Word for unlocking the resource represented by the recipient object
#define CTR_DICT_FEATURE_SET                     "feature:"                  // Word to obtain the current activation status of the feature identified by argument 1
#define CTR_DICT_FEATURE_ENABLE_SET              "feature:enable:"           // Word to select feature identified by argument 1 and enable it or disable it as specified by argument 2
#define CTR_DICT_TEST                            "test"                      // Word to perform a test on the recipient object without arguments
#define CTR_DICT_FROM_SET                        "from:"                     // Word to obtain an object resulting from transforming another object specified by argument 1 (from).
#define CTR_DICT_ISODATETIME                     "iso-datetime"              // Word to obtain an standard iso datetime formatted representation of the recipient object

/* Section B: Code generation, must match Dict/List messages! */
#define CTR_DICT_CODEGEN_MAP_NEW                 "(Dict new) "               // Code generation for dict, new part
#define CTR_DICT_CODEGEN_MAP_PUT                 "put:"                      // Code generation for dict, value part
#define CTR_DICT_CODEGEN_MAP_PUT_AT              " at:"                      // Code generation for dict, key part
#define CTR_DICT_CODEGEN_ARRAY_NEW               "List new "                 // Code generation for list, new part (empty)
#define CTR_DICT_CODEGEN_ARRAY_NEW_PUSH          "List ← "                   // Code generation for list, new and add part

/* Section C: System terms & Math (hard to translate) */
#define CTR_DICT_OBSD_PLEDGE_SET                 "pledge:"                   // Term to invoke pledge command on OpenBSD with argument
#define CTR_DICT_OBSD_UNVEIL_SET                 "unveil:permissions:"       // Term to invoke unveil command on OpenBSD with arguments
#define CTR_DICT_UNIX_CHMOD_SET                  "chmod:"                    // Word or abbreviation to apply a POSIX-style chmod command to the recipient object
#define CTR_DICT_UNIX_STAT                       "stat"                      // Word to obtain the status of a POSIX-statable object
#define CTR_DICT_UNIX_MKDIR_SET                  "mkdir:mode:"               // Phrase to create a new directory specified by the path in argument 1 with mode specified by argument 2
#define CTR_DICT_UNIX_CHDIR_SET                  "chdir:"                    // Term to switch working directory to specified path in argument
#define CTR_DICT_HEXADECIMAL                     "Hx"                        // Word or abbreviation indicating a hexadecimal number
#define CTR_DICT_OCTAL                           "Oct"                       // Word or abbreviation indicating an octal number
#define CTR_DICT_BINARY                          "Bin"                       // Word or abbreviation indicating a binary number
#define CTR_DICT_UTF8                            "utf8"                      // Word or abbreviation to request a UTF-8 encoded string from the recipient object
#define CTR_DICT_BYTES                           "bytes"                     // Word to obtain byte values from recipient object
#define CTR_DICT_BYTE                            "byte"                      // Word to obtain a single byte value from a recipient object
#define CTR_DICT_TCCOMPARE                       "tccompare:"                // Word to compare the recipient object to the object specified by the argument using a constant time comparison
#define CTR_DICT_TEMPORARY_WRITE_SET             "tempwrite:"                // Word, abbreviation or term to describe writing a string to a temporary file (path will be returned)
#define CTR_DICT_OWNER_GROUP_SET                 "owner:group:"              // Phrase to change owner and group of a resource represented by the recipient object
#define CTR_DICT_GC_MODE_GET                     "gcmode"                    // Word to obtain the current mode of operation of the garbage collector
#define CTR_DICT_SHELLESC_SET                    "shell-escape:"             // Word or phrase to escape the string in the argument for use in a shell command
#define CTR_DICT_ABS                             "abs"                       // Word for the absolute value without the sign
#define CTR_DICT_SQRT                            "sqrt"                      // Word for the square root of a number
#define CTR_DICT_MATH_SIN                        "sin"                       // Word or abbreviation for sinus
#define CTR_DICT_MATH_COS                        "cos"                       // Word or abbreviation for cosinus
#define CTR_DICT_MATH_TAN                        "tan"                       // Word or abbreviation for tangus
#define CTR_DICT_MATH_ATAN                       "atan"                      // Word or abbreviation for atangus
#define CTR_DICT_MATH_LOG                        "log"                       // Word or abbreviation for logarithm

/* Section D: Symbols (recommended to not translate) */
#define CTR_DICT_VAR_ICON                        ">>"                        // Word or symbol to declare a variable
#define CTR_DICT_BULLET                          "~"                         // Adds a value to a list (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_SYMBOL_EQUALS                   "="                         // Compares the value of two objects (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_PLUS                            "+"                         // Symbol for addition (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_MINUS                           "-"                         // Symbol for subtraction (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_MULTIPLIER                      "×"                         // Non-ASCII symbol for multiplication (ASCII equivalent is provided by default) (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_DIVISION                        "÷"                         // Non-ASCII symbol for division (ASCII equivalent is provided by default) (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_GREATER                         ">"                         // Symbol for greater than comparisons
#define CTR_DICT_LESS                            "<"                         // Symbol for less than comparisons
#define CTR_DICT_AT_SYMBOL                       "?"                         // Symbol to get element from list or dict (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_NEW_ARRAY_AND_PUSH_SYMBOL       "←"                         // Non-ASCII symbol for return (ASCII equivalent is provided by default)
#define CTR_DICT_GREATER_OR_EQUAL_SYMBOL         "≥"                         // Non-ASCII symbol for greater or equal comparisons (ASCII equivalent is provided by default) (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_LESS_OR_EQUAL_SYMBOL            "≤"                         // Non-ASCII symbol for less or equal comparisons (ASCII equivalent is provided by default) (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_UNEQUALS_SYMBOL                 "≠"                         // Non-ASCII symbol for unequality in comparisons (ASCII equivalent is provided by default) (binary message, must be exactly 1 UTF8-codepoint)
#define CTR_DICT_END_OF_LINE                     "."                         // End of line marker
#define CTR_DICT_NUM_DEC_SEP                     "."                         // Symbol to use as decimal separator
#define CTR_DICT_NUM_THO_SEP                     ","                         // Symbol to use as thousands separator
#define CTR_DICT_QUOT_OPEN                       "['"                        // Start of literal string
#define CTR_DICT_QUOT_CLOSE                      "']"                        // End of a literal string
#define CTR_DICT_MESSAGE_CHAIN                   ","                         // Symbol to use for chaining multiple keyword messages, must be exactly 1 byte
#define CTR_DICT_ASSIGN                          ":="                        // Symbol to use for assignment
#define CTR_DICT_RETURN                          "<-"                        // Symbol to use as return
#define CTR_DICT_PUSH_SYMBOL                     ";"                         // Symbol to add an element to a list

/* Section E: Restricted (do not translate unless you know impact) */
#define CTR_DICT_BLOCK_START                     "{"                         // Symbol to use to start a group of instructions (not translatable)
#define CTR_DICT_BLOCK_END                       "}"                         // Symbol to use to close a group of instructions (not translatable)
#define CTR_DICT_PARAMETER_PREFIX                ":"                         // Symbol to use as parameter prefix (not translatable)
#define CTR_DICT_PAREN_OPEN                      "("                         // Symbol to use for starting an experssion (not translatable)
#define CTR_DICT_PAREN_CLOSE                     ")"                         // Symbol to use for ending an experssion (not translatable)
