#include <stdio.h>
#include <string.h>

#define JSTRING_IMPLEMENTATION
#define JSTRING_UNSTRIP_PREFIX
#include "../jstring.h"

int main() {
    JSTRING_String_View sv = jstring_sv_from_cstr("Hello world, from string view!");
    printf("First test: %s\n", jstring_cstr_from_sv(sv));
    
    const char* data = "Hello world, from parts!";
    sv = jstring_sv_from_parts(data, strlen(data));
    printf("Second test: %s\n", jstring_cstr_from_sv(sv));

    const char* data2 = "Invalid data";
    JSTRING_Result ok;
    sv = jstring_safe_sv_from_parts(data2, strlen(data2)+1, &ok);
    if(ok == JSTRING_SUCCESS) {
        printf("Third test: you shouldn't be here...\n");
    } else {
        printf("Third test: couldn't create string view\n");
    }
}
