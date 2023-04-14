yes | docker system prune
docker build -t wwp:0.1 .
docker run --name nm_container -it wwp:0.1 /bin/bash
