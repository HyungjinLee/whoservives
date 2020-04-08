//////////////////////////////////////////////////////////////////////////
//
// 이 화일은 함수 등록시 자동으로 생성된 프로젝트입니다.
//
// 사용자가 임으로 만든 경우, Project의 Setting...의 설정이 필요하므로,
//
// 이는 도움말의 '함수 작성법'을 참조 바랍니다.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "GrabCutWithBoundary.h"
#include "KScOpenCvUtils.h"

// DLL을 만들기 위한 부분
BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: break;
		case DLL_THREAD_ATTACH:  break;
		case DLL_THREAD_DETACH:  break;
		case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}

// 함수의 정의 부분
int CDECL GrabCutWithBoundary(int* left,int* top,int* right,int* bottom,KScUserDefineArray* testImg,KScUserDefineArray* ResultImg)
{
// 전처리 /////////////////////////////////////////////////////////////////////

    // 입력 버퍼 자료 형태 검사.

    // 출력 버퍼 자료 형태 검사.

    // 입력 버퍼 할당 여부 검사.

	// 출력 버퍼 할당 여부 검사.

// 실제 처리 부분 /////////////////////////////////////////////////////////////
	
	KScMatType_cv* matPtr = NULL;
	matPtr = GetNewObjFromUDA(matPtr, testImg); // Convert UserDefinedType to Mat Type
	if (matPtr == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", " cvDisplayImg", MB_OK);
		return FALSE;
	}

	// 이 곳에 함수의 실제 처리 코드를 삽입합니다.

	cv::Mat image = matPtr->image;
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

	// 입력 영상에 대한 부분 전경/배경 레이블을 지정하는 방법
	// 전경 객체 내부를 포함하는 내부 직사각형을 정의
	
	cv::Size s = image.size();
	int rows = s.height;
	int cols = s.width;

	if ((*right < *left) || (*bottom < *top))
		return FALSE;

	if (*left < 0 || *top < 0 || *right > cols || *bottom > rows) // 바운더리가 화면 범위를 벗어난 경우
		return FALSE;

	cv::Rect rectangle(*left, *top, (*right-*left), (*bottom-*top) );
	// 경계 직사각형 정의
	// 직사각형 밖의 화소는 배경으로 레이블링



   // 입력 영상과 자체 분할 영상 외에 cv::grabCut 함수를 호출할 때
   // 이 알고리즘에 의해 만든 모델을 포함하는 두 행렬의 정의가 필요
	cv::Mat result; // 분할 (4자기 가능한 값)
	cv::Mat bgModel, fgModel; // 모델 (초기 사용)

	cv::grabCut(image,    // 입력 영상
		result,    // 분할 결과
		rectangle,   // 전경을 포함하는 직사각형
		bgModel, fgModel, // 모델
		2,     // 반복 횟수
		cv::GC_INIT_WITH_RECT); // 직사각형 사용

	   // cv::CC_INT_WITH_RECT 플래그를 이용한 경계 직사각형 모드를 사용하도록 지정

	 // cv::GC_PR_FGD 전경에 속할 수도 있는 화소(직사각형 내부의 화소 초기값)
	 // cv::GC_PR_FGD와 동일한 값을 갖는 화소를 추출해 분할한 이진 영상을 얻음
	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
	// 전경일 가능성이 있는 화소를 마크한 것을 가져오기
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	// 결과 영상 생성
	image.copyTo(foreground, result);
	// 배경 화소는 복사되지 않음

	cv::namedWindow("Result");
	cv::imshow("Result", result);

	cv::namedWindow("Survival");
	cv::imshow("Foreground", foreground);

	KScMatType_cv* matoutPtr = NULL;
	matoutPtr = AttachNewObjToUDA(matoutPtr, ResultImg);  // define Mat for User define Array

	matoutPtr->image = foreground;	// 결과 사진을 output 파라미터에 넣어줌

	cv::waitKey(0);


// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


