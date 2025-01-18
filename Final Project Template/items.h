#pragma once

#include <stdbool.h>

typedef struct item{
    int id;
    char text1[20]; // can edit name
    char text2[20]; // can edit name
    float price;
    bool inStock;
    char date[11];
    int inventory;
} Item;