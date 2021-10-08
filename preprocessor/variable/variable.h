#pragma once

#include "stdbool.h"

typedef struct s_variable
{
    const char* name;
    const char* value;
} t_variable;

t_variable* variable_create(const char* name, const char* value);
void variable_destroy(t_variable* variable);

bool variables_have_same_names(const t_variable* lhs, const t_variable* rhs);

void variable_update_value(t_variable* variable, const char* value);