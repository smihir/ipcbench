#latency only

rm -rf outputlatency
mkdir outputlatency


./pipeipc -s 4 > outputlatency/pipe_s4.txt
./socketipc -s 4 > outputlatency/socket_s4.txt
./smemipc -s 4 > outputlatency/smemipc_s4.txt
./pipeipc -s 16 > outputlatency/pipe_s16.txt
./socketipc -s 16 > outputlatency/socket_s16.txt
./smemipc -s 16 > outputlatency/smemipc_s16.txt
./pipeipc -s 64 > outputlatency/pipe_s64.txt
./socketipc -s 64 > outputlatency/socket_s64.txt
./smemipc -s 64 > outputlatency/smemipc_s64.txt
./pipeipc -s 256 > outputlatency/pipe_s256.txt
./socketipc -s 256 > outputlatency/socket_s256.txt
./smemipc -s 256 > outputlatency/smemipc_s256.txt
./pipeipc -s 1024 > outputlatency/pipe_s1024.txt
./socketipc -s 1024 > outputlatency/socket_s1024.txt
./smemipc -s 1024 > outputlatency/smemipc_s1024.txt
./pipeipc -s 4096 > outputlatency/pipe_s4096.txt
./socketipc -s 4096 > outputlatency/socket_s4096.txt
./smemipc -s 4096 > outputlatency/smemipc_s4096.txt
./pipeipc -s 16384 > outputlatency/pipe_s16k.txt
./socketipc -s 16384 > outputlatency/socket_s16k.txt
./smemipc -s 16384 > outputlatency/smemipc_s16k.txt
./pipeipc -s 65536 > outputlatency/pipe_s64k.txt
./socketipc -s 65536 > outputlatency/socket_s64k.txt
./smemipc -s 65536 > outputlatency/smemipc_s64k.txt
./pipeipc -s 262144 > outputlatency/pipe_s256k.txt
./socketipc -s 262144 > outputlatency/socket_s256k.txt
./smemipc -s 262144 > outputlatency/smemipc_s256k.txt
./pipeipc -s 524288 > outputlatency/pipe_s512k.txt
./socketipc -s 524288 > outputlatency/socket_s512k.txt
./smemipc -s 524288 > outputlatency/smemipc_s512k.txt
