#ifndef JSTRING_H
#define JSTRING_H

// ==========
// || Libs ||
// ==========

#include <cstdlib>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// ===============
// || Constants ||
// ===============

#ifndef JSTRINGDEF
#define JSTRINGDEF
#endif // JSTRINGDEF

#define JSTRING_NULLPTR NULL


// ===========
// || Enums ||
// ===========

typedef enum {
    JSTRING_SUCCESS = 0,
    JSTRING_FAILURE,
} JSTRING_Result;


// ================================
// || Main struct & constructors ||
// ================================

typedef struct {
    const char* data;
    size_t count;
} JSTRING_String_View;

// Returns a String view from a given const char*
JSTRINGDEF JSTRING_String_View jstring_sv_from_cstr(const char* cstr);
// Returns a String view from the given parts.
// NOTE: if the 'count' argument is bigger then the actual string, it will break logic... 
// use [safe_sv_from_parts] method to avoid this problem 
JSTRINGDEF JSTRING_String_View jstring_sv_from_parts(const char* data, size_t count);
// Returns a String view from the given parts.
// NOTE: the 'ok' argument defines if the logic is valid or not (see [sv_from_parts] method for specification)
JSTRINGDEF JSTRING_String_View jstring_safe_sv_from_parts(const char* data, size_t count, JSTRING_Result* ok);
// Returns a const char* form a given String view.
// NOTE: this const char* will always have '\0' character at the end.
JSTRINGDEF const char* jstring_cstr_from_sv(JSTRING_String_View sv);
// Returns a const char* from a given String view.
// NOTE: this const char* WON'T always have '\0' character at the end. 
JSTRINGDEF const char* jstring_raw_cstr_from_sv(JSTRING_String_View sv);


#ifdef JSTRING_IMPLEMENTATION // TODO: remove 'n' in ifndef

// ==================
// || Constructors ||
// ==================

JSTRINGDEF JSTRING_String_View jstring_sv_from_parts(const char *data, size_t count) {
    JSTRING_String_View sv;
    sv.data = data;
    sv.count = count;
    return sv;
}

JSTRINGDEF JSTRING_String_View jstring_sv_from_cstr(const char *cstr) {
    return jstring_sv_from_parts(cstr, strlen(cstr)); 
}

JSTRINGDEF JSTRING_String_View jstring_safe_sv_from_parts(const char* data, size_t count, JSTRING_Result* ok) {
    JSTRING_String_View sv = jstring_sv_from_parts("", 0);

    size_t len = strlen(data);
    if(count > len) {
        *ok = JSTRING_FAILURE;
        return sv;
    }

    *ok = JSTRING_SUCCESS;
    return jstring_sv_from_parts(data, count);
}

JSTRINGDEF const char* jstring_cstr_from_sv(JSTRING_String_View sv) {
    char* cstr = (char*)malloc(sv.count + 1);
    if(cstr == JSTRING_NULLPTR) return JSTRING_NULLPTR;

    memcpy(cstr, sv.data, sv.count);
    cstr[sv.count] = '\0';
    return cstr;
}

JSTRINGDEF const char* jstring_raw_cstr_from_sv(JSTRING_String_View sv) {
    char* cstr = (char*)malloc(sv.count);
    if(cstr == JSTRING_NULLPTR) return JSTRING_NULLPTR;

    memcpy(cstr, sv.data, sv.count);
    return cstr;
}


#endif // JSTRING_IMPLEMENTATION


#ifndef JSTRING_UNSTRIP_PREFIX
    
    #define Result          JSTRING_Result    
    #define String_View     JSTRING_String_View
    
    #define sv_from_cstr(cstr)                      jstring_sv_from_cstr(cstr)
    #define sv_from_parts(cstr, count)              jstring_sv_from_parts(cstr, count)
    #define safe_sv_from_parts(cstr, count, ok)     jstring_safe_sv_from_parts(cstr, count, ok)
    #define cstr_from_sv(sv)                        jstring_cstr_from_sv(sv)
    #define raw_cstr_from_sv(sv)                    jstring_raw_cstr_from_sv(sv)

#endif // JSTRING_UNSTRIP_PREFIX


#endif // JSTRING_H
