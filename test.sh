#!/bin/bash

fileary=()
fileary+=("review_files/easy_test_32")
fileary+=("review_files/easy_test_64")
fileary+=("review_files/not_so_easy_test_32")
fileary+=("review_files/not_so_easy_test_64")
fileary+=("review_files/error_header")
fileary+=("review_files/header")
fileary+=("review_files/header_and_prog")
fileary+=("review_files/header_and_prog_copy")
fileary+=("review_files/header_copy")
fileary+=("review_files/header_offset_error")
fileary+=("review_files/unterminated_string")
fileary+=("review_files/wrong_arch")

fileary+=("/usr/lib/gcc/x86_64-linux-gnu/10/crtend.o")
fileary+=("/usr/lib/gcc/x86_64-linux-gnu/10/libasan.so")
fileary+=("/usr/lib/gcc/x86_64-linux-gnu/10/libtsan.so")
fileary+=("/usr/lib/gcc/x86_64-linux-gnu/10/libubsan.so")
fileary+=("/usr/lib/gcc/x86_64-linux-gnu/10/libitm.so")
FILE_NAME=a.out

main() {
	for i in ${fileary[@]}; do
 	 	echo "==== FILE [$i] ===="
		FILE_NAME=$i
		check_diff
		echo
	done
}

check_diff() {
	./ft_nm	$FILE_NAME > txt2
	nm		$FILE_NAME > txt1

	diff txt1 txt2
}

main 
