add_executable(client)
target_sources(client PRIVATE client.c drawThread.c inputThread.c menu.c
        ../shm/buffer.c ../shm/names.c ../shm/shm.c ../shm/synBuffer.c
        ../server/simulationStructs.c)