cmake_minimum_required(VERSION 3.15)
project(posix_queues C)

set(CMAKE_C_STANDARD 99)

add_executable(posix_queues_send sender.c message.h)
add_executable(posix_queues_recv receiver.c message.h)