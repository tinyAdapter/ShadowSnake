#ifndef LOG_H
#define LOG_H

/*写入错误文档*/
bool LOG_WriteError(const char* log);
/*写入警告文档*/
bool LOG_WriteWarning(const char* log);
/*写入信息文档*/
bool LOG_WriteInfo(const char* log);

#endif

