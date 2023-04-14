FROM	debian:latest

RUN		apt update && apt install -y \
		vim \
		gcc \
		make

COPY	nm_src /tmp

CMD 	["/bin/sh"]
