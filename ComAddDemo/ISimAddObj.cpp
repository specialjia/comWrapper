// ISimAddObj.cpp : Implementation of CISimAddObj

#include "stdafx.h"
#include "ISimAddObj.h"

#include <string>

#include "AddExport.h"
#include "comutil.h"
#pragma comment(lib,"Add.lib")

// CISimAddObj

struct buftest
{
	int a;
	int b;
	char buf[20];
};

STDMETHODIMP CISimAddObj::Add(LONG num1, LONG num2, LONG* sum)
{
	getchar();
	// buftest* pt = (buftest*)sum;
	// pt->a = num1;
	//
	// pt->b= num2;
	// strcpy(pt->buf, "add123456789");
	// *sum = AddMethod(num1, num2);

	return S_OK;
}


STDMETHODIMP CISimAddObj::Test(void)
{

	return S_OK;
}


STDMETHODIMP CISimAddObj::TestVar(VARIANT va)
{
	// VariantInit(&va);
	//
	// VariantClear(&va);
	SAFEARRAY* psa = va.parray;
	BYTE* buf;

	SafeArrayAccessData(psa, (void**)&buf); //安全指针
	int len = 2;
	for (int i = 0; i < len; i++) 	//直接修改缓冲区 <= "" p = "" >
	{
		buf[i] = 8;

	}

	SafeArrayUnaccessData(psa);

	return S_OK;
}


STDMETHODIMP CISimAddObj::bufTest(VARIANT buf)
{
	// TODO: 在此处添加实现代码

	return S_OK;
}


STDMETHODIMP CISimAddObj::buftest2(VARIANT* var)
{
	
	SAFEARRAY FAR* psa;
	SAFEARRAYBOUND* rgsabound = new SAFEARRAYBOUND[2];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = 2; //设置数组大小
	psa = SafeArrayCreate(VT_UI1, 1, rgsabound);  //创建数组

	{
		//读取
		//BYTE* buf;

		//SafeArrayAccessData(psa, (void**)&buf); //安全指针
		//SafeArrayUnaccessData(psa); //关闭后仍然可读取数据，但不能写入
	}


	//写入
	BYTE* buf;

	SafeArrayAccessData(psa, (void**)&buf); //安全指针
	int len = 2;
	for (int i = 0; i < len; i++) 	//直接修改缓冲区 <= "" p = "" >
	{
		buf[i] = 8;

	}

	SafeArrayUnaccessData(psa);

	V_VT(var) = VT_ARRAY | VT_UI1;
	V_ARRAY(var) = psa;

	return S_OK;
}


STDMETHODIMP CISimAddObj::strTest(BSTR str)
{
	// TODO: 在此处添加实现代码
	 
	std::wstring str1 = str;
	CComBSTR comBSTR = str;
	 
	char* lpszText2 = _com_util::ConvertBSTRToString(bstrText);

	return S_OK;
}
