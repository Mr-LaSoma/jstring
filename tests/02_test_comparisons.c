#include <stdio.h>

#define JSTRING_IMPLEMENTATION
#define JSTRING_UNSTRIP_PREFIX
#include "../jstring.h"

int main() {
    JSTRING_String_View a = jstring_sv_from_cstr("hello");
    JSTRING_String_View b = jstring_sv_from_cstr("world!");
    
    const char* aCstr = jstring_cstr_from_sv(a);
    const char* bCstr = jstring_cstr_from_sv(b);
    
    JSTRING_String_View a2 = jstring_sv_from_cstr("HELLO");
    JSTRING_String_View b2 = jstring_sv_from_cstr("WORLD");

    const char* a2Cstr = jstring_cstr_from_sv(a2);
    const char* b2Cstr = jstring_cstr_from_sv(b2);
    
    printf("--- Test Case Sensitive ---\n");
    switch (jstring_sv_compare(a, b)) {
        case -1:
            printf("%s, %s\n", aCstr, bCstr); 
            break;
        case 1:
            printf("%s, %s\n", bCstr, aCstr);
            break;
        case 0:
            printf("Apparently '%s' and '%s' are equals\n", aCstr, bCstr);
            break;
    }

    if(jstring_sv_equals(a, a2)) {
        printf("Yep, this dosn't works. '%s' and '%s' shouldn't be equals\n", aCstr, a2Cstr);
    } else {
        printf("Ok, '%s' and '%s' are different words\n", aCstr, a2Cstr);
    }

    printf("\n--- Test Case Insensitive ---\n");

    if (jstring_sv_equals_ignore_case(a, a2)) {
        printf("Ok, '%s' and '%s' are equals (case-insensitive)\n", aCstr, a2Cstr);
    } else {
        printf("Error, '%s' and '%s' should be equals (case-insensitive)\n", aCstr, a2Cstr);
    }

    switch (jstring_sv_compare_ignore_case(a, b2)) {
        case -1:
            printf("Success: '%s' comes before '%s'\n", aCstr, b2Cstr);
            break;
        case 1:
            printf("Error: '%s' should not come before '%s'\n", b2Cstr, aCstr);
            break;
        case 0:
            printf("Error: '%s' and '%s' should not be equal\n", aCstr, b2Cstr);
            break;
    }

    if (jstring_sv_compare_ignore_case(a, a2) == 0) {
        printf("Success: '%s' and '%s' are the same\n", aCstr, a2Cstr);
    } else {
        printf("Error: '%s' and '%s' are different??\n", aCstr, a2Cstr);
    }

    return 0;
}
