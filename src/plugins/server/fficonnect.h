extern ctr_object* CtrDataBlob;
void ctr_internal_ffi(ctr_object* ffispec);
void begin_ffi();
ctr_object* ctr_build_blob(void* data, size_t len);
