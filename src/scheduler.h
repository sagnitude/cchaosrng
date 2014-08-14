#ifndef scheduler__
#define scheduler__
#include "common.h"
#include <stdlib.h>
#include "cp.h"

#define INITIALQUEUESIZE 20

#define POOLTASK 1

struct Task{
  int type;//POOL/POINT
  int contentType;
};

struct TaskQueue{
  int offset;
  int size;
  ChaosPool* pool;
  Task* tasklist[1];
};

/*
 * Task Queue Maintainance
 */
private TaskQueue*
newTaskQueue(int length);

TaskQueue*
newTaskQueueWithPool(int length, ChaosPool* pool);

void
addTaskToQueue(Task* newTask, TaskQueue* taskQueue);

Task*
popTaskFromQueue(TaskQueue* taskQueue);

/*
 * Task Executer
 */
void
executeNextTask(ChaosPool* pool);

void
executePoolTask(Task* task, ChaosPool* pool);

#endif
