from cffi import FFI

ffi = FFI()

ffi.cdef("const char *crs(const char*);")
ffi.cdef("const char *src(const char*);")

clib = ffi.dlopen("./libcrs.so")

def crs(code):
  name = clib.crs(code.encode())

  if name == ffi.NULL:
    return None

  return ffi.string(name).decode()

def src(name):
  code = clib.src(name.encode())

  return ffi.string(code).decode()
