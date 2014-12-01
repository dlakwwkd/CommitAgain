#pragma once
///////////////////////////////////////////////////////////////////////////
/*
    UnitID에서 타입 체크를 하기 위한 매크로
*/
///////////////////////////////////////////////////////////////////////////
#define MAIN_TYPE_BIT   0xF0000000
#define MAIN_TYPE_BIT_T 0x0FFFFFFF
#define SIDE_TYPE_BIT   0x0F000000
#define SIDE_TYPE_BIT_T 0xF0FFFFFF

#define SET_MAIN_TYPE(unitID, type) (((unitID) & MAIN_TYPE_BIT_T) + ((type) << 28))
#define SET_SIDE_TYPE(unitID, type) (((unitID) & SIDE_TYPE_BIT_T) + (((type) << 24) & MAIN_TYPE_BIT_T))
#define INIT_MAIN_TYPE(unitID)      ((unitID) & MAIN_TYPE_BIT_T)
#define INIT_SIDE_TYPE(unitID)      ((unitID) & SIDE_TYPE_BIT_T)
#define GET_MAIN_TYPE(unitID)       (((unitID) & MAIN_TYPE_BIT) >> 28)
#define GET_SIDE_TYPE(unitID)       (((unitID) & SIDE_TYPE_BIT) >> 24)
