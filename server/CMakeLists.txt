add_executable(server)
target_sources(server PRIVATE server.c simThread.c simulation.c simulationStructs.c
        ../shm/buffer.c ../shm/names.c ../shm/shm.c ../shm/synBuffer.c
        ../client/drawThread.c)