#running the object files
rm -rf output_tput

mkdir output_tput
#./pipeipc > output/pipe_latency.txt
#./socketipc > output/socket_latency.txt
#./smemipc > output/smemipc_latency.txt
#./tsc_precision > output/tsc_precision_latency.txt


./pipeipc -t -s 4 > output/pipe_s4.txt
./socketipc -t -s 4 > output/socket_s4.txt
./smemipc -t -s 4 > output/smemipc_s4.txt
./pipeipc -t -s 16 > output/pipe_s16.txt
./socketipc -t -s 16 > output/socket_s16.txt
./smemipc -t -s 16 > output/smemipc_s16.txt
./pipeipc -t -s 64 > output/pipe_s64.txt
./socketipc -t -s 64 > output/socket_s64.txt
./smemipc -t -s 64 > output/smemipc_s64.txt
./pipeipc -t -s 256 > output/pipe_s256.txt
./socketipc -t -s 256 > output/socket_s256.txt
./smemipc -t -s 256 > output/smemipc_s256.txt
./pipeipc -t -s 1024 > output/pipe_s1024.txt
./socketipc -t -s 1024 > output/socket_s1024.txt
./smemipc -t -s 1024 > output/smemipc_s1024.txt
./pipeipc -t -s 4096 > output/pipe_s4096.txt
./socketipc -t -s 4096 > output/socket_s4096.txt
./smemipc -t -s 4096 > output/smemipc_s4096.txt
./pipeipc -t -s 16384 > output/pipe_s16k.txt
./socketipc -t -s 16384 > output/socket_s16k.txt
./smemipc -t -s 16384 > output/smemipc_s16k.txt
./pipeipc -t -s 65536 > output/pipe_s64k.txt
./socketipc -t -s 65536 > output/socket_s64k.txt
./smemipc -t -s 65536 > output/smemipc_s64k.txt
./pipeipc -t -s 262144 > output/pipe_s256k.txt
./socketipc -t -s 262144 > output/socket_s256k.txt
./smemipc -t -s 262144 > output/smemipc_s256k.txt
./pipeipc -t -s 524288 > output/pipe_s512k.txt
./socketipc -t -s 524288 > output/socket_s512k.txt
./smemipc -t -s 524288 > output/smemipc_s512k.txt
