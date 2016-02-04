#latency only

rm -rf output
mkdir output


./pipeipc -s 4 > output/pipe_s4.txt
./socketipc -s 4 > output/socket_s4.txt
./smemipc -s 4 > output/smemipc_s4.txt
./pipeipc -s 16 > output/pipe_s16.txt
./socketipc -s 16 > output/socket_s16.txt
./smemipc -s 16 > output/smemipc_s16.txt
./pipeipc -s 64 > output/pipe_s64.txt
./socketipc -s 64 > output/socket_s64.txt
./smemipc -s 64 > output/smemipc_s64.txt
./pipeipc -s 256 > output/pipe_s256.txt
./socketipc -s 256 > output/socket_s256.txt
./smemipc -s 256 > output/smemipc_s256.txt
./pipeipc -s 1024 > output/pipe_s1024.txt
./socketipc -s 1024 > output/socket_s1024.txt
./smemipc -s 1024 > output/smemipc_s1024.txt
./pipeipc -s 4096 > output/pipe_s4096.txt
./socketipc -s 4096 > output/socket_s4096.txt
./smemipc -s 4096 > output/smemipc_s4096.txt
./pipeipc -s 16384 > output/pipe_s16k.txt
./socketipc -s 16384 > output/socket_s16k.txt
./smemipc -s 16384 > output/smemipc_s16k.txt
./pipeipc -s 65536 > output/pipe_s64k.txt
./socketipc -s 65536 > output/socket_s64k.txt
./smemipc -s 65536 > output/smemipc_s64k.txt
./pipeipc -s 262144 > output/pipe_s256k.txt
./socketipc -s 262144 > output/socket_s256k.txt
./smemipc -s 262144 > output/smemipc_s256k.txt
./pipeipc -s 524288 > output/pipe_s512k.txt
./socketipc -s 524288 > output/socket_s512k.txt
./smemipc -s 524288 > output/smemipc_s512k.txt
