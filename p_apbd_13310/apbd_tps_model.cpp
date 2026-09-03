/*************************************************
Copyright: Baosight Software LTD.co Copyright (c) 2024
Author:      195255
Version:     1.0
Date:        2024-05-22 09:47:35
Description: tps模型远程调用
**************************************************/

#include "stdafx.h"
#include "epex.h"
#include <cstdio>

BM2F_ENTERACE(apbd_tps_model)


int f_apbd_tps_model(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
{
	CTracer log(__FUNCTION__);
	int doFlag = 0;
	CString sqlstr = " ";
	try
	{
		// -----Begin IPLAT4C::IPLAT4CServiceCompositeStatementObj()----- //
		//调用远程服务器上的模型
		iPlat4C::CRestClient restClient(conn, "RUN_TPSMODEL");//EX04中配置的系统代码
		Log::Trace("", __FUNCTION__, "restClient finish");
		restClient.AddHttpHeader("Accept", "*");
		Log::Trace("", __FUNCTION__, "Accept finish");
		restClient.AddHttpHeader("Content-Type", "application/json;charset=UTF-8");
		Log::Trace("", __FUNCTION__, "Content-Type finish");
		restClient.Call("RUN_TPSMODEL", bcls_rec, bcls_ret);
		Log::Trace("", __FUNCTION__, "call finish");

		ei_sys the_s;
		bcls_ret->GetSYS(&the_s);
		Log::Trace("", __FUNCTION__, "GetSYS finish");
		if (the_s.flag < 0)
		{
			Log::Trace("", "", "--ei_outsys.msg: [{0}]", the_s.msg);
			throw CException(the_s.msg);
		}

		// -----End IPLAT4C::IPLAT4CServiceCompositeStatementObj()----- //
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


