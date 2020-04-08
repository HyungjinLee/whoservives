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
#include "GetBoundaryFromServer.h"
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
int CDECL GetBoundaryFromServer(KScUserDefineArray* testImg,int* left,int* top,int* right,int* bottom)
{
// 전처리 /////////////////////////////////////////////////////////////////////
	
	
	/*
	GPU 서버가 없이 로컬에서 YOLO를 구동한 경우 필요 없는 함수 - 서버로부터 입력 이미지에서 객체의 좌표들을 불러옴

	OverView

	1. 클라이언트
	
	서버에 접속해서 darknet(yolo) 실행 명령어 
	'./darknet detector test data/obj.data data/yolo-obj.cfg backup/yolo-obj_10000.weights data/testimg2.jpg'를 shell에 입력하는 php 파일 실행
	이 때 testimg.jpg 파일을 어떻게 서버로 넘겨줄지...
	*/
	
	/*
	2. 서버단에서
	darknet이 실행되어 boundary가 검출된 후에 그 좌표를 position.html 파일에 저장
	*/

	/*
	3. 클라이언트
	position.html 파일이 있는지 확인하고, 있으면 그 안의 좌표 값을 읽어서 left, top, right, bottom의 4가지 파라미터에 넘겨줌
	*/

    // 입력 버퍼 자료 형태 검사.

    // 출력 버퍼 자료 형태 검사.

    // 입력 버퍼 할당 여부 검사.

	// 출력 버퍼 할당 여부 검사.

// 실제 처리 부분 /////////////////////////////////////////////////////////////

	// Get the KScMatType pointer from mat1_uda
	KScMatType_cv* matPtr = NULL;
	matPtr = GetNewObjFromUDA(matPtr, testImg); // Convert UserDefinedType to Mat Type
	if (matPtr == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", " cvDisplayImg", MB_OK);
		return FALSE;
	}

	// 이 곳에 함수의 실제 처리 코드를 삽입합니다.

// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


