/// <summary>
/// 功能说明：太钢二炼钢工艺路径表新增
/// <version>1.0.0.0</para>
/// <creator>YZ</creator>
/// <history>2023/10/23文件创建</history>
/// </summary>
#include "stdafx.h"
#include "tapbd001s2n.h"

BM2F_ENTERACE(apbd001s2n_save);


int f_apbd001s2n_save(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
{
	/*打印程序起止LOG*/
	CTracer log(__FUNCTION__);


	/* 程序内部变量 */
	int doFlag = 0;		//返回值

	/*数据库SQL操作字符串，用于捕获数据库操作异常情况*/
	CString sqlstr = "";
	CString sqlwhere = "";

	/* 业务变量 */
	CString st_no = "";
	CString datetimeNow = CDateTime::Now().ToString("yyyyMMddHHmmss");

	//数据库变量
	CDbCommand cmd(conn);
	CTAPBD001S2N tapbd001s2n(conn);

	try
	{
		Log::Trace("", __FUNCTION__, "INSERT_BLOCK={0} ", bcls_rec->Tables["INSERT_BLOCK"].Rows.get_Count());
		Log::Trace("", __FUNCTION__, "UPDATE_BLOCK={0} ", bcls_rec->Tables["UPDATE_BLOCK"].Rows.get_Count());
		Log::Trace("", __FUNCTION__, "DELETE_BLOCK={0} ", bcls_rec->Tables["DELETE_BLOCK"].Rows.get_Count());
		if (bcls_rec->Tables["INSERT_BLOCK"].Rows.get_Count() > 0)
		{
			for (int i = 0; i < bcls_rec->Tables["INSERT_BLOCK"].Rows.get_Count(); i++)
			{
				tapbd001s2n.Reset();
				tapbd001s2n.MergeFrom(bcls_rec->Tables["INSERT_BLOCK"].Rows[i]);
				tapbd001s2n.REC_CREATE_TIME = datetimeNow;
				tapbd001s2n.REC_CREATOR = s.userid;
				tapbd001s2n.Insert();
			}
		}
		if (bcls_rec->Tables["UPDATE_BLOCK"].Rows.get_Count() > 0)
		{
			for (int i = 0; i < bcls_rec->Tables["UPDATE_BLOCK"].Rows.get_Count(); i++)
			{
				tapbd001s2n.Reset();
				tapbd001s2n.MergeFrom(bcls_rec->Tables["UPDATE_BLOCK"].Rows[i]);
				tapbd001s2n.REC_REVISE_TIME = datetimeNow;
				tapbd001s2n.REC_REVISOR = s.userid;
				tapbd001s2n.Update("REC_REVISE_TIME,REC_REVISOR,RULE_DESC,ROUTE_TYPE", "ST_NO");
			}
		}
		if (bcls_rec->Tables["DELETE_BLOCK"].Rows.get_Count() > 0)
		{
			for (int i = 0; i < bcls_rec->Tables["DELETE_BLOCK"].Rows.get_Count(); i++)
			{
				tapbd001s2n.Reset();
				tapbd001s2n.MergeFrom(bcls_rec->Tables["DELETE_BLOCK"].Rows[i]);
				tapbd001s2n.Delete("ST_NO");
			}
		}
	}
	/*捕获数据库操作异常*/
	catch (CDbException& ex)
	{
		CFormattable arguments[] = { ex.GetCode() };
		CMessageFormat::Format(s.msg, _RES("GCRSS0000006")/*数据库处理出错，sqlcode = [{0}]。请联系系统维护人员。*/, arguments, 1);
		CString str = ex.GetMsg() + "\r\n" + sqlstr;
		/*返回前台，与EI.EIInfo对象的sys_info.sysmsg参数对应*/
		strncpy(s.sysmsg, (const char *)str, sizeof(s.sysmsg) - 1);
		s.flag = -1;
		/*数据库异常时返回-1，事务将被回滚*/
		doFlag = -1;
	}
	/*捕获应用错误*/
	catch (CApplicationException& ex)
	{
		s.flag = ex.GetCode();
		doFlag = -1;
	}
	catch (CException& ex)
	{
		strncpy(s.msg, (const char *)ex.GetMsg(), sizeof(s.msg) - 1);
		s.flag = ex.GetCode();
		doFlag = -1;
	}

	s.flag = doFlag;
	return(doFlag);
}

