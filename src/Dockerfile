FROM ubuntu:22.04
#FROM public.ecr.aws/lts/ubuntu:22.04
RUN apt-get update && apt-get -y install \
  make \
  gcc \
  valgrind \
  clang-format-13 \
  cppcheck
RUN mkdir /project
COPY . /project
WORKDIR /project/src
CMD [ "/bin/bash" ]
