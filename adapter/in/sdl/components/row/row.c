
//
// Created by Theo OMNES on 15/10/2023.
//

#include "row.h"
#include "port/out/log/log_error.h"
#include "port/out/log/log_info.h"

int get_cell_height(RowCell param);

RowCell cell_by_type(CellType cellType, Cell cell);

Row update_row_rect(Row row);

RowCell button_row_cell(Button button);

Row create_row(int length, ...) {
    Row row;
    row.length = length;
    row.cells = malloc(sizeof(RowCell) * length);
    row.spacing = 0;
    row.rect = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};

    va_list args;
    va_start(args, length);
    for (int i = 0; i < length; ++i) {
        row.cells[i] = cell_by_type(va_arg(args, CellType), (Cell){.button = va_arg(args, Button)});
        int cell_height = get_cell_height(row.cells[i]);
        if(cell_height > row.rect.h) row.rect.h = cell_height;
        row.rect.w += get_cell_width(row.cells[i]);
    }
    va_end(args);

    return row;
}

Row create_row_with_indexes(int length, ...) {
    Row row;
    row.length = length;
    row.cells = malloc(sizeof(RowCell) * length);
    row.spacing = 0;
    row.rect = (SDL_Rect) {.x = 0, .y = 0, .w = 0, .h = 0};

    va_list args;
    va_start(args, length);
    for (int i = 0; i < length; ++i) {
        int index = va_arg(args, int);
        row.cells[index] = cell_by_type(va_arg(args, CellType), (Cell){.button = va_arg(args, Button)});
        int cell_height = get_cell_height(row.cells[index]);
        if(cell_height > row.rect.h) row.rect.h = cell_height;
        row.rect.w += get_cell_width(row.cells[index]);
    }
    va_end(args);

    return row;
}

RowCell cell_by_type(CellType cellType, Cell cell) {
    switch (cellType) {
        case BUTTON: return (RowCell) {.cellType = BUTTON, .cell.button = cell.button};
        default: {
            log_error("cell_by_type: unknown cell type [%d]", cellType);
            return (RowCell) {.cellType = BUTTON, .cell = cell};
        }
    }
}

int get_cell_width(RowCell param) {
    switch (param.cellType) {
        case BUTTON: {
            return param.cell.button.button_rect.w;
        }
        default: {
            log_error("get_cell_width: unknown cell type [%d]", param.cellType);
            return 0;
        }
    }
}

int get_cell_height(RowCell param) {
    switch (param.cellType) {
        case BUTTON: return param.cell.button.size.height;
        default: {
            log_error("get_cell_height: unknown cell type [%d]", param.cellType);
            return 0;
        }
    }
}


Row row_with_row_button_at_index(Row row, Button button, uint16_t index) {
    if(index >= row.length) {
        log_error("row_with_row_button_at_index: index [%d] out of bounds", index);
        return row;
    }
    row.cells[index] = button_row_cell(button);
    return update_row_rect(row);
}

RowCell button_row_cell(Button button) {
    return (RowCell) {
        .cellType = BUTTON,
        .cell = button,
    };
}

Row update_row_rect(Row row) {
    row.rect.w = 0;
    for(int i = 0; i < row.length; i++) {
        int cell_height = get_cell_height(row.cells[i]);
        if(cell_height > row.rect.h) row.rect.h = cell_height;
        row.rect.w += get_cell_width(row.cells[i]);
    }
    return row;
}

RowCell get_button_in_row_at_index(Row row, uint16_t index) {
    RowCell cell = row.cells[index];
    if(cell.cellType != BUTTON) {
        return (RowCell) {.cellType = NO_CELL};
    }
    return cell;
}


Row spacing_row(uint8_t spacing, Row row) {
    row.spacing = spacing;
    row.rect.w += (row.length - 1) * spacing;
    return row;
}

Row update_row_position_in_zone(Row row, SDL_Rect zone) {
    return position_row(row.position, row, zone);
}