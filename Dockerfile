FROM debian:stretch

RUN apt-get update \
 && apt-get install -y -q \
    curl \
    golang \
    make \
    openssl \
    python3

RUN useradd -m docker
USER docker
WORKDIR /home/docker

RUN curl https://sh.rustup.rs -sSf | sh -s -- -y

ENV PATH=$PATH:/home/docker/.cargo/bin
RUN cargo install mdbook
