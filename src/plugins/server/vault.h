#define BASE64_ENCODE_OUT_SIZE(s) ((unsigned int)((((s) + 2) / 3) * 4 + 1))
#define BASE64_DECODE_OUT_SIZE(s) ((unsigned int)(((s) / 4) * 3))

ctr_object* ctr_gui_vault_set(ctr_object* myself, ctr_argument* argumentList);
ctr_object* ctr_gui_vault_get(ctr_object* myself, ctr_argument* argumentList);
void begin_vault();