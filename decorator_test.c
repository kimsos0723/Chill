#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct chill_pointer chill_string;
typedef struct chill_blueprint chill_blueprint;

#define CONCAT_(x,y) x##y
#define GEN_FUNC_NAME(x,y) CONCAT_(x,y)

#define ADD_BRUEPRINT(__url, __options, __fn_name) \
    extern chill_string __fn_name(chill_string options);\
    void __attribute__((constructor)) GEN_FUNC_NAME(a, __COUNTER__ ) () {\
        __fn_name(make_chill_string(#__options));\
    }\
    chill_string __fn_name(chill_string options)

struct chill_pointer {
    char* str;
    size_t len;
};

struct chill_blueprint {
    chill_string url;
    chill_string options;    
};

extern chill_string make_chill_string(char* str);

ADD_BRUEPRINT("/", foo1, foo) {
    printf("%s\n", options.str);
    return make_chill_string("bar");
}

ADD_BRUEPRINT("/", bar2, bar) {
    printf("%s\n", options.str);
    return make_chill_string("bar");
}

int main()
{
    
    return 0;
}

chill_string make_chill_string(char* str) {
    chill_string a = { str, strlen(str) };    
    return a;
}


