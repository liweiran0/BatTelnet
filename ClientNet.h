#pragma once
#include "CommonDef.h"
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

class ClientNet
{
public:
  //������ָ��������
  int Connect(const char* address, int port);
  //������Ϣ
  int SendMsg(string msg);
  //�ر�
  void Close();

private:
  SOCKET m_sock;
};