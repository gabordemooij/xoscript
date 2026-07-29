/* Input function */
int readxml(char** xmlui);

/* Output functions */
void json_start(void);
void json_string(const char *s);
void json_key(const char* s);
void json_close(void);
