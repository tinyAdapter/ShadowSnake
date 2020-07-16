#ifndef RUNTIME_H
#define RUNTIME_H

//��ȡ��Ļ�ϵ��������ݣ�
void interceptScreenStrings();

//��ת��ĳһ״̬
void RT_JumpToState(int stateId);

//��ͣ��Ϸ
void RT_Pause(bool isDead, const char* prompt = "��ͣ");

//�ָ���Ϸ
void RT_Resume();

//�˳���Ϸ
void RT_Exit(int exitCode);

#endif
