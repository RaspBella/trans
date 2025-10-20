#pragma once

#define C_IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')

#define C_IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')

#define VALID_CRS(code) (C_IS_UPPER(((code)[0])) && C_IS_UPPER(((code)[1])) && C_IS_UPPER(((code)[2])))

#define LOWERCASE_VALID_CRS(code) (C_IS_LOWER(((code)[0])) && C_IS_LOWER(((code)[1])) && C_IS_LOWER(((code)[2])))

#define CASE_I_VALID_CRS(code) (VALID_CRS((code)) || LOWERCASE_VALID_CRS((code)))

#define SEP "\n"

const char *crs(const char *code);
const char *src(const char *name);
