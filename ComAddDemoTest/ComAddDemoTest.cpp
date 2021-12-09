// ComAddDemoTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#import "E:\\code\\comWrapper\\ComAddDemo\\x64\\Debug\\ComAddDemo.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
//
// #define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
//         EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
// MIDL_DEFINE_GUID(IID, IID_IISimAddObj, 0x9C3D29CF, 0x6F29, 0x4D8D, 0xA3, 0xE5, 0x8F, 0x45, 0x35, 0x7B, 0x54, 0x72);
struct buftest
{
	int a;
	int b;
	char buf[20];
};

int _tmain(int argc, _TCHAR* argv[])
{
	 
	long num1 = 10;
	long num2 = 20;
	long sum = 0;
	 
	printf("sizeof(long)=%d\nsizeof(int)=%d\nsizeof(char*)=%d\nsizeof(int*)=%d\n",
		sizeof(long), sizeof(int), sizeof(char*), sizeof(int*));
	//system("pause");
	CoInitialize(NULL);
	CLSID clsid;
	IISimAddObj* pProxy;
	HRESULT hr = CLSIDFromProgID(OLESTR("ComAddDemo.SimAddObj"), &clsid);//这里的字符串一定要和注册表中的ProgID一致!!!   
	hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IISimAddObj, (void **)&pProxy); //创建COM对象
	buftest t={0};
	t.a = 10;
	t.b = 11;
	strcpy(t.buf, "wocao");
	buftest* pt = &t;

	long* ptl = (long*)pt;

	long* pl = &sum;
	
	//{
	//	HBITMAP  hbi;
	//	BITMAP bm;
	//	GetObject(hbi, sizeof(bm), &bm);
	//	BITMAPINFOHEADER bi = { sizeof(bi) };
	//	bi.biWidth = bm.bmWidth;
	//	bi.biHeight = bm.bmHeight;
	//	bi.biBitCount = bm.bmBitsPixel;
	//	bi.biPlanes = bm.bmPlanes;
	//	bi.biSizeImage = bm.bmWidthBytes * bm.bmHeight;

	//	int dib_size = sizeof(bi) + bi.biSizeImage;
	//	BYTE* dib = new BYTE[dib_size];
	//	memcpy(dib, &bi, sizeof(bi));
	//	memcpy(dib + sizeof(bi), bm.bmBits, bi.biSizeImage);
	//	//send_function(dib, dib_size);
	//}
	//BITMAPINFOHEADER* bi = (BITMAPINFOHEADER*)dib;
	//BYTE* bits = dib + sizeof(bi);
	//HBITMAP hbitmap = CreateBitmap(bi->biWidth, bi->biHeight, bi->biPlanes, bi->biBitCount, bits);
	{
		{
			VARIANT* buffer = new VARIANT;

			
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
				BYTE *buf ;

				SafeArrayAccessData(psa, (void**)&buf); //安全指针
				int len = 2;
				for (int i = 0; i < len; i++) 	//直接修改缓冲区 <= "" p = "" >
				{
					buf[i] = (i + 2) % 256;
					 
				}
				
				SafeArrayUnaccessData(psa);
			 
			V_VT(buffer) = VT_ARRAY | VT_UI1;
			V_ARRAY(buffer) = psa;
			BSTR str;
			char buf1[234] = "jwq test";
			CComBSTR comBSTR = buf1;
			str = ::SysAllocString(comBSTR);
			pProxy->strTest(str);
			pProxy->buftest2(buffer);  //成功
			pProxy->TestVar(*buffer); //调用COM接口
			getchar();
		}
	
		/*VARIANT buffer;
		 
		long dim = SafeArrayGetDim(buffer.parray);
		long ubound;
		long lbound;

		SafeArrayGetUBound(buffer.parray, dim, &ubound);
		SafeArrayGetLBound(buffer.parray, dim, &lbound);
		BSTR* buf;
		BSTR  pd[2];
		SafeArrayAccessData(buffer.parray, (void**)&buf);
		for (int i = lbound; i < ubound; i++)
			pd[i] = buf[i];

		pProxy->TestVar(buffer);*/
	}
	
	printf("%d + %d = %d", num1, num2, sum);

	if (pProxy)
	{
		pProxy->Release();
	}
	pProxy = NULL;	

	hr = CLSIDFromProgID(OLESTR("ComAddDemo.SimAddObj"), &clsid);//这里的字符串一定要和注册表中的ProgID一致!!!   
	hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IISimAddObj, (void **)&pProxy); //创建COM对象
	pProxy->Add(num1, num2, &sum); //调用COM接口
	printf("%d + %d = %d", num1, num2, sum);


	num1 = 40;
	num2 = 40;
	pProxy->Add(num1, num2, &sum); //调用COM接口
	printf("%d + %d = %d", num1, num2, sum);

	if (pProxy)
	{
		pProxy->Release();
	}
	pProxy = NULL;	

	CoUninitialize();

	
	return 0;
}

