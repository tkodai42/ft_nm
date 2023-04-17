FROM	debian:latest

ARG		NM_DIR="/nm_dir"

RUN		apt update && apt install -y \
		vim \
		gcc \
		make

RUN		mkdir -p ${NM_DIR} && \
		mkdir -p ${NM_DIR}/src && \
		mkdir -p ${NM_DIR}/parse_files && \
		mkdir -p ${NM_DIR}/libft && \
		mkdir -p ${NM_DIR}/includes

COPY	Makefile		${NM_DIR}
COPY	src/			${NM_DIR}/src/
COPY	test_files/		${NM_DIR}/test_files/
COPY	parse_files/	${NM_DIR}/parse_files/
COPY	libft/			${NM_DIR}/libft/
COPY	includes/		${NM_DIR}/includes/

CMD 	["/bin/sh"]
