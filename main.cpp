#include "CommonDef.h"
#include "ClientNet.h"

void main(int argv, char* argc[])
{
  if (argv < 3)
  {
    cout << "Usage: cfg_filename command [parameters]" << endl;
    system("pause");
    return;
  }
  string cfg_file(argc[1]);
  FILE* fp = fopen(cfg_file.c_str(), "r");
  
  string remote_ip = "127.0.0.1";
  string port = "20000";

  if (fp)
  {
    char buffer[1024];
    fgets(buffer, 1023, fp);
    remote_ip = buffer;
    fgets(buffer, 1023, fp);
    port = buffer;
  }
  string cmd = argc[2];
  string send_cmd="";
  if (cmd == "info")
  {
    send_cmd = "cmd=\"info\"";
  }
  else if (cmd == "task")
  {
    send_cmd = "cmd=\"task\"";
  }
  else if (cmd == "process")
  {
    send_cmd = "cmd=\"process\"";
  }
  else if (cmd == "computer")
  {
    send_cmd = "cmd=\"computer\"";
  }
  else if (cmd == "acctask")
  {
    string tid = argc[3];
    send_cmd = "cmd=\"acctask\":taskid=\"" + tid + "\"";
  }
  else if (cmd == "killtask")
  {
    string tid = argc[3];
    send_cmd = "cmd=\"killtask\":taskid=\"" + tid + "\"";
  }
  else if (cmd == "settask")
  {
    string tid = argc[3];
    string process = argc[4];
    send_cmd = "cmd=\"settask\":taskid=\"" + tid + "\":process=\"" + process + "\"";
  }
  else if (cmd == "removecomputer")
  {
    string ip = argc[3];
    send_cmd = "cmd=\"removecomputer\":ip=\"" + ip + "\"";
  }
  else if (cmd == "setcomputer")
  {
    string ip = argc[3];
    string cores = argc[4];
    send_cmd = "cmd=\"removecomputer\":ip=\"" + ip + "\":cores=\"" + cores + "\"";
  }
  else if (cmd == "lazysetcomputer")
  {
    string ip = argc[3];
    string cores = argc[4];
    send_cmd = "cmd=\"lazysetcomputer\":ip=\"" + ip + "\":cores=\"" + cores + "\"";
  }
  else if (cmd == "addtask")
  {
    // name owner cores dir callback_file
    string task_name = argc[3];
    string owner = argc[4];
    string cores = argc[5];
    string dir = argc[6];
    string callback = argc[7];
    send_cmd = "cmd=\"addtask\":taskname=\"" + task_name + "\":owner=\"" + owner + "\":cores=\"" + cores + "\":dir=\"" + dir + "\":callback=\"" + callback + "\"";
  }
  ClientNet client;
  client.Connect(remote_ip.c_str(), stoi(port));
  client.SendMsg(send_cmd);
  client.Close();
  if (cmd != "addtask")
  {
    system("pause");
  }
  return;
}
