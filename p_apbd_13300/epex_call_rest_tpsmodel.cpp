/*************************************************
Copyright: Baosight Software LTD.co Copyright (c) 2023
Author:      195255
Version:     1.0
Date:        2023-02-16 15:19:48
Description: 调用TPS模型
**************************************************/

#include "stdafx.h"
#include "epex.h"
#include <cstdio>
BM2F_ENTERACE(epex_call_rest_tpsmodel)
int f_epex_call_rest_tpsmodel_lib(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn);

int f_epex_call_rest_tpsmodel(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
{
	CTracer log(__FUNCTION__);
	int doFlag = 0;
	CString sqlstr = " ";
	try
	{
		Log::Trace("", __FUNCTION__, "doFlag={0} ", doFlag);
		doFlag = f_epex_call_rest_tpsmodel_lib(bcls_rec, bcls_ret, conn);
		Log::Trace("", __FUNCTION__, "doFlag={0} ", doFlag);
		if (doFlag < 0)
		{
			throw CApplicationException(-1, s.msg, s.svc_name);
		}
	}
	catch (CDbException& ex)
	{
		CFormattable arguments[] = { ex.GetCode(), ex.GetMsg() };
		CMessageFormat::Format(s.msg, "Database Error,sqlcode=[{0}],sqlmsg=[{1}]", arguments, 2);
		CString str = sqlstr + "\r\n" + ex.GetMsg();
		strncpy(s.sysmsg, (const char*)str, sizeof(s.sysmsg) - 1);
		s.flag = -1;
		doFlag = -1;
	}
	catch (CApplicationException& ex)
	{
		s.flag = ex.GetCode();
		doFlag = -1;
	}
	catch (CException& ex)
	{
		strcpy(s.msg, ex.GetMsg());
		s.flag = ex.GetCode();
		doFlag = -1;
	}
	return doFlag;
}


