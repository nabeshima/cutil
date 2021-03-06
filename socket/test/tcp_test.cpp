/**
 * $Id: tcp_test.cpp 3 2013-05-20 13:07:23Z cota@upard.org $
 * Copyright (c) 2016 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "Socket.h"
#include "Thread.h"

#include <vector>
#include <sstream>
#include <iostream>

using namespace std;
using namespace cutil;

void thread_func() {
  Socket socket_listen;
  socket_listen.open(IPv4, TCP);
  socket_listen.bind(15433);
  cout << "bound " << socket_listen.boundPort() << endl;
  Socket socket = socket_listen.accept();

  cout << "bound " << socket_listen.boundPort() << " " << socket.isOpen()
       << endl;

  int timeout_count = 0;
  while (true) {
    int64_t c;
    cout << "INQ 1 : " << socket.byteInRecvQueue() << endl;

    if (!socket.isReceivable(10000)) {
      cout << "sock: " << socket.isOpen() << ", not receivable. may timeout"
           << endl;
      sleep(1);
      continue;
    }
    if (socket.recv(&c, sizeof(c)) == 0) {
      cout << "connection is down (recv)" << endl;
      break;
    }
    timeout_count = 0;

    cout << "RECV: " << c << " from " << socket.fromAddress().toString()
         << endl;
    cout << "INQ 2 : " << socket.byteInRecvQueue() << endl;

    if (c == 1234567) {
      break;
    }
    sleep(1);
  }
}

int main(int argc, char **argv) {
  Thread thread;
  thread.start(thread_func);

  Socket socket;

  vector<Address> res;
  Address::resolve(&res, "127.0.0.1");
  Address peer;

  for (unsigned int i = 0; i < res.size(); ++i) {
    if (res[i].getFamily() == IPv4) {
      res[i].setPort(15433);
      peer = res[i];
    }
  }

  while (true) {
    bool ret = socket.open(peer.getFamily(), TCP);
    if (!ret) {
      cout << "socket open failure" << endl;
      sleep(1);
      continue;
    }
    ret = socket.connect(peer);
    if (!ret) {
      cout << "connection failure" << endl;
      sleep(1);
      continue;
    }
    if (ret) {
      cout << "connection success" << endl;
      break;
    }
  }

  usleep(1000000);

  int64_t l = 0;
  while (true) {
    l += 0x000000fa;
    cout << "SEND: " << l << endl;

    //     stringstream sstrm;
    //     sstrm << l;

    cout << "OUTQ 0 : " << socket.byteInSendQueue() << endl;
    //    if ( !socket.sendString( sstrm.str() ) ) {
    if (!socket.send(&l, sizeof(l))) {
      cout << "connection is down (send)" << endl;
      break;
    }
    cout << "OUTQ 1 : " << socket.byteInSendQueue() << endl;

    if (l > 1000) {
      l = 1234567;
      socket.send(&l, sizeof(l));
      break;
    }
    usleep(1000000);
  }

  thread.join();

  return 0;
}
