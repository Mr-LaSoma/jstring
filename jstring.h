#ifndef JSTRING_H_
#define JSTRING_H_

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

#define JSTRING_NULLPTR_ NULL
#define JSTRING_NULLCHAR_ '\0'

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

// Returns a String_View from a null-terminated string.
// Example: jstring_sv_from_cstr("hello") → { data: "hello", count: 5 }
JSTRINGDEF JSTRING_String_View jstring_sv_from_cstr(const char* cstr);

// Returns a String_View from a pointer and a length.
// NOTE: if 'count' is greater than the actual length of 'data', behavior is undefined.
// Use [jstring_safe_sv_from_parts] if 'count' cannot be guaranteed.
JSTRINGDEF JSTRING_String_View jstring_sv_from_parts(const char* data, size_t count);

// Returns a String_View from a pointer and a length, with bounds validation.
// Sets 'ok' to JSTRING_FAILURE if 'count' exceeds the actual length of 'data'.
// On failure, returns an empty String_View.
JSTRINGDEF JSTRING_String_View jstring_safe_sv_from_parts(const char* data, size_t count, JSTRING_Result* ok);

// Returns a null-terminated const char* from a String_View.
// The returned string is heap-allocated and must be freed by the caller.
JSTRINGDEF const char* jstring_cstr_from_sv(JSTRING_String_View sv);

// Returns a heap-allocated const char* from a String_View, WITHOUT a null terminator.
// The returned pointer must be freed by the caller.
// Use [jstring_cstr_from_sv] if you need a null-terminated string.
JSTRINGDEF const char* jstring_raw_cstr_from_sv(JSTRING_String_View sv);

// Frees the heap-allocated data owned by a String_View and resets it to empty.
// NOTE: Only call this on String_Views returned by owning functions
//   (e.g. to_lower, to_upper, substring, replace, replace_all, replace_first).
// Calling this on a non-owning String_View (e.g. from trim, sv_from_cstr, sv_from_parts)
// is undefined behavior.
// Safe to call multiple times on the same String_View (no double-free).
// Safe to call with sv == NULL.
JSTRINGDEF void jstring_sv_free(JSTRING_String_View* sv);

// ========================
// || Comparison methods ||
// ========================

// Compares two String_Views lexicographically (case sensitive).
// Returns:
//   -1 if 'a' comes before 'b'
//    0 if 'a' and 'b' are equal
//    1 if 'a' comes after 'b'
// Example: compare("apple", "banana") → -1
JSTRINGDEF int jstring_sv_compare(JSTRING_String_View a, JSTRING_String_View b);

// Returns true if 'a' and 'b' contain exactly the same characters (case sensitive).
// Example: equals("Hello", "hello") → false
JSTRINGDEF bool jstring_sv_equals(JSTRING_String_View a, JSTRING_String_View b);

// Compares two String_Views lexicographically (case insensitive).
// Returns:
//   -1 if 'a' comes before 'b'
//    0 if 'a' and 'b' are equal
//    1 if 'a' comes after 'b'
// Example: compare_ignore_case("Apple", "apple") → 0
JSTRINGDEF int jstring_sv_compare_ignore_case(JSTRING_String_View a, JSTRING_String_View b);

// Returns true if 'a' and 'b' contain the same characters, ignoring case.
// Example: equals_ignore_case("Hello", "hello") → true
JSTRINGDEF bool jstring_sv_equals_ignore_case(JSTRING_String_View a, JSTRING_String_View b);


// ===================
// || Query methods ||
// ===================

// Returns the number of characters in the String_View.
// Equivalent to accessing sv.count directly — provided for readability.
JSTRINGDEF size_t jstring_sv_length(JSTRING_String_View sv);

// Returns true if the String_View has no characters (count == 0).
// NOTE: doesn't ignore spaces — " " is NOT considered empty.
JSTRINGDEF bool jstring_sv_is_empty(JSTRING_String_View sv);

// Returns true if the String_View has no characters (count == 0).
// NOTE: does ignore spaces — " " is considered empty.
JSTRINGDEF bool jstring_sv_is_blank(JSTRING_String_View sv);

// Returns the character at position 'index' (case sensitive).
// Sets 'ok' to JSTRING_FAILURE if 'index' is out of bounds, and returns '\0'.
// Example: char_at("hello", 1, &ok) → 'e'
JSTRINGDEF char jstring_sv_char_at(JSTRING_String_View sv, size_t index, JSTRING_Result* ok);

// Returns true if 'sv' contains 'str' as a substring (case sensitive).
// Returns true if 'str' is empty. 
// Example: contains("hello world", "world") → true
JSTRINGDEF bool jstring_sv_contains(JSTRING_String_View sv, JSTRING_String_View str);

// Returns true if 'sv' begins with 'prefix' (case sensitive).
// Returns true if 'prefix' is empty. 
// Example: starts_with("hello", "hel") → true
JSTRINGDEF bool jstring_sv_starts_with(JSTRING_String_View sv, JSTRING_String_View prefix);

// Returns true if 'sv' ends with 'suffix' (case sensitive).
// Returns true if 'suffix' is empty.
// Example: ends_with("hello", "llo") → true
JSTRINGDEF bool jstring_sv_ends_with(JSTRING_String_View sv, JSTRING_String_View suffix);

// Returns the index of the first occurrence of 'str' inside 'sv' (case sensitive).
// Returns -1 if 'str' is not found.
// Example: index_of("hello world", "world") → 6
JSTRINGDEF int jstring_sv_index_of(JSTRING_String_View sv, JSTRING_String_View str);

// Returns the index of the last occurrence of 'str' inside 'sv' (case sensitive).
// Returns -1 if 'str' is not found.
// Example: last_index_of("hello hello", "hello") → 6
JSTRINGDEF int jstring_sv_last_index_of(JSTRING_String_View sv, JSTRING_String_View str);

// Returns true if 'sv' contains 'str' as a substring (case insensitive).
// Returns true if 'str' is empty (mirrors Java behavior).
// Example: contains_ignore_case("Hello World", "world") → true
JSTRINGDEF bool jstring_sv_contains_ignore_case(JSTRING_String_View sv, JSTRING_String_View str);

// Returns true if 'sv' begins with 'prefix' (case insensitive).
// Returns true if 'prefix' is empty.
// Example: starts_with_ignore_case("Hello", "hel") → true
JSTRINGDEF bool jstring_sv_starts_with_ignore_case(JSTRING_String_View sv, JSTRING_String_View prefix);

// Returns true if 'sv' ends with 'suffix' (case insensitive).
// Returns true if 'suffix' is empty.
// Example: ends_with_ignore_case("Hello", "LLO") → true
JSTRINGDEF bool jstring_sv_ends_with_ignore_case(JSTRING_String_View sv, JSTRING_String_View suffix);

// Returns the index of the first occurrence of 'str' inside 'sv' (case insensitive).
// Returns -1 if 'str' is not found.
// Example: index_of_ignore_case("Hello World", "WORLD") → 6
JSTRINGDEF int jstring_sv_index_of_ignore_case(JSTRING_String_View sv, JSTRING_String_View str);

// Returns the index of the last occurrence of 'str' inside 'sv' (case insensitive).
// Returns -1 if 'str' is not found.
// Example: last_index_of_ignore_case("Hello Hello", "HELLO") → 6
JSTRINGDEF int jstring_sv_last_index_of_ignore_case(JSTRING_String_View sv, JSTRING_String_View str);


// ============================
// || Transformation methods ||
// ============================

// Returns a String_View with leading and trailing whitespace removed.
// Uses isspace() — removes spaces, tabs, \n, \r, \f, \v.
// Does not allocate — returns a view into the original data.
// Example: trim("  hello  ") → "hello"
JSTRINGDEF JSTRING_String_View jstring_sv_trim(JSTRING_String_View sv);

// Returns a String_View with leading whitespace (ASCII <= 32) removed.
// Example: trim_left("  hello  ") → "hello  "
JSTRINGDEF JSTRING_String_View jstring_sv_trim_left(JSTRING_String_View sv);

// Returns a String_View with trailing whitespace (ASCII <= 32) removed.
// Example: trim_right("  hello  ") → "  hello"
JSTRINGDEF JSTRING_String_View jstring_sv_trim_right(JSTRING_String_View sv);

// Returns a new String_View with all characters converted to lowercase.
// Sets 'ok' to JSTRING_FAILURE if memory allocation fails.
// NOTE: The returned String_View owns its data — the caller must free() sv.data when done.
// Example: to_lower("Hello WORLD", &ok) → "hello world"
JSTRINGDEF JSTRING_String_View jstring_sv_to_lower(JSTRING_String_View sv, JSTRING_Result* ok);

// Returns a new String_View with all characters converted to uppercase.
// Sets 'ok' to JSTRING_FAILURE if memory allocation fails.
// NOTE: The returned String_View owns its data — the caller must free() sv.data when done.
// Example: to_upper("Hello World", &ok) → "HELLO WORLD"
JSTRINGDEF JSTRING_String_View jstring_sv_to_upper(JSTRING_String_View sv, JSTRING_Result* ok);

// Returns a sub-view of 'sv' from index 'beg' (inclusive) to 'end' (exclusive).
// Does not allocate — returns a view into the original data.
// Sets 'ok' to JSTRING_FAILURE if:
//   - 'beg' > 'end'
//   - 'end' > sv.count
// On failure, returns an empty String_View.
// Example: substring("hello", 1, 3, &ok) → "el"
JSTRINGDEF JSTRING_String_View jstring_sv_substring(JSTRING_String_View sv, size_t beg, size_t end, JSTRING_Result* ok);

// Returns a new String_View with the first 'count' occurrences of 'from' replaced with 'to'.
// If 'from' is empty or 'count' is 0, returns an unmodified copy of 'sv'.
// The returned String_View owns its data — the caller must free() sv.data when done.
// Returns an empty String_View if memory allocation fails.
// Example: replace("foo foo foo", "foo", "bar", 2) → "bar bar foo"
JSTRINGDEF JSTRING_String_View jstring_sv_replace(JSTRING_String_View sv, JSTRING_String_View from, JSTRING_String_View to, size_t count);

// Returns a new String_View with all occurrences of 'from' replaced with 'to'.
// If 'from' is empty, returns an unmodified copy of 'sv'.
// The returned String_View owns its data — the caller must free() sv.data when done.
// Returns an empty String_View if memory allocation fails.
// Example: replace_all("foo foo foo", "foo", "bar") → "bar bar bar"
JSTRINGDEF JSTRING_String_View jstring_sv_replace_all(JSTRING_String_View sv, JSTRING_String_View from, JSTRING_String_View to);

// Returns a new String_View with only the first occurrence of 'from' replaced with 'to'.
// If 'from' is empty, returns an unmodified copy of 'sv'.
// The returned String_View owns its data — the caller must free() sv.data when done.
// Returns an empty String_View if memory allocation fails.
// Example: replace_first("foo foo foo", "foo", "bar") → "bar foo foo"
JSTRINGDEF JSTRING_String_View jstring_sv_replace_first(JSTRING_String_View sv, JSTRING_String_View from, JSTRING_String_View to);

#endif // JSTRING_H_

#ifdef JSTRING_IMPLEMENTATION 


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
        if(ok) *ok = JSTRING_FAILURE;
        return jstring_sv_from_parts("", 0);
    }

    if(ok) *ok = JSTRING_SUCCESS;
    return jstring_sv_from_parts(data, count);
}

JSTRINGDEF const char* jstring_cstr_from_sv(JSTRING_String_View sv) {
    char* cstr = (char*)malloc(sv.count + 1);
    if(cstr == JSTRING_NULLPTR_) return JSTRING_NULLPTR_;

    memcpy(cstr, sv.data, sv.count);
    cstr[sv.count] = JSTRING_NULLCHAR_;
    return cstr;
}

JSTRINGDEF const char* jstring_raw_cstr_from_sv(JSTRING_String_View sv) {
    char* cstr = (char*)malloc(sv.count);
    if(cstr == JSTRING_NULLPTR_) return JSTRING_NULLPTR_;

    memcpy(cstr, sv.data, sv.count);
    return cstr;
}

JSTRINGDEF void jstring_sv_free(JSTRING_String_View* sv) {
    (if sv == JSTRING_NULLPTR_ || sv->data == JSTRING_NULLPTR_) return null;
    free((void*)sv->data);
    sv->data = JSTRING_NULLPTR_;
    sv->count = 0;
}

// ======================
// || End Constructors ||
// ======================


// ======================
// || Start Comparison ||
// ======================


JSTRINGDEF int jstring_sv_compare(JSTRING_String_View a, JSTRING_String_View b) {
    size_t minlen = a.count <= b.count ? a.count : b.count;
    for(size_t i = 0; i < minlen; i++) {
        if(a.data[i] < b.data[i]) { return -1; }
        else if(a.data[i] > b.data[i]) { return 1; }
    }
    if(a.count < b.count) { return -1; }
    if(a.count > b.count) { return 1;}
    return 0;
}

JSTRINGDEF bool jstring_sv_equals(JSTRING_String_View a, JSTRING_String_View b) {
    if(a.count != b.count) { return false; }
    for(size_t i = 0; i < a.count; i++) {
        if(a.data[i] != b.data[i]) { return false; }
    }
    return true;
}

JSTRINGDEF int jstring_sv_compare_ignore_case(JSTRING_String_View a, JSTRING_String_View b) {
    size_t minlen = a.count <= b.count ? a.count : b.count;
    for(size_t i = 0; i < minlen; i++) {
        char ac = tolower((unsigned char)a.data[i]);
        char bc = tolower((unsigned char)b.data[i]);

        if(ac < bc) { return -1; }
        else if(ac > bc) { return 1; }
    }
    if(a.count < b.count) { return -1; }
    if(a.count > b.count) { return 1;}
    return 0;
}

JSTRINGDEF bool jstring_sv_equals_ignore_case(JSTRING_String_View a, JSTRING_String_View b) {
    if(a.count != b.count) { return false; }
    for(size_t i = 0; i < a.count; i++) {
        if(tolower((unsigned char)a.data[i]) != tolower(b.data[i])) { return false; }
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
    return sv.count == 0;
}

JSTRINGDEF bool jstring_sv_is_blank(JSTRING_String_View sv) {
    JSTRING_String_View trimmed = jstring_sv_trim(sv);
    return trimmed.count == 0;
}

JSTRINGDEF char jstring_sv_char_at(JSTRING_String_View sv, size_t index, JSTRING_Result* ok) {
    if(index >= sv.count) {
        if(ok) *ok = JSTRING_FAILURE;
        return JSTRING_NULLCHAR_;
    }
    if(ok) *ok = JSTRING_SUCCESS;
    return sv.data[index];
}

JSTRINGDEF bool jstring_sv_contains(JSTRING_String_View sv, JSTRING_String_View str) {
    if(str.count == 0) { return true; }
    if(str.count > sv.count) { return false; }
    
    for(size_t i = 0; i <= sv.count - str.count; i++) {
        size_t j = 0;
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
    
    for(size_t i = 0; i < prefix.count; i++) {
        if(sv.data[i] != prefix.data[i]) { return false; }
    }
    return true;
}

JSTRINGDEF bool jstring_sv_ends_with(JSTRING_String_View sv, JSTRING_String_View suffix) {
    if(suffix.count == 0) { return true; }
    if(suffix.count > sv.count) { return false; }
    
    size_t offset = sv.count - suffix.count;
    for(size_t i = 0; i < suffix.count; i++) {
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
    
    for(size_t i = 0; i <= sv.count - str.count; i++) {
        size_t j = 0;
        while(j < str.count && tolower((unsigned char)sv.data[i+j]) == tolower(str.data[j])) {
            j++;
        }
        if(j == str.count) { return true; }
    }

    return false;
}

JSTRINGDEF bool jstring_sv_starts_with_ignore_case(JSTRING_String_View sv, JSTRING_String_View prefix) {
    if(prefix.count == 0) { return true; }
    if(prefix.count > sv.count) { return false; }
    
    for(size_t i = 0; i < prefix.count; i++) {
        if(tolower((unsigned char)sv.data[i]) != tolower(prefix.data[i])) { return false; }
    }
    return true;
}

JSTRINGDEF bool jstring_sv_ends_with_ignore_case(JSTRING_String_View sv, JSTRING_String_View suffix) {
    if(suffix.count == 0) { return true; }
    if(suffix.count > sv.count) { return false; }
    
    size_t offset = sv.count - suffix.count;
    for(size_t i = 0; i < suffix.count; i++) {
        if(tolower((unsigned char)sv.data[offset+i]) != tolower(suffix.data[i])) { return false; }
    }
    return true;
}

JSTRINGDEF int jstring_sv_index_of_ignore_case(JSTRING_String_View sv, JSTRING_String_View str) {
    if (str.count == 0) { return 0; }
    if (str.count > sv.count) { return -1; }
    for (size_t i = 0; i <= sv.count - str.count; i++) {
        size_t j = 0;
        while (j < str.count && tolower((unsigned char)sv.data[i + j]) == tolower(str.data[j])) {
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
        while (j < str.count && tolower((unsigned char)sv.data[i + j]) == tolower(str.data[j])) {
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
    if(data == JSTRING_NULLPTR_) {
        if(ok) *ok = JSTRING_FAILURE;
        return jstring_sv_from_parts("", 0);
    }

    for(size_t i = 0; i < sv.count; i++) {
        data[i] = tolower((unsigned char)sv.data[i]);
    }

    if(ok) *ok = JSTRING_SUCCESS;
    return jstring_sv_from_parts(data, sv.count);
}

JSTRINGDEF JSTRING_String_View jstring_sv_to_upper(JSTRING_String_View sv, JSTRING_Result* ok) {
    char* data = (char*)malloc(sv.count);
    if(data == JSTRING_NULLPTR_) {
        if(ok) *ok = JSTRING_FAILURE;
        return jstring_sv_from_parts("", 0);
    }

    for(size_t i = 0; i < sv.count; i++) {
        data[i] = toupper((unsigned char)sv.data[i]);
    }

    if(ok) *ok = JSTRING_SUCCESS;
    return jstring_sv_from_parts(data, sv.count);
}

JSTRINGDEF JSTRING_String_View jstring_sv_substring(JSTRING_String_View sv, size_t beg, size_t end, JSTRING_Result* ok) {
    if(beg > end || end > sv.count) {
        if(ok) *ok = JSTRING_FAILURE;
        return jstring_sv_from_parts("", 0);
    }
    if(ok) *ok = JSTRING_SUCCESS;
    return jstring_sv_from_parts(sv.data + beg, end - beg);
}

JSTRINGDEF JSTRING_String_View jstring_sv_replace(JSTRING_String_View sv, JSTRING_String_View from, JSTRING_String_View to, size_t count) {
    if(from.count == 0 || count == 0) {
        return jstring_sv_from_parts(sv.data, sv.count);
    }

    size_t replaced = 0;
    size_t i = 0;
    size_t new_len = 0;
    while (i < sv.count) {
        if (replaced < count && i + from.count <= sv.count &&
            memcmp(sv.data + i, from.data, from.count) == 0) {
            new_len += to.count;
            i += from.count;
            replaced++;
        } else {
            new_len += 1;
            i += 1;
        }
    }

    char* data = (char*)malloc(new_len > 0 ? new_len : 1);
    if (data == JSTRING_NULLPTR_) return jstring_sv_from_parts("", 0);

    size_t out = 0;
    replaced = 0;
    i = 0;
    while (i < sv.count) {
        if (replaced < count && i + from.count <= sv.count &&
            memcmp(sv.data + i, from.data, from.count) == 0) {
            memcpy(data + out, to.data, to.count);
            out += to.count;
            i += from.count;
            replaced++;
        } else {
            data[out++] = sv.data[i++];
        }
    }

    return jstring_sv_from_parts(data, new_len);
}

JSTRINGDEF JSTRING_String_View jstring_sv_replace_all(JSTRING_String_View sv, JSTRING_String_View from, JSTRING_String_View to) {
    return jstring_sv_replace(sv, from, to, sv.count);
}
JSTRINGDEF JSTRING_String_View jstring_sv_replace_first(JSTRING_String_View sv, JSTRING_String_View from, JSTRING_String_View to) {
    return jstring_sv_replace(sv, from, to, 1);
}

// ==========================
// || End Transformation ||
// ==========================


#endif // JSTRING_IMPLEMENTATION

#ifndef JSTRING_UNSTRIP_PREFIX_GUARD_
#define JSTRING_UNSTRIP_PREFIX_GUARD_

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
    #define sv_free(sv)                             jstring_sv_free(sv)    

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
    #define sv_is_blank(sv)                         jstring_sv_is_blank(sv)
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

    #define sv_replace(sv, from, to, count)     jstring_sv_replace(sv, from, to, count)
    #define sv_replace_all(sv, from, to)        jstring_sv_replace_all(sv, from, to)
    #define sv_replace_first(sv, from, to)      jstring_sv_replace_first(sv, from, to)

#endif // JSTRING_UNSTRIP_PREFIX

#endif // JSTRING_UNSTRIP_PREFIX_GUARD_
