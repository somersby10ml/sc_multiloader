#pragma once
#include <Windows.h>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

/// <summary>
/// 현재시가가져오기
/// </summary>
/// <returns></returns>
std::string GetTime();

/// <summary>
/// 에러메세지
/// </summary>
/// <param name="dwErrorNumber">에러번호</param>
void ErrorMessage(DWORD dwErrorNumber);

/// <summary>
/// 관리자권한 확인
/// </summary>
/// <returns></returns>
BOOL IsElevated();
