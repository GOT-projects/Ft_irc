#pragma once

#include "../includes.hpp"

bool is_number(const std::string& s);
std::string runUnixCommandAndCaptureOutput(std::string cmd);
bool checkEndString(const std::string &msg, const std::string &regex);
