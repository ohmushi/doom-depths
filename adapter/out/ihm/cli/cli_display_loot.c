
//
// Created by Theo OMNES on 01/10/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <loot/loot.h>

#include <port/out/ihm/display_loot.h>

void display_loot(Loot loot) {
    char *s = loot_to_string(loot);
    fprintf(stdout, "\nNew loot: \n%s\n", s);
    free(s);
}