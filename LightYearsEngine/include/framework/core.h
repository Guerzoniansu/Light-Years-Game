#pragma once
#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace ly
{
template<typename T>
using unique = std::unique_ptr<T>; //Using permits us to give a nickname to a type of variable

template<typename T>
using shared = std::shared_ptr<T>; //Here, saying that a variable is of type shared means it is of type std::shared_ptr<T>

template<typename T>
using weak = std::weak_ptr<T>;

template<typename T>
using list = std::vector<T>;

template<typename keyType, typename valType, typename pr = std::less<keyType>>
using map = std::map<keyType, valType, pr>; //The pr type uses std::less which means that the data we want to store should be ordered

template<typename keyType, typename valType, typename hasher = std::hash<keyType>>
using dict = std::unordered_map<keyType, valType, hasher>; //hasher is like a function which takes in the keyValue and spit out a unique index

template<typename T>
using set = std::unordered_set<T>;

using uint8 = unsigned char;

//This is called a macro
#define LOG(M, ...) printf(M"\n", ##__VA_ARGS__)
}