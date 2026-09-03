/*************************************************
Copyright: Baosight Software LTD.co Copyright (c) 2023
Author:      gjf
Version:     1.0
Date:        2023-02-16 11:00:21
Description: 记录画面操作日志
**************************************************/

#include "stdafx.h"

BM2F_ENTERACE(apbdl001_record)
int f_apbd_FormOperationLogIns(CDbConnection * conn, CString function, CString desc = "", CString remark = "");

int f_apbdl001_record(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
{
	CTracer log(__FUNCTION__);

	/* 程序内部变量 */
	int doFlag = 0;		//返回值
	/* 业务变量 */
	EIClass bcls_sub_in;	 //调用函数的参数块
	//EIClass bcls_sub_out;	 //调组函数的返回块	
	int funcFlag = 0;
	int fetchRowStart = 0; //查询到的记录行号

	//查询参数	
	CString function = "";//功能
	CString desc = "";//描述
	CString remark = "";//说明


	CString sqlstr = "";		//数据库SQL操作字符串
	CString sql_where = "";
	try
	{
		// -----Begin IPLAT4C::IPLAT4CServiceCompositeStatementObj()----- //
		//======================================================================
		//1.0 获取前台输入数据
		//======================================================================
		if (bcls_rec->Tables["RECORD"].Columns.Contains("FUNCTION"))
		{
			function = ((CString)bcls_rec->Tables["RECORD"].Rows[0]["FUNCTION"]).Trim();
		}

		if (bcls_rec->Tables["RECORD"].Columns.Contains("DESC"))
		{
			desc = ((CString)bcls_rec->Tables["RECORD"].Rows[0]["DESC"]).Trim();
		}
		if (bcls_rec->Tables["RECORD"].Columns.Contains("REMARK"))
		{
			remark = ((CString)bcls_rec->Tables["RECORD"].Rows[0]["REMARK"]).Trim();
		}

		Log::Trace("", __FUNCTION__, "---传入参数:function=[{0}]", function);
		Log::Trace("", __FUNCTION__, "---传入参数:desc=[{0}]", desc);
		Log::Trace("", __FUNCTION__, "---传入参数:remark=[{0}]", remark);


		///---------------------------------------------
		/// 2.1  调函数：处理 宝钢大院_热区 年计划信息插入相应表中
		///---------------------------------------------
		funcFlag = f_apbd_FormOperationLogIns(conn, function, desc, remark);

		Log::Trace("", __FUNCTION__, "--2.1----end函数-- f_apbd_FormOperationLogIns funcFlag=[{0}] ", funcFlag);


		if (funcFlag != 0)
		{
			strcpy(s.msg, CString::Format(" 调函数失败:%s ", (const char*)s.msg));
			strcpy(s.sysmsg, CString::Format("调函数失败: %s", (const char*)s.sysmsg));
			// 抛出应用异常
			throw CApplicationException(-1, s.msg, log.Location);
		}



		Log::Trace("", __FUNCTION__, "---999999---all--end--- 处理成功--   ");
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


