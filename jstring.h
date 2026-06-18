#ifndef JSTRING_H
#define JSTRING_H

// ==========
// || Libs ||
// ==========

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

// Returns a String view from a given const char*.
JSTRINGDEF JSTRING_String_View jstring_sv_from_cstr(const char* cstr);
// Returns a String view from the given parts.
// NOTE: if the 'count' argument is bigger then the actual string, it will break logic... 
// use [safe_sv_from_parts] method to avoid this problem.
JSTRINGDEF JSTRING_String_View jstring_sv_from_parts(const char* data, size_t count);
// Returns a String view from the given parts.
// NOTE: the 'ok' argument defines if the logic is valid or not (see [sv_from_parts] method for specification).
JSTRINGDEF JSTRING_String_View jstring_safe_sv_from_parts(const char* data, size_t count, JSTRING_Result* ok);
// Returns a const char* form a given String view.
// NOTE: this const char* will always have '\0' character at the end.
JSTRINGDEF const char* jstring_cstr_from_sv(JSTRING_String_View sv);
// Returns a const char* from a given String view.
// NOTE: this const char* WON'T always have '\0' character at the end. 
JSTRINGDEF const char* jstring_raw_cstr_from_sv(JSTRING_String_View sv);


// ========================
// || Comparison methods ||
// ========================

// Returns an int reppresenting the lexicall order.
// Int:
// - -1 if 'a' is lexically lesser then 'b',
// - 1 if 'a' is lexically greater then 'b' and
// - 0 if 'a' is equal to 'b'
// NOTE: this method is case sensitive
JSTRINGDEF int jstring_sv_compare(JSTRING_String_View a, JSTRING_String_View b);
// Returns if 'a' have the same exactly characters of 'b'.
// NOTE: this method is case sensitive
JSTRINGDEF bool jstring_sv_equals(JSTRING_String_View a, JSTRING_String_View b);
// Returns an int reppresenting the lexicall order.
// Int:
// - -1 if 'a' is lexically lesser then 'b',
// - 1 if 'a' is lexically greater then 'b' and
// - 0 if 'a' is equal to 'b'
// NOTE: this method is NOT case sensitive
JSTRINGDEF int jstring_sv_compare_ignore_case(JSTRING_String_View a, JSTRING_String_View b);
// Returns if 'a' have the same exactly characters of 'b'.
// NOTE: this method is NOT case sensitive
JSTRINGDEF bool jstring_sv_equals_ignore_case(JSTRING_String_View a, JSTRING_String_View b);


// ============================
// || Transformation methods ||
// ============================

// Returns a String view with all the white spaces on both sides trimmed of.
JSTRINGDEF JSTRING_String_View jstring_sv_trim(JSTRING_String_View sv);
// Returns a String view with all the white spaces on the left side trimmed of.
JSTRINGDEF JSTRING_String_View jstring_sv_trim_left(JSTRING_String_View sv);
// Returns a String view with all the white spaces on the right side trimmed of.
JSTRINGDEF JSTRING_String_View jstring_sv_trim_right(JSTRING_String_View sv);
// Returns a String view with all characters converted to lowercase.
// NOTE: the 'ok' argument defines if the method was able to create the new String view; 
JSTRINGDEF JSTRING_String_View jstring_sv_to_lower(JSTRING_String_View sv, JSTRING_Result* ok);
// Returns a String view with all characters converted to uppercase.
// NOTE: the 'ok' argument defines if the method was able to create the new String view; 
JSTRINGDEF JSTRING_String_View jstring_sv_to_upper(JSTRING_String_View sv, JSTRING_Result* ok);
// Returns a Sub view of a given String view from the index 'beg' (inclusive) to 'end' (exclusive).
// NOTE: the 'ok' argument defines if the method was able to create a new sub string view.
JSTRINGDEF JSTRING_String_View jstring_sv_substring(JSTRING_String_View sv, size_t beg, size_t end, JSTRING_Result* ok);


#ifdef JSTRING_IMPLEMENTATION // TODO: remove 'n' in ifndef


// ========================
// || Start Constructors ||
// ========================

JSTRINGDEF JSTRING_String_View jstring_sv_from_cstr(const char *cstr) {
    return jstring_sv_from_parts(cstr, strlen(cstr)); 
}

JSTRINGDEF JSTRING_String_View jstring_sv_from_parts(const char *data, size_t count) {
    JSTRING_String_View sv;
    sv.data = data; 
    sv.count = count;
    return sv;
}

JSTRINGDEF JSTRING_String_View jstring_safe_sv_from_parts(const char* data, size_t count, JSTRING_Result* ok) {
    size_t len = strlen(data);
    if(count > len) {
        *ok = JSTRING_FAILURE;
        return jstring_sv_from_parts("", 0);
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

// ======================
// || End Constructors ||
// ======================


// ======================
// || Start Comparison ||
// ======================


JSTRINGDEF int jstring_sv_compare(JSTRING_String_View a, JSTRING_String_View b) {
    size_t minlen = a.count <= b.count ? a.count : b.count;
    for(int i = 0; i < minlen; i++) {
        if(a.data[i] < b.data[i]) { return -1; }
        else if(a.data[i] > b.data[i]) { return 1; }
    }
    if(a.count < b.count) { return -1; }
    if(a.count > b.count) { return 1;}
    return 0;
}

JSTRINGDEF bool jstring_sv_equals(JSTRING_String_View a, JSTRING_String_View b) {
    if(a.count != b.count) { return false; }
    for(int i = 0; i < a.count; i++) {
        if(a.data[i] != b.data[i]) { return false; }
    }
    return true;
}

JSTRINGDEF int jstring_sv_compare_ignore_case(JSTRING_String_View a, JSTRING_String_View b) {
    size_t minlen = a.count <= b.count ? a.count : b.count;
    for(int i = 0; i < minlen; i++) {
        char ac = tolower(a.data[i]);
        char bc = tolower(b.data[i]);

        if(ac < bc) { return -1; }
        else if(ac > bc) { return 1; }
    }
    if(a.count < b.count) { return -1; }
    if(a.count > b.count) { return 1;}
    return 0;
}

JSTRINGDEF bool jstring_sv_equals_ignore_case(JSTRING_String_View a, JSTRING_String_View b) {
    if(a.count != b.count) { return false; }
    for(int i = 0; i < a.count; i++) {
        if(tolower(a.data[i]) != tolower(b.data[i])) { return false; }
    }
    return true;
}

// ======================
// || End Comparison ||
// ======================


// ==========================
// || Start Transformation ||
// ==========================

JSTRINGDEF JSTRING_String_View jstring_sv_trim(JSTRING_String_View sv) {
    return jstring_sv_trim_right(jstring_sv_trim_left(sv));
}

JSTRINGDEF JSTRING_String_View jstring_sv_trim_left(JSTRING_String_View sv) {
    size_t i;
    for(i = 0; i < sv.count && isspace(sv.data[i]); i++) {}
    return jstring_sv_from_parts(sv.data + i, sv.count - i);
}

JSTRINGDEF JSTRING_String_View jstring_sv_trim_right(JSTRING_String_View sv) {
    size_t i;
    for(i = 0; i < sv.count && isspace(sv.data[sv.count - 1 - i]); i++) {}
    return jstring_sv_from_parts(sv.data, sv.count - i);
}

JSTRINGDEF JSTRING_String_View jstring_sv_to_lower(JSTRING_String_View sv, JSTRING_Result* ok) {
    char* data = (char*)malloc(sv.count);
    if(data == JSTRING_NULLPTR) {
        *ok = JSTRING_FAILURE;
        return jstring_sv_from_parts("", 0);
    }

    for(int i = 0; i < sv.count; i++) {
        data[i] = tolower(sv.data[i]);
    }

    *ok = JSTRING_SUCCESS;
    return jstring_sv_from_parts(data, sv.count);
}

JSTRINGDEF JSTRING_String_View jstring_sv_to_upper(JSTRING_String_View sv, JSTRING_Result* ok) {
    char* data = (char*)malloc(sv.count);
    if(data == JSTRING_NULLPTR) {
        *ok = JSTRING_FAILURE;
        return jstring_sv_from_parts("", 0);
    }

    for(int i = 0; i < sv.count; i++) {
        data[i] = toupper(sv.data[i]);
    }

    *ok = JSTRING_SUCCESS;
    return jstring_sv_from_parts(data, sv.count);
}

JSTRINGDEF JSTRING_String_View jstring_sv_substring(JSTRING_String_View sv, size_t beg, size_t end, JSTRING_Result* ok) {
    if((beg < 0 && beg >= sv.count) || (end < 0 && end > sv.count)) {
        *ok = JSTRING_FAILURE;
        return jstring_sv_from_parts("", 0);
    }

    size_t len = end-beg;
    char* data = (char*)malloc(len);
    for(int i = 0; i < len; i++) {
       data[i] = sv.data[beg+i];
    }

    *ok = JSTRING_SUCCESS;
    return jstring_sv_from_parts(data, len);
}

// ==========================
// || End Transformation ||
// ==========================


#endif // JSTRING_IMPLEMENTATION


#ifndef JSTRING_UNSTRIP_PREFIX
    
    #define Result          JSTRING_Result    
    #define SUCCESS         JSTRING_SUCCESS 
    #define FAILURE         JSTRING_FAILURE
    #define String_View     JSTRING_String_View
    
    #define sv_from_cstr(cstr)                      jstring_sv_from_cstr(cstr)
    #define sv_from_parts(cstr, count)              jstring_sv_from_parts(cstr, count)
    #define safe_sv_from_parts(cstr, count, ok)     jstring_safe_sv_from_parts(cstr, count, ok)
    #define cstr_from_sv(sv)                        jstring_cstr_from_sv(sv)
    #define raw_cstr_from_sv(sv)                    jstring_raw_cstr_from_sv(sv)
    
    #define sv_compare(a, b)                jstring_sv_compare(a, b)
    #define sv_equals(a, b)                 jstring_sv_equals(a, b)
    #define sv_compare_ignore_case(a, b)    jstring_sv_compare_ignore_case(a, b)
    #define sv_equals_ignore_case(a, b)     jstring_sv_equals_ignore_case(a, b)

    #define sv_trim(sv)                     jstring_sv_trim(sv)
    #define sv_trim_left(sv)                jstring_sv_trim_left(sv)
    #define sv_trim_right(sv)               jstring_sv_trim_right(sv)
    #define sv_to_lower(sv, ok)             jstring_sv_to_lower(sv, ok)
    #define sv_to_upper(sv, ok)             jstring_sv_to_upper(sv, ok)
    #define sv_substring(sv, beg, end, ok)  jstring_sv_substring(sv, beg, end, ok)

#endif // JSTRING_UNSTRIP_PREFIX


#endif // JSTRING_H
