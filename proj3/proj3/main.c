#include <stdio.h>
#include <stdlib.h>

int abs(int x){
    if(x > 0){
        return x;
    } else if(x < 0) {
        return x * -1;
    } else {
        return 0;
    }
}

void findShortestSequence(int floor, int start, int goal, int up, int down) {
    int flag = 0, arr[100], index = 0, max_steps = abs(start-goal), count = 0, i;
    while(1) {
        arr[index++] = start;
        if(start == goal){
            break;
        } else if(goal > start) {
            start += up;
        } else if(goal < start) {
            start -= down;
        }
        count++;

        if(count > max_steps){
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        printf("Use the stairs.\n");
    } else {
        arr[index++] = start;
        for(i = 0; i < count; i++){
            printf("%d->",arr[i]);
        }
        printf("%d\n",arr[i]);

    }
}

int main(){
    int f,s,g,u,d;
    scanf("%d %d %d %d %d",&f,&s,&g,&u,&d);

    findShortestSequence(f, s, g, u, d);

    return 0;
}
