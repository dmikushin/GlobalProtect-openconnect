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

RUN apt-get update

RUN apt-get -y --no-install-recommends install \
    build-essential \
    libqt5core5a \
    libqt5websockets5 \
    libqt5webenginewidgets5 \
    libqt5keychain1 \
    openconnect \
    ca-certificates

RUN apt-get -y --no-install-recommends install \
    openssh-server \
    sudo \
    vim

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd && \
    mkdir -p /var/run/sshd && \
    bash -c 'install -m755 <(printf "#!/bin/sh\nexit 0") /usr/sbin/policy-rc.d' && \
    ex +'%s/^#\zeHostKey .*ssh_host_.*_key/\1/g' -scwq /etc/ssh/sshd_config && \
    echo "MaxSessions 2147483647" >> /etc/ssh/sshd_config && \
    RUNLEVEL=1 dpkg-reconfigure openssh-server && \
    ssh-keygen -A -v && \
    update-rc.d ssh defaults

RUN apt-get -y --no-install-recommends install \
    supervisor

# Create an SSH key for SSH login
RUN sudo ssh-keygen -t rsa -q -f "/root/.ssh/id_rsa" -N "" && \
    mv /root/.ssh/id_rsa.pub /root/.ssh/authorized_keys

# We use supervisor instead of systemd to start multiple applications.
COPY ./docker/supervisord.conf /etc/
COPY ./docker/supervisor-log-prefix.sh /

COPY --from=builder /gpagent/install/ /usr

# Allow plain username/password storage in the configuration folder,
# because all keyrings require D-Bus, which we don't have in container.
ENV GPAGENT_ALLOW_PLAIN_PASSWORD=1

RUN apt-get -y --no-install-recommends install \
     git && \
     apt-get clean && \
     rm -rf /var/lib/apt/lists/*

# Setup noVNC to access gpagent via web browser.
WORKDIR /usr/share/
RUN git clone https://github.com/kanaka/noVNC.git
RUN ln -s /usr/share/noVNC/vnc_lite.html /usr/share/noVNC/index.html
WORKDIR /usr/share/noVNC/utils/
RUN git clone https://github.com/kanaka/websockify
WORKDIR /root
 
# Start supervisord
EXPOSE 8080
EXPOSE 8083
CMD ["/usr/bin/supervisord", "-c", "/etc/supervisord.conf"]

