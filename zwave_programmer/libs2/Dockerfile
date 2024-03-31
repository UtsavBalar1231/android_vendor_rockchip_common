FROM ubuntu:20.04

ENV TZ=Europe/Copenhagen
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    cmake ninja-build cmake python gcovr build-essential doxygen graphviz zip \
    && rm -rf /var/lib/apt/lists/*
