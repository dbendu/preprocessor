#include "stddef.h"
#include "ctype.h"
#include "string.h"

#include "preprocessor_helpers.h"
#include "variable/variable.h"
#include "str/str.h"

static char replacement_symbol = '$';
static char assignment_operator = '=';
static char comment_symbol = '#';

#pragma region StringProcessors

bool is_variable_definition(const char* str)
{
    return
        !is_comment(str) &&
        isalpha(str[0]) &&
        strchr(str, assignment_operator) != NULL;
}

bool is_comment(const char* str)
{
    return str[0] == comment_symbol;
}

bool contains_replacements(const char* str)
{
    return strchr(str, replacement_symbol) != NULL;
}

bool is_ordinary_string(const char* str)
{
    return
        !is_variable_definition(str) &&
        !is_comment(str) &&
        !contains_replacements(str);
}

static char next_symbol(const char* str)
{
    return str[1];
}

#pragma endregion

char* find_replacement(const char* str)
{
    char* replacement_symbol_pos = strchr(str, replacement_symbol);

    while (next_symbol(replacement_symbol_pos) == replacement_symbol)
        replacement_symbol_pos += 1;

    return replacement_symbol_pos;
}

t_variable* extract_variable(const char* str)
{
    const char* const assignment_operator_position = strchr(str, assignment_operator);

    const size_t str_len = strlen(str);
    const size_t var_name_len = assignment_operator_position - str;
    const size_t var_value_len = str_len - (assignment_operator_position + 1 - str);

    char* var_name = substr(str, var_name_len);
    char* var_value = substr(assignment_operator_position + 1, var_value_len);

    return variable_create(var_name, var_value);
}

t_variable* determine_variable_to_replacement(const char* replacement, t_variables_manager* variables_manager)
{
    t_variable* variable_to_replacement = varman_get_variable_by_index(variables_manager, 0);

    for (size_t i = 0; i < varman_vars_count(variables_manager); ++i)
    {
        t_variable* var = varman_get_variable_by_index(variables_manager, i);

        if (strstr(var->name, replacement) != NULL && strlen(var->name) > strlen(variable_to_replacement->name))
            variable_to_replacement = var;
    }

    return variable_to_replacement;
}

void replace(char* replacement_pos, t_variable* variable)
{
    strrep(
        replacement_pos,
        strlen(variable->name) + 1,
        variable->value,
        strlen(variable->value));
}
