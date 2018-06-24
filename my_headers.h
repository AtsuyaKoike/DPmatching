#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <ppl.h>
#include <array>

#define		DIMENSION		200
#define		TXT_CAPACITY	256
#define		TOTAL_FRAME		200
#define		WORD_NUMBER		100
#define		T_RO_F			3

#define		FILEA			"city011\\city011_"
#define		FILEB			"city012\\city012_"
#define		FILEC			"city021\\city021_"
#define		FILED			"city022\\city022_"

#define		TXT_DATA_NAME_1		""

using namespace	std;
using namespace concurrency;

float Min(float x1, float x2, float x3); //3Ç¬ÇÃéÆÇÃílÇÃç≈è¨ílÇï‘Ç∑
void Metrizable_Calc(float *result, float *data1, float data2[100][15], size_t para_value);

