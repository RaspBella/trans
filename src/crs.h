#pragma once

#define C_IS_UPPER(c) c >= 'A' && c <= 'Z'
#define VALID_CRS(code) C_IS_UPPER(code[0]) && C_IS_UPPER(code[1]) && C_IS_UPPER(code[2])

const char *crs(const char *code);
const char *src(const char *name);
