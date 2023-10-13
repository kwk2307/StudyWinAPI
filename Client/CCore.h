#pragma once

// �̱��� ����
// �ش� Ŭ������ ������� �� �ִ� ��ü�� ������ �Ѱ��� ����
// extern Ű���� -> ��𼭵� ������ �� ������ ������ ������ ���� ����. 

class CCore
{
	//���� �ɹ��Լ��� this �� ����.

	//���� ���� ����
	// 1. �Լ� �ȿ� : ������ ������ �����. �Լ��� ȣ��� ������� ������
	// 2. ���� �ȿ� : ������ ������ �����. �� ���� �ȿ����� ȣ�Ⱑ��. ���������� �ٸ����� ���Ͼȿ����� �̸��� �ٸ����
	// 3. Ŭ���� �ȿ� : ������ ������ �����. Ŭ������ ����ǰ� �����Ǵ� �Ͱ� ������� ������. ������ Ŭ���� ���ο����� ���� ������

// Ŭ������ �ּҸ� �����Ҵ��ؼ� ������ ������ �ִ� ���� �ɹ������� �����ϴ� ���
//private:
//	static CCore* g_pCore;
//public:
//	static CCore* GetInstance() {
//		 
//		// ���� ȣ�� ���� ���
//		if (g_pCore == nullptr) {
//
//			g_pCore = new CCore;
//		}
//		
//		// 2�� �̻� ȣ��� ��� 
//		return g_pCore;
//	}
//
//	static void Release(){
//		if (g_pCore != nullptr) {
//
//			delete g_pCore;
//			g_pCore = nullptr;
//		}
//	}


// ��ü ��ü�� ������ ������ �ö󰡴� ���
// �ּ� ���� ���� Ŭ���� ���ο� ���� ���� 
// ������ ������ �Ű���� �ʿ䰡 ���� ���α׷��� ����� �� ���� ����Ǳ� ����
//public:
	//static const CCore* GetInstance() {
	//	static CCore core;
	//	return &core;
	//}
	// 

	//����ϰ� ���̴� �ڵ尡 �����ϱ� ��ũ�η� �̸� �����صд�.
	SINGLE(CCore)

private:
	HWND m_hWnd;			//���� ������ �ڵ�
	POINT m_ptResolution;	//���� ������ �ػ�
	HDC m_hDC;				//Device Context �ڵ鷯

	HBITMAP m_bitmap;		//�̸� �׸� ��Ʈ��
	HDC m_memhDC;			//�� ��Ʈ���� Device Context 

public:
	int init(HWND _hWnd, POINT _ptResolution);
	HWND getHWND();
	void progress();

private:
	void update();
	void render();
};
