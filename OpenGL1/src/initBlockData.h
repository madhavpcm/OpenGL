#pragma once
#include<iostream>
#include<vector>
#include"../../src/blockMaterials.h"
#include<fstream>
#include"nholmanjson/json.hpp"

using json = nlohmann::json;

void initBlockDatas(const std::vector<block_Materials>& database);