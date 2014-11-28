// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <assert.h>
#include <limits.h>
#include <vector>
#include <map>
#include <algorithm>
#include <atomic>
#include <typeinfo>
#include <Box2D\Box2D.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#define PTM_RATIO 32

#define EXTEND(f) (f)*PTM_RATIO
#define REDUCE(f) (f)/PTM_RATIO

#define INCREASE(v) {EXTEND((v).x), EXTEND((v).y)}
#define DECREASE(v) {REDUCE((v).x), REDUCE((v).y)}
