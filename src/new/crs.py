from cffi import FFI

ffi = FFI()

ffi.cdef("const char *crs(char*);");

clib = ffi.dlopen("./libcrs.so")

def crs(code):
  name = clib.crs(code.encode())

  if name == ffi.NULL:
    return None

  return ffi.string(name).decode()
