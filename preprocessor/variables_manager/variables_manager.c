#include "stddef.h"
#include "stdlib.h"

#include "variables_manager.h"
#include "../array/array.h"

t_variables_manager* varman_create()
{
    t_variables_manager* varman = malloc(sizeof(t_variables_manager));

    varman->variables = array_create(sizeof(t_variable), (t_element_destroyer)variable_destroy);

    return varman;
}

void varman_destroy(t_variables_manager* variables_manager)
{
    array_destroy(variables_manager->variables);
    free(variables_manager);
}

void varman_add_or_update_var(t_variables_manager* variables_manager, t_variable* variable)
{
    for (size_t i = 0; i < array_length(variables_manager->variables); ++i)
    {
        t_variable* var = varman_get_variable_by_index(variables_manager, i);

        if (variables_have_same_names(var, variable))
        {
            variable_update_value(var, variable->value);
            variable_destroy(variable);
            
            return;
        }
    }

    array_append(variables_manager->variables, &variable);
}

t_variable* varman_get_variable_by_index(t_variables_manager* variables_manager, int pos)
{
    return (t_variable*)array_get_elem(variables_manager->variables, pos);
}

size_t varman_vars_count(t_variables_manager* variables_manager)
{
    return array_length(variables_manager->variables);
}