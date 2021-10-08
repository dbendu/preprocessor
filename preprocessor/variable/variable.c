#include "string.h"
#include "stdbool.h"
#include "stdlib.h"

#include "variable.h"

t_variable* variable_create(const char* name, const char* value)
{
    t_variable* variable = malloc(sizeof(t_variable));

    variable->name = name;
    variable->value = value;

    return variable;
}

void variable_destroy(t_variable* variable)
{
    free((void*)variable->name);
    free((void*)variable->value);

    free(variable);
}

bool variables_have_same_names(const t_variable* lhs, const t_variable* rhs)
{
    return strcmp(lhs->name, rhs->name) == 0;
}

void variable_update_value(t_variable* variable, const char* value)
{
    free((void*)variable->value);
    variable->value = strdup(value);
}