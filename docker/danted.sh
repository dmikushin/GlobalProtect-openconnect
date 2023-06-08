#!/usr/bin/bash
# Wait for tun0 address to become availale and use it in /etc/danted.conf
while true; do
	IP=$(ip a | grep tun0 | grep inet | awk '{print $2}' | sed "s|/.*||")
	if [ "x$IP" != "x" ]; then
		echo "Starting SOCKS5 proxy to destination $IP provided by VPN"
		sed "s|##TUN0##|$IP|" /etc/danted.conf.in > /etc/danted.conf
		/usr/sbin/danted
	fi
	echo "Waiting for VPN to become ready"
	sleep 1
done
