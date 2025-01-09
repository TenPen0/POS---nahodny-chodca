cmake_minimum_required(VERSION 3.25)
project(POS C)

set(CMAKE_C_STANDARD 11)

add_executable(client
        shm/buffer.c
        shm/buffer.h
        shm/shm.c
        shm/shm.h
        shm/names.h
        shm/synBuffer.c
        shm/synBuffer.h
        client/client.c
        client/client.h
        shm/names.c
        server/simulation.c
        server/simulation.h
        client/drawThread.c
        client/drawThread.h
        client/inputThread.c
        client/inputThread.h
)

add_executable(server server/server.c
        server/server.h
        shm/buffer.c
        shm/buffer.h
        shm/shm.c
        shm/shm.h
        shm/names.h
        shm/synBuffer.c
        shm/synBuffer.h
        shm/names.c
        server/simulation.c
        server/simulation.h
        client/drawThread.h
        client/drawThread.c
        server/simThread.c
        server/simThread.h
)