rm -r dir 
rm -r dir1
rm -r dir2
rm -r dir3

mkdir -p ./dir
fallocate -l 3M ./dir/file2_3M
fallocate -l 5M ./dir/file3_5M
fallocate -l 5M ./dir/file1_5M

mkdir -p ./dir1
fallocate -l 3M ./dir1/file2_3M
fallocate -l 5M ./dir1/file3_5M
fallocate -l 5M ./dir1/file1_5M

mkdir -p ./dir2
fallocate -l 1M ./dir2/file1_1M
fallocate -l 6M ./dir2/file2_6M
fallocate -l 3M ./dir2/file3_3M

mkdir -p ./dir3
fallocate -l 6M ./dir3/file1_6M
fallocate -l 2M ./dir3/file2_2M