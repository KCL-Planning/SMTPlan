# The recipe below implements a Docker multi-stage build:
# <https://docs.docker.com/develop/develop-images/multistage-build/>
###############################################################################
## First stage: an image to build the planner.
##
## We'll install here all packages we need to build the planner
###############################################################################
FROM ubuntu:16.04 AS builder
RUN apt-get update && apt-get install --no-install-recommends -y \
    git ca-certificates g++ make flex bison cmake doxygen libbz2-dev libgsl-dev libz-dev libboost1.58-all-dev libgmp3-dev libmpfr-dev m4 zlib1g-dev p7zip

RUN git clone https://github.com/Z3Prover/z3.git /z3 \
 && cd /z3 \
 && git checkout tags/z3-4.8.8 \
 && mkdir build \
 && cd build \
 && cmake -G "Unix Makefiles" -DZ3_BUILD_LIBZ3_SHARED=FALSE ../ \
 && make -j4 \
 && make install

RUN git clone https://github.com/bluescarni/mppp.git /mppp \
 && cd /mppp \
 && git checkout tags/v0.9 \
 && cmake -DMPPP_BUILD_STATIC_LIBRARY=ON . \
 && make \
 && make install

RUN git clone https://github.com/bluescarni/piranha.git /piranha \
 && cd /piranha \
 && git checkout 7e42042 \
 && mkdir build \
 && cd build \
 && cmake ../ \
 && make install

# RUN git clone https://github.com/KCL-Planning/SMTPlan.git /SMTPlan \
#  && cd /SMTPlan/SMTPlan \
#  && mkdir build \
#  && cd build \
#  && cmake .. \
#  && make

COPY . /SMTPlan
RUN cd /SMTPlan/SMTPlan \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make

# RUN ldconfig /usr/local/lib
# CMD /bin/bash

###############################################################################
## Second stage: the image to run the planner
##
## This is the image that will be distributed, we will simply copy here
## the files that we fetched and compiled in the previous image and that
## are strictly necessary to run the planner
###############################################################################
FROM ubuntu:16.04
# # Install any package needed to *run* the planner
RUN apt-get update && apt-get install --no-install-recommends -y \
    libgmp3-dev libmpfr-dev \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /SMTPlan/SMTPlan/build/SMTPlan /SMTPlan

RUN chmod +x ./SMTPlan

CMD /bin/bash
