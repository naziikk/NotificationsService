FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libpqxx-dev \
    postgresql-client \
    libcurl4-openssl-dev \
    libssl-dev

WORKDIR /app
COPY . .

RUN mkdir build && cd build && cmake .. && make

CMD ["./build/NotificationsService"]