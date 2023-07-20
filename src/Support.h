#pragma once

#include <string>
#include <memory>
#include <vector>

using CSVData = std::vector<std::vector<std::string>>;

std::unique_ptr<CSVData> readCSV(const std::string &foo);
void foo(const std::string &csvFilePath);