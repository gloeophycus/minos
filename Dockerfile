FROM i386/debian:buster

RUN apt-get update && apt-get install -y build-essential ruby && rm -rf /var/lib/apt/lists/*
WORKDIR /src
CMD ["bash"]
