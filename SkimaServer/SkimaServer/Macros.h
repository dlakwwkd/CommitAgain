#pragma once
///////////////////////////////////////////////////////////////////////////
/*
    클라의 픽셀단위 좌표와 서버(Box2d)의 미터단위 좌표 간의 변환 매크로
*/
///////////////////////////////////////////////////////////////////////////
#define PTM_RATIO 32

template <typename T>   T Extend(T input){ return input * PTM_RATIO; }
template <typename T>   T Reduce(T input){ return input / PTM_RATIO; }

#define INCREASE(v) {Extend((v).x), Extend((v).y)}
#define DECREASE(v) {Reduce((v).x), Reduce((v).y)}

#define CONVERT_IN(v, roomID)   {Reduce((v).x), Reduce((v).y + static_cast<float>((roomID)*MAX_MAP_SIZE_Y))}
#define CONVERT_OUT(v, roomID)  {Extend((v).x), Extend((v).y) - static_cast<float>((roomID)*MAX_MAP_SIZE_Y)}


///////////////////////////////////////////////////////////////////////////
/*
    UnitID에서 타입 체크를 하기 위한 매크로
*/
///////////////////////////////////////////////////////////////////////////
#define MAIN_TYPE_BIT   0xF0000000
#define MAIN_TYPE_BIT_T 0x0FFFFFFF
#define SIDE_TYPE_BIT   0x0F000000
#define SIDE_TYPE_BIT_T 0xF0FFFFFF
#define MAX_ID_SIZE     0x00FFFFFF

#define SET_MAIN_TYPE(unitID, type) (((unitID) & MAIN_TYPE_BIT_T) + ((type) << 28))
#define SET_SIDE_TYPE(unitID, type) (((unitID) & SIDE_TYPE_BIT_T) + (((type) << 24) & MAIN_TYPE_BIT_T))
#define INIT_MAIN_TYPE(unitID)      ((unitID) & MAIN_TYPE_BIT_T)
#define INIT_SIDE_TYPE(unitID)      ((unitID) & SIDE_TYPE_BIT_T)
#define INIT_TYPE(unitID)           (((unitID) & MAIN_TYPE_BIT_T) & SIDE_TYPE_BIT_T)
#define GET_MAIN_TYPE(unitID)       (((unitID) & MAIN_TYPE_BIT) >> 28)
#define GET_SIDE_TYPE(unitID)       (((unitID) & SIDE_TYPE_BIT) >> 24)

template <typename T>
int MakeID(T)
{
    static int makeId = 0;
    if (++makeId > MAX_ID_SIZE)
        makeId = 1;
    
    return makeId;
}