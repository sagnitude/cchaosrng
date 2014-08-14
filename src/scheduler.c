#include "scheduler.h"

/*
 * Task Queue Maintainance
 */
TaskQueue*
newTaskQueue(int length){
  return (TaskQueue*)malloc(sizeof(TaskQueue) + (length - 1) * sizeof(Task*));
}

TaskQueue*
newTaskQueueWithPool(int length, ChaosPool* pool){
  TaskQueue* temp =  newTaskQueue(length);
  temp -> offset = 0;
  temp -> size = length;
  temp -> pool = pool;
  return temp;
}

void
addTaskToQueue(Task* newTask, TaskQueue* taskQueue){
  if(taskQueue->size == taskQueue->offset){
    //expand queue
    TaskQueue* backup = taskQueue;
    taskQueue = realloc(taskQueue, taskQueue->size * 2);
    if(!taskQueue){
      taskQueue = backup;
      perror("Reallocating memory failed.\n");
      return;
    }
  }
  taskQueue -> size *= 2;
  taskQueue -> tasklist[taskQueue->offset++] = newTask;
}

Task*
popTaskFromQueue(TaskQueue* taskQueue){
  taskQueue -> offset --;
  return taskQueue -> tasklist[taskQueue->offset];
}

/*
 * Task Executer
 */
void
executeNextTask(ChaosPool* pool){
  Task* nextTask = popTaskFromQueue(pool -> taskQueue);

  switch(nextTask->type){
    case POOLTASK:
      executePoolTask(nextTask, pool);
      break;
    default:
      break;
  }
}

void
executePoolTask(Task* task, ChaosPool* pool){
  // switch(task->contentType){
  //
  // }
}
