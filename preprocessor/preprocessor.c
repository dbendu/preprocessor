#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#include "preprocessor.h"
#include "preprocessor_helpers.h"
#include "variables_manager/variables_manager.h"

#define MAX_INPUT_LEN 80

static char input_buffer[MAX_INPUT_LEN + 1];

#pragma region Input

static char* read_input()
{
    fgets(input_buffer, MAX_INPUT_LEN + 1, stdin);
    return input_buffer;
}

static bool input_ended(const char* input)
{
    return strcmp(input, "\n") == 0;
}

static void process_input(const char* input, t_variables_manager* variables_manager)
{
    if (is_comment(input))
        return;

    while (contains_replacements(input))
    {
        char* replacement_pos = find_replacement(input);

        t_variable* var = determine_variable_to_replacement(replacement_pos, variables_manager);

        replace(replacement_pos, var);
    }

    if (is_variable_definition(input))
    {
        t_variable* var = extract_variable(input);
        varman_add_or_update_var(variables_manager, var);
    }
    else if (is_ordinary_string(input))
        printf("%s\n", input);
}

#pragma endregion

void process()
{
    t_variables_manager* variables_manager = varman_create();

    while (true)
    {
        char* input = read_input();

        if (input_ended(input))
            break;

        process_input(input, variables_manager);
    }

    varman_destroy(variables_manager);
}
