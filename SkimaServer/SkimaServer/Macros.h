#pragma once
///////////////////////////////////////////////////////////////////////////
/*
    클라의 픽셀단위 좌표와 서버(Box2d)의 미터단위 좌표 간의 변환 매크로
*/
///////////////////////////////////////////////////////////////////////////
#define PTM_RATIO 32

#define EXTEND(f) (f)*PTM_RATIO
#define REDUCE(f) (f)/PTM_RATIO
#define INCREASE(v) {EXTEND((v).x), EXTEND((v).y)}
#define DECREASE(v) {REDUCE((v).x), REDUCE((v).y)}

#define CONVERT_IN(v, roomID)   {REDUCE((v).x), REDUCE((v).y + (roomID)*MAX_MAP_SIZE_Y)}
#define CONVERT_OUT(v, roomID)  {EXTEND((v).x), EXTEND((v).y) - (roomID)*MAX_MAP_SIZE_Y}

