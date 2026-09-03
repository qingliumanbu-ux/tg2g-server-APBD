/*************************************************
Copyright: Baosight Software LTD.co Copyright (c) 2023
Author:      YC2365
Version:     1.0
Date:        2023-10-26 17:40:51
Description: 工艺路径表
**************************************************/

#include "stdafx.h"

BM2F_ENTERACE(apbd001s2n_inq2)


int f_apbd001s2n_inq2(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
{
CTracer log(__FUNCTION__);
 int doFlag = 0;
 CString sqlstr = " ";
 try
 {
  // -----Begin IPLAT4C::IPLAT4CServiceCompositeStatementObj()----- //
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


