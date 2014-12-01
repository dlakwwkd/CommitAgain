#pragma once
///////////////////////////////////////////////////////////////////////////
/*
    Ŭ���� �ȼ����� ��ǥ�� ����(Box2d)�� ���ʹ��� ��ǥ ���� ��ȯ ��ũ��
*/
///////////////////////////////////////////////////////////////////////////
#define PTM_RATIO 32

#define EXTEND(f) (f)*PTM_RATIO
#define REDUCE(f) (f)/PTM_RATIO
#define INCREASE(v) {EXTEND((v).x), EXTEND((v).y)}
#define DECREASE(v) {REDUCE((v).x), REDUCE((v).y)}

#define CONVERT_IN(v, roomID)   {REDUCE((v).x), REDUCE((v).y + (roomID)*MAX_MAP_SIZE_Y)}
#define CONVERT_OUT(v, roomID)  {EXTEND((v).x), EXTEND((v).y) - (roomID)*MAX_MAP_SIZE_Y}

