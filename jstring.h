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
#define JSTRING_NULLCHAR (char)0

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


// ===================
// || Query methods ||
// ===================

// Returns the 'count' value of the String view (made just for readability).
JSTRINGDEF size_t jstring_sv_length(JSTRING_String_View sv);
// Returns if the String view is empty.
// NOTE: the spaces are ignored and the method is case sensitive.
JSTRINGDEF bool   jstring_sv_is_empty(JSTRING_String_View sv);
// Returns the character at a certain position in the String view.
// NOTE: 'ok' argument defines if the index is valid and the method is case sensitive.
JSTRINGDEF char   jstring_sv_char_at(JSTRING_String_View sv, size_t index, JSTRING_Result* ok);
// Returns whether a String view contains a certain String view.
// NOTE: the method is case sensitive.
JSTRINGDEF bool   jstring_sv_contains(JSTRING_String_View sv, JSTRING_String_View str);
// Returns whether a String view starts with a certain prefix.
// NOTE: spaces are NOT ignored and the method is case sensitive.
JSTRINGDEF bool   jstring_sv_starts_with(JSTRING_String_View sv, JSTRING_String_View prefix);
// Returns whether a String view ends with a certain prefix.
// NOTE: spaces are NOT ignored and the method is case sensitive.
JSTRINGDEF bool   jstring_sv_ends_with(JSTRING_String_View sv, JSTRING_String_View suffix);
// Returns the start index of a string found into a certain String view.
// Int: 
// - -1 means the string is not found
// NOTE: the method is case sensitive.
JSTRINGDEF int    jstring_sv_index_of(JSTRING_String_View sv, JSTRING_String_View str);
// Returns the end index of a string found into a certain String view.
// Int: 
// - -1 means the string is not found
// NOTE: the method is case sensitive.
JSTRINGDEF int    jstring_sv_last_index_of(JSTRING_String_View sv, JSTRING_String_View str);
// Returns whether a String view contains a certain String view.
// NOTE: the method is NOT case sensitive.
JSTRINGDEF bool   jstring_sv_contains_ignore_case(JSTRING_String_View sv, JSTRING_String_View str);
// Returns whether a String view starts with a certain prefix.
// NOTE: spaces are NOT ignored and the method is NOT case sensitive.
JSTRINGDEF bool   jstring_sv_starts_with_ignore_case(JSTRING_String_View sv, JSTRING_String_View prefix);
// Returns whether a String view ends with a certain prefix.
// NOTE: spaces are NOT ignored and the method is NOT case sensitive.
JSTRINGDEF bool   jstring_sv_ends_with_ignore_case(JSTRING_String_View sv, JSTRING_String_View suffix);
// Returns the start index of a string found into a certain String view.
// Int: 
// - -1 means the string is not found
// NOTE: the method is NOT case sensitive.
JSTRINGDEF int    jstring_sv_index_of_ignore_case(JSTRING_String_View sv, JSTRING_String_View str);
// Returns the end index of a string found into a certain String view.
// Int: 
// - -1 means the string is not found
// NOTE: the method is NOT case sensitive.
JSTRINGDEF int    jstring_sv_last_index_of_ignore_case(JSTRING_String_View sv, JSTRING_String_View str);


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


// ===================
// || Start Queries ||
// ===================


JSTRINGDEF size_t jstring_sv_length(JSTRING_String_View sv) {
    return sv.count;
}

JSTRINGDEF bool jstring_sv_is_empty(JSTRING_String_View sv) {
    JSTRING_String_View trimmed = jstring_sv_trim(sv);
    return trimmed.count == 0;
}

JSTRINGDEF char jstring_sv_char_at(JSTRING_String_View sv, size_t index, JSTRING_Result* ok) {
    if(index >= sv.count) {
        *ok = JSTRING_FAILURE;
        return JSTRING_NULLCHAR;
    }
    *ok = JSTRING_SUCCESS;
    return sv.data[index];
}

JSTRINGDEF bool jstring_sv_contains(JSTRING_String_View sv, JSTRING_String_View str) {
    if(str.count == 0) { return true; }
    if(str.count > sv.count) { return false; }
    
    for(int i = 0; i <= sv.count - str.count; i++) {
        int j = 0;
        while(j < str.count && sv.data[i+j] == str.data[j]) {
            j++;
        }
        if(j == str.count) { return true; }
    }

    return false;
}

JSTRINGDEF bool jstring_sv_starts_with(JSTRING_String_View sv, JSTRING_String_View prefix) {
    if(prefix.count == 0) { return true; }
    if(prefix.count > sv.count) { return false; }
    
    for(int i = 0; i < prefix.count; i++) {
        if(sv.data[i] != prefix.data[i]) { return false; }
    }
    return true;
}

JSTRINGDEF bool jstring_sv_ends_with(JSTRING_String_View sv, JSTRING_String_View suffix) {
    if(suffix.count == 0) { return true; }
    if(suffix.count > sv.count) { return false; }
    
    int offset = sv.count - suffix.count;
    for(int i = 0; i < suffix.count; i++) {
        if(sv.data[offset+i] != suffix.data[i]) { return false; }
    }
    return true;
}

JSTRINGDEF int jstring_sv_index_of(JSTRING_String_View sv, JSTRING_String_View str) {
    if (str.count == 0) { return 0; }
    if (str.count > sv.count) { return -1; }
    for (size_t i = 0; i <= sv.count - str.count; i++) {
        size_t j = 0;
        while (j < str.count && sv.data[i + j] == str.data[j]) {
            j++;
        }
        if (j == str.count) { return (int)i; }
    }
    return -1;
}

JSTRINGDEF int jstring_sv_last_index_of(JSTRING_String_View sv, JSTRING_String_View str) {
    if (str.count == 0) { return (int)sv.count; }
    if (str.count > sv.count) { return -1; }
    
    for (size_t i = sv.count - str.count; ; i--) {
        size_t j = 0;
        while (j < str.count && sv.data[i + j] == str.data[j]) {
            j++;
        }
        if (j == str.count) { return (int)i; }
        if (i == 0) { break; }
    }
    return -1;
}

JSTRINGDEF bool jstring_sv_contains_ignore_case(JSTRING_String_View sv, JSTRING_String_View str) {
    if(str.count == 0) { return true; }
    if(str.count > sv.count) { return false; }
    
    for(int i = 0; i <= sv.count - str.count; i++) {
        int j = 0;
        while(j < str.count && tolower(sv.data[i+j]) == tolower(str.data[j])) {
            j++;
        }
        if(j == str.count) { return true; }
    }

    return false;
}

JSTRINGDEF bool jstring_sv_starts_with_ignore_case(JSTRING_String_View sv, JSTRING_String_View prefix) {
    if(prefix.count == 0) { return true; }
    if(prefix.count > sv.count) { return false; }
    
    for(int i = 0; i < prefix.count; i++) {
        if(tolower(sv.data[i]) != tolower(prefix.data[i])) { return false; }
    }
    return true;
}

JSTRINGDEF bool jstring_sv_ends_with_ignore_case(JSTRING_String_View sv, JSTRING_String_View suffix) {
    if(suffix.count == 0) { return true; }
    if(suffix.count > sv.count) { return false; }
    
    int offset = sv.count - suffix.count;
    for(int i = 0; i < suffix.count; i++) {
        if(tolower(sv.data[offset+i]) != tolower(suffix.data[i])) { return false; }
    }
    return true;
}

JSTRINGDEF int jstring_sv_index_of_ignore_case(JSTRING_String_View sv, JSTRING_String_View str) {
    if (str.count == 0) { return 0; }
    if (str.count > sv.count) { return -1; }
    for (size_t i = 0; i <= sv.count - str.count; i++) {
        size_t j = 0;
        while (j < str.count && tolower(sv.data[i + j]) == tolower(str.data[j])) {
            j++;
        }
        if (j == str.count) { return (int)i; }
    }
    return -1;
}

JSTRINGDEF int jstring_sv_last_index_of_ignore_case(JSTRING_String_View sv, JSTRING_String_View str) {
    if (str.count == 0) { return (int)sv.count; }
    if (str.count > sv.count) { return -1; }
    
    for (size_t i = sv.count - str.count; ; i--) {
        size_t j = 0;
        while (j < str.count && tolower(sv.data[i + j]) == tolower(str.data[j])) {
            j++;
        }
        if (j == str.count) { return (int)i; }
        if (i == 0) { break; }
    }
    return -1;
}


// =================
// || End Queries ||
// =================


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


    #define sv_length(sv)                           jstring_sv_length(sv)
    #define sv_is_empty(sv)                         jstring_sv_is_empty(sv)
    #define sv_char_at(sv, index, ok)               jstring_sv_char_at(sv, index, ok)
    #define sv_contains(sv, str)                    jstring_sv_contains(sv, str)
    #define sv_starts_with(sv, prefix)              jstring_sv_starts_with(sv, prefix)
    #define sv_ends_with(sv, suffix)                jstring_sv_ends_with(sv, suffix)
    #define sv_index_of(sv, str)                    jstring_sv_index_of(sv, str)
    #define sv_last_index_of(sv, str)               jstring_sv_last_index_of(sv, str)
    #define sv_contains_ignore_case(sv, str)        jstring_sv_contains_ignore_case(sv, str)
    #define sv_starts_with_ignore_case(sv, prefix)  jstring_sv_starts_with_ignore_case(sv, prefix)
    #define sv_ends_with_ignore_case(sv, suffix)    jstring_sv_ends_with_ignore_case(sv, suffix)
    #define sv_index_of_ignore_case(sv, str)        jstring_sv_index_of_ignore_case(sv, str)
    #define sv_last_index_of_ignore_case(sv, str)   jstring_sv_last_index_of_ignore_case(sv, str)

#endif // JSTRING_UNSTRIP_PREFIX


#endif // JSTRING_H
