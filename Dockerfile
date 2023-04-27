FROM	debian:latest

ARG		NM_DIR="/nm_dir"

RUN		apt update && apt install -y \
		vim \
		gcc \
		file \
		libc6-dev-i386 \
		make

RUN		mkdir -p ${NM_DIR} && \
		mkdir -p ${NM_DIR}/src && \
		mkdir -p ${NM_DIR}/parse_files && \
		mkdir -p ${NM_DIR}/libft && \
		mkdir -p ${NM_DIR}/includes && \
		mkdir -p ${NM_DIR}/review_files

COPY	Makefile		${NM_DIR}
COPY	src/			${NM_DIR}/src/
COPY	parse_files/	${NM_DIR}/parse_files/
COPY	libft/			${NM_DIR}/libft/
COPY	includes/		${NM_DIR}/includes/
COPY	review_files/	${NM_DIR}/review_files/
COPY	diff.sh			${NM_DIR}

RUN		chmod +x ${NM_DIR}/diff.sh

CMD 	["/bin/sh"]
