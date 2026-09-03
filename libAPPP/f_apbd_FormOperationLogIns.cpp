/*************************************************
Copyright: Baosight Software LTD.co Copyright (c) 2023
Author:      195255
Version:     1.0
Date:        2023-02-16 11:13:11
Description: 画面操作日志添加
**************************************************/

#include "stdafx.h"
#include "tapbdl001.h"

BM2_FUNCTION_EXPORT


int f_apbd_FormOperationLogIns(CDbConnection * conn, CString function, CString desc = "", CString remark = "")
{
	CTracer log(__FUNCTION__);
	int doFlag = 0;
	CString sqlstr = " ";
	CString dateTime = CDateTime::Now().ToString("yyyyMMddHHmmss");
	try
	{
		// -----Begin IPLAT4C::IPLAT4CServiceCompositeStatementObj()----- //
		CTAPBDL001 tapbdl001(conn);

		tapbdl001.Reset();

		tapbdl001.REC_CREATOR = s.userid;
		tapbdl001.REC_CREATE_TIME = dateTime;
		tapbdl001.FORM_NO1 = s.formname;
		tapbdl001.FUNCTION = function;
		tapbdl001.OP_DESC = desc;
		tapbdl001.MAKER_REMARK = remark;

		if (tapbdl001.FORM_NO1.Trim() != "")
		{
			tapbdl001.Insert();
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


