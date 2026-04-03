#pragma once

#include <common.h>
#include <field.h>
#include <symbols.h>

inline Common::GameModeReturnStruct makegameMode(int cols, int rows, int mines)
{
    Common::GameModeReturnStruct gm;
    gm.cols             = cols;
    gm.rows             = rows;
    gm.mines            = mines;
    gm.offsetX          = 4;
    gm.offsetY          = 4;
    gm.cellWidth        = 3;
    gm.difficultyString = "test";
    return gm;
}