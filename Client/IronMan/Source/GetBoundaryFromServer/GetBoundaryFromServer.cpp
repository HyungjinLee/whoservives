//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "GetBoundaryFromServer.h"
#include "KScOpenCvUtils.h"

// DLL�� ����� ���� �κ�
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

// �Լ��� ���� �κ�
int CDECL GetBoundaryFromServer(KScUserDefineArray* testImg,int* left,int* top,int* right,int* bottom)
{
// ��ó�� /////////////////////////////////////////////////////////////////////
	
	
	/*
	GPU ������ ���� ���ÿ��� YOLO�� ������ ��� �ʿ� ���� �Լ� - �����κ��� �Է� �̹������� ��ü�� ��ǥ���� �ҷ���

	OverView

	1. Ŭ���̾�Ʈ
	
	������ �����ؼ� darknet(yolo) ���� ��ɾ� 
	'./darknet detector test data/obj.data data/yolo-obj.cfg backup/yolo-obj_10000.weights data/testimg2.jpg'�� shell�� �Է��ϴ� php ���� ����
	�� �� testimg.jpg ������ ��� ������ �Ѱ�����...
	*/
	
	/*
	2. �����ܿ���
	darknet�� ����Ǿ� boundary�� ����� �Ŀ� �� ��ǥ�� position.html ���Ͽ� ����
	*/

	/*
	3. Ŭ���̾�Ʈ
	position.html ������ �ִ��� Ȯ���ϰ�, ������ �� ���� ��ǥ ���� �о left, top, right, bottom�� 4���� �Ķ���Ϳ� �Ѱ���
	*/

    // �Է� ���� �ڷ� ���� �˻�.

    // ��� ���� �ڷ� ���� �˻�.

    // �Է� ���� �Ҵ� ���� �˻�.

	// ��� ���� �Ҵ� ���� �˻�.

// ���� ó�� �κ� /////////////////////////////////////////////////////////////

	// Get the KScMatType pointer from mat1_uda
	KScMatType_cv* matPtr = NULL;
	matPtr = GetNewObjFromUDA(matPtr, testImg); // Convert UserDefinedType to Mat Type
	if (matPtr == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", " cvDisplayImg", MB_OK);
		return FALSE;
	}

	// �� ���� �Լ��� ���� ó�� �ڵ带 �����մϴ�.

// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


