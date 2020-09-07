#pragma once


void Sieve();

void substitute_str(std::string& iostring, const std::string& before, const std::string& after);

char* substitute_cstr(const char* input, const char before, const char* after);