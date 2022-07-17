#include <stdio.h>
#include "thread.h"

// 多线程可以正常打印
// warn:也不能100%保证必定是线程安全的顺序，在打印超长字符串的时候
void use_printf(const char *s) {
  printf("%s", s);
}

// 多线程之间的状态冲突 。。。
void use_putchar(const char *s) {
  for (; *s; s++) {
    putchar(*s);
  }
}

void (*print)(const char *) = use_printf;

void Tworker() {
  char buf[128];
  int c = gettid() % 4 + 1;
  sprintf(buf, "\033[3%dm%d\033[0m", c, c);
  while (1) {
    print(buf);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    print = use_putchar;
  }

  setbuf(stdout, NULL);
  for (int i = 0; i < 4; i++) {
    create(Tworker);//创建线程 
  }
}
