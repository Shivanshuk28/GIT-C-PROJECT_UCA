gcc -c src/init_git.c -o output_files/init_git.o
gcc -c src/blob.c -o output_files/blob.o
gcc -c src/index.c -o output_files/index.o
gcc -c src/git_status.c -o output_files/git_status.o
gcc -c src/commit.c -o output_files/commit.o
gcc -o my_program main.c output_files/blob.o output_files/index.o output_files/git_status.o output_files/init_git.o output_files/commit.o -lssl -lcrypto

./my_program
