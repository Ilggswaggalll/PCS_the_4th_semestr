FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Moscow

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    make \
    git \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    qt6-base-dev \
    qt6-base-dev-tools \
    libqt6core6 \
    libqt6widgets6 \
    && rm -rf /var/lib/apt/lists/*

# Catch2
RUN git clone --depth 1 --branch v3.5.2 https://github.com/catchorg/Catch2.git && \
    cd Catch2 && \
    cmake -B build -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build build --target install -j$(nproc) && \
    cd .. && \
    rm -rf Catch2

WORKDIR /app

COPY include/ ./include/
COPY src/ ./src/
COPY CMakeLists.txt .
COPY tests/ ./tests/

RUN mkdir -p build && cd build && \
    cmake .. -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release && \
    make -j$(nproc)


FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    libqt6core6 \
    libqt6widgets6 \
    && rm -rf /var/lib/apt/lists/*

# Копируем собранные бинарники
COPY --from=builder /app/build/search_engine /app/search_engine
COPY --from=builder /app/build/tests/ /app/tests/

RUN mkdir -p /app/test_docs
WORKDIR /app

COPY txt_files/ /app/test_docs/
