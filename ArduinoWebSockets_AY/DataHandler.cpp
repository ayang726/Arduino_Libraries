#include "DataHandler.h"


 SocketData::SocketData(String event, int data) {
    this->event = event;
    this->data = data;
    String str(data);
    this->dataStr = str;
    this->parsedString = "42[\""+event+"\",\""+dataStr+"\"]";
  }
 SocketData::SocketData(int data) {
    this->event = "message";
    this->data = data;
    String str(data);
    this->dataStr = str;
    this->parsedString = "42[\""+event+"\",\""+dataStr+"\"]";
  }