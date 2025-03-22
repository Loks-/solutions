#include "message.h"

#include "common/base.h"

#include <queue>

int NumberOfNodes() { return 1; }
int MyNodeId() { return 0; }

namespace {
static std::queue<long long> qp, qs, qr;
}

void PutChar([[maybe_unused]] int target, char value) {
  assert(target == 0);
  qp.push(value);
}

void PutInt([[maybe_unused]] int target, int value) {
  assert(target == 0);
  qp.push(value);
}

void PutLL([[maybe_unused]] int target, long long value) {
  assert(target == 0);
  qp.push(value);
}

void Send([[maybe_unused]] int target) {
  assert(target == 0);
  for (; !qp.empty(); qp.pop()) qs.push(qp.front());
}

int Receive([[maybe_unused]] int source) {
  assert((source == 0) || (source == -1));
  assert(!qs.empty());
  for (; !qs.empty(); qs.pop()) qr.push(qs.front());
  return 0;
}

char GetChar([[maybe_unused]] int source) {
  assert(source == 0);
  assert(!qr.empty());
  long long value = qr.front();
  qr.pop();
  return char(value);
}

int GetInt([[maybe_unused]] int source) {
  assert(source == 0);
  assert(!qr.empty());
  long long value = qr.front();
  qr.pop();
  return int(value);
}

long long GetLL([[maybe_unused]] int source) {
  assert(source == 0);
  assert(!qr.empty());
  long long value = qr.front();
  qr.pop();
  return value;
}
