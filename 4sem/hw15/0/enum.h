#ifndef ENUM_H
#define ENUM_H

enum commandType { CMD_NONE, QUIT, STOP, SELECT, INSERT, DELETE};
enum conditionType { COND_NONE, EQ, NE, LT, GT, LE, GE, LIKE};
enum operationType {OP_NONE, AND, OR};
enum requestStatement {INCORRECT, CORRECT, REQ_NONE};

#endif // ENUM_H
