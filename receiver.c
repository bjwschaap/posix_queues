#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "message.h"

key_t queue_key;
int queue_id;
int exit_code = 0;
message_t msg;

int main() {
    // Create a 'key' to identify a queue with. This must be the same key for all
    // communicating processes
    queue_key = ftok("/etc/passwd", 'X');
    // Open the queue using the key (create if not exists)
    queue_id = msgget(queue_key, 0600 | IPC_CREAT);

    while (true) {
        if (msgrcv(queue_id, &msg, sizeof(msg) - sizeof(long), 0, 0) < 0) {
            perror("msgrcv");
            exit_code = 1;
            break;
        }

        printf("%s\n", msg.text);
        sleep(10);
    }

    return exit_code;
}
