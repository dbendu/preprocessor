#pragma once

#include "stdbool.h"

#include "variables_manager/variables_manager.h"
#include "variable/variable.h"

bool is_variable_definition(const char* str);
bool is_comment(const char* str);
bool is_ordinary_string(const char* str);
bool contains_replacements(const char* str);

char* find_replacement(const char* str);
t_variable* extract_variable(const char* str);
t_variable* determine_variable_to_replacement(const char*replacement, t_variables_manager* variables_manager);

void replace(char* replacement_pos, t_variable* variable);
