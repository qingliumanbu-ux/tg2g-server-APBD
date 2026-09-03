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

int f_epex_call_rest_tpsmodel_z_lib(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
{
	CTracer log(__FUNCTION__);
	int doFlag = 0;
	CString sqlstr = " ";
	CString flag = " ";
	CString model_style = " ";
	try
	{
		flag = bcls_rec->Tables["FLAG"].Rows[0]["FLAG"].ToString().Trim();
		model_style = bcls_rec->Tables["MODELSTYLE"].Rows[0]["MODEL_STYLE"].ToString().Trim();
		Log::Trace("", __FUNCTION__, "flag = {0} , model_style={1}", flag, model_style);
		// -----Begin IPLAT4C::IPLAT4CServiceCompositeStatementObj()----- //
		iPlat4C::CRestClient restClient(conn, "MZX_TEST");//EX04中配置的系统代码
		Log::Trace("", __FUNCTION__, "restClient finish");
		restClient.AddHttpHeader("Accept", "*");
		Log::Trace("", __FUNCTION__, "Accept finish");
		restClient.AddHttpHeader("Content-Type", "application/json;charset=UTF-8");
		Log::Trace("", __FUNCTION__, "Content-Type finish");

		if (flag == "1")
		{//get data
			restClient.Call("MZX_TEST", bcls_rec, bcls_ret);
			Log::Trace("", __FUNCTION__, "call finish MZX_TEST");
		}
		else
		{//run model
			restClient.Call("CP_MODEL_Z", bcls_rec, bcls_ret);
			Log::Trace("", __FUNCTION__, "call finish CP_MODEL_Z");
		}


		ei_sys the_s;
		bcls_ret->GetSYS(&the_s);
		Log::Trace("", __FUNCTION__, "GetSYS finish");
		if (the_s.flag < 0)
		{
			Log::Trace("", "", "--ei_outsys.msg: [{0}]", the_s.msg);
			throw CException(the_s.msg);
		}
		Log::Trace("", __FUNCTION__, "11111 = {0}");
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


