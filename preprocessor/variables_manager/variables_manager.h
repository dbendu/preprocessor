#pragma once

#include "stddef.h"

#include "../variable/variable.h"
#include "../array/array.h"

typedef struct s_variables_manager
{
    t_array* variables;
} t_variables_manager;

t_variables_manager* varman_create();
void varman_destroy(t_variables_manager* variables_manager);

void varman_add_or_update_var(t_variables_manager* variables_manager, t_variable* variable);
t_variable* varman_get_variable_by_index(t_variables_manager* variables_manager, int pos);

size_t varman_vars_count(t_variables_manager* variables_manager);
