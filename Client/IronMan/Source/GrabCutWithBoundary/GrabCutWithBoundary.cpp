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
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "GrabCutWithBoundary.h"
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
int CDECL GrabCutWithBoundary(int* left,int* top,int* right,int* bottom,KScUserDefineArray* testImg,KScUserDefineArray* ResultImg)
{
// ��ó�� /////////////////////////////////////////////////////////////////////

    // �Է� ���� �ڷ� ���� �˻�.

    // ��� ���� �ڷ� ���� �˻�.

    // �Է� ���� �Ҵ� ���� �˻�.

	// ��� ���� �Ҵ� ���� �˻�.

// ���� ó�� �κ� /////////////////////////////////////////////////////////////
	
	KScMatType_cv* matPtr = NULL;
	matPtr = GetNewObjFromUDA(matPtr, testImg); // Convert UserDefinedType to Mat Type
	if (matPtr == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", " cvDisplayImg", MB_OK);
		return FALSE;
	}

	// �� ���� �Լ��� ���� ó�� �ڵ带 �����մϴ�.

	cv::Mat image = matPtr->image;
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

	// �Է� ���� ���� �κ� ����/��� ���̺��� �����ϴ� ���
	// ���� ��ü ���θ� �����ϴ� ���� ���簢���� ����
	
	cv::Size s = image.size();
	int rows = s.height;
	int cols = s.width;

	if ((*right < *left) || (*bottom < *top))
		return FALSE;

	if (*left < 0 || *top < 0 || *right > cols || *bottom > rows) // �ٿ������ ȭ�� ������ ��� ���
		return FALSE;

	cv::Rect rectangle(*left, *top, (*right-*left), (*bottom-*top) );
	// ��� ���簢�� ����
	// ���簢�� ���� ȭ�Ҵ� ������� ���̺�



   // �Է� ����� ��ü ���� ���� �ܿ� cv::grabCut �Լ��� ȣ���� ��
   // �� �˰��� ���� ���� ���� �����ϴ� �� ����� ���ǰ� �ʿ�
	cv::Mat result; // ���� (4�ڱ� ������ ��)
	cv::Mat bgModel, fgModel; // �� (�ʱ� ���)

	cv::grabCut(image,    // �Է� ����
		result,    // ���� ���
		rectangle,   // ������ �����ϴ� ���簢��
		bgModel, fgModel, // ��
		2,     // �ݺ� Ƚ��
		cv::GC_INIT_WITH_RECT); // ���簢�� ���

	   // cv::CC_INT_WITH_RECT �÷��׸� �̿��� ��� ���簢�� ��带 ����ϵ��� ����

	 // cv::GC_PR_FGD ���濡 ���� ���� �ִ� ȭ��(���簢�� ������ ȭ�� �ʱⰪ)
	 // cv::GC_PR_FGD�� ������ ���� ���� ȭ�Ҹ� ������ ������ ���� ������ ����
	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
	// ������ ���ɼ��� �ִ� ȭ�Ҹ� ��ũ�� ���� ��������
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	// ��� ���� ����
	image.copyTo(foreground, result);
	// ��� ȭ�Ҵ� ������� ����

	cv::namedWindow("Result");
	cv::imshow("Result", result);

	cv::namedWindow("Survival");
	cv::imshow("Foreground", foreground);

	KScMatType_cv* matoutPtr = NULL;
	matoutPtr = AttachNewObjToUDA(matoutPtr, ResultImg);  // define Mat for User define Array

	matoutPtr->image = foreground;	// ��� ������ output �Ķ���Ϳ� �־���

	cv::waitKey(0);


// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


