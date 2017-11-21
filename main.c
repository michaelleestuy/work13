#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
  int r = 0;
  int w = 1;

  int pipedown[2];
  int pipeup[2];

  pipe(pipedown);
  pipe(pipeup);


  if(!fork()){
    close(pipedown[w]);
    int f;
    read(pipedown[r], &f, sizeof(int));
    close(pipedown[r]);
    
    printf("Child received: %d\n Adding 1\n", f);
    f += 1;
    write(pipeup[w], &f, sizeof(f));
    close(pipeup[w]);
    close(pipeup[r]);
  }
  else{
    close(pipedown[r]);
    int f = 420;
    printf("Parent sends child: %d\n", f);
    write(pipedown[w], &f, sizeof(f));
    close(pipedown[w]);

    close(pipeup[w]);
    int status;
    wait(&status);
    int f2;
    read(pipeup[r], &f2, sizeof(int));
    printf("Parent received: %d\n", f2);
    close(pipeup[r]);
    

  }
  return 0;
}
