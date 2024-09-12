FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libpqxx-dev \
    libhttplib-dev \
    postgresql-client

WORKDIR /app
COPY . .

RUN mkdir build && cd build && cmake .. && make

CMD ["./build/NotificationsService"]