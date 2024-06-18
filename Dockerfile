# Первый этап - сборка
FROM ubuntu:24.10 AS builder

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    git cmake \
    python3 python3-pip \
    clang build-essential \
    openssl libssl-dev

RUN pip3 install --break-system-packages conan

WORKDIR /app

RUN git clone --recursive https://github.com/6yntar05/turbowarp_cloud_cpp .

WORKDIR /app/build

RUN conan profile detect
RUN conan install .. -vvv --build=missing --settings=build_type=Debug --settings compiler.cppstd=20
RUN conan build .. -vvv --build=missing --settings=build_type=Debug --settings compiler.cppstd=20

# Второй этап - создание минимального образа для запуска
FROM ubuntu:24.10

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    libstdc++6 openssl libssl-dev \
    && apt-get clean

WORKDIR /app

COPY --from=builder /app/build/Debug/turbowarp_cloud_cpp /app/turbowarp_cloud_cpp
COPY generate_certs.sh /app/generate_certs.sh

RUN chmod +x /app/generate_certs.sh
RUN /app/generate_certs.sh
RUN chmod 644 /app/cert /app/privkey

ENTRYPOINT ["/app/turbowarp_cloud_cpp"]
