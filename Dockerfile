FROM ubuntu:22.10 AS builder
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update

RUN apt-get install -y \
      build-essential \
      cmake \
      qtbase5-dev \
      libqt5websockets5-dev \
      qtwebengine5-dev \
      qttools5-dev \
      qt5keychain-dev

COPY . /gpagent
RUN cd /gpagent && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/gpagent/install .. && \
    make -j12 && \
    make install

FROM ubuntu:22.10
ENV DEBIAN_FRONTEND noninteractive

COPY --from=builder /gpagent/install/ /usr

RUN apt-get update

RUN apt-get install -y \
    build-essential \
    libqt5core5a \
    libqt5websockets5 \
    libqt5webengine5 \
    libqt5keychain1 \
    openconnect

RUN apt-get install -y \
    openssh-server \
    sudo \
    vim && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd && \
    mkdir -p /var/run/sshd && \
    bash -c 'install -m755 <(printf "#!/bin/sh\nexit 0") /usr/sbin/policy-rc.d' && \
    ex +'%s/^#\zeListenAddress/\1/g' -scwq /etc/ssh/sshd_config && \
    ex +'%s/^#\zeHostKey .*ssh_host_.*_key/\1/g' -scwq /etc/ssh/sshd_config && \
    RUNLEVEL=1 dpkg-reconfigure openssh-server && \
    ssh-keygen -A -v && \
    update-rc.d ssh defaults

# Start SSH server
EXPOSE 22
CMD ["/usr/bin/sudo", "/usr/sbin/sshd", "-D", "-o", "ListenAddress=0.0.0.0"]

