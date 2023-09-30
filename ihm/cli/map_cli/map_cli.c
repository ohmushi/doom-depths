
//
// Created by Theo OMNES on 28/09/2023.
//

#include <stdio.h>
#include "../cli_ihm.h"
#include "../../../infrastructure/utils/log/log.h"

Position ask_player_zone_position_to_go(Map map);
void display_map(Map m);


Position enter_map(Map m) {
    Position p = no_position();
    while (position_is_in_map_and_not_empty(p, m) == false) {
        display_map(m);
        p = ask_player_zone_position_to_go(m);
    }
    return p;
}


/*
     a   b   c
0           [x]
1   [x] [x] [x]
2   [x]
*/
void display_map(Map m) {
    for(int i = 0; i < m.width+1; i++) {
        if(i == 0) fputs("\t", stdout);
        else fprintf(stdout, " %c\t", 'a' + i-1);
    }
    fputc('\n', stdout);
    for(int row = 0; row < m.height; row++) {
        fprintf(stdout, "%d\t", row+1);
        for(int col = 0; col < m.width; col++) {
            Position p = position(col, row);
            Zone z = get_zone_in_map_by_position(m, p);
            switch (z.status) {
                case ZONE_EMPTY:
                    fputs("\t", stdout);
                    break;
                case NOT_DISCOVERED:
                    fputs("[o]\t", stdout);
                    break;
                case ZONE_FINISHED:
                    fputs("[x]\t", stdout);
                    break;
            }
        }
        fputc('\n', stdout);
    }
    fputc('\n', stdout);
}

Position ask_player_zone_position_to_go(Map map) {
    fprintf(stdout, "Select zone column[a-%c] and row[1-%d]", 'a'+map.width-1, map.height);
    fputs("\ncolumn: ", stdout);
    char column = -1;
    while(column < 'a' || column >= 'a' + map.width) {
        fflush(stdin);
        column = fgetc(stdin);
    }
    uint16_t row = -1;
    fputs("row: ", stdout);
    while(row < 1 || row > map.height) {
        fflush(stdin);
        scanf("%hd", &row);
    }

    Position p = position(column-'a', row-1);
    char* position_str = position_to_string(p);
    log_info(position_str);
    free(position_str);

    return p;
}